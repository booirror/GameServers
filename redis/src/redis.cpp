#include "redis.h"
#include "fmacros.h"

#ifndef _WIN32
#include <unistd.h>
#endif
#include <time.h>
#include <ctype.h>
#include <errno.h>
#include <sys/stat.h>
#ifndef _WIN32
#include <sys/time.h>
#endif
#include <assert.h>
#include <fcntl.h>
#include <limits.h>

#ifdef _WIN32
#include <fcntl.h>
#ifndef FD_SETSIZE
#define FD_SETSIZE 16000
#endif
#ifndef STDIN_FILENO
#define STDIN_FILENO (_fileno(stdin))
#endif
#include <winsock2.h>
#include <windows.h>
#include "win32fixes.h"
#define strcasecmp _stricmp
#define strncasecmp _strnicmp
#define strtoull _strtoui64
#endif


#include "zmalloc.h"
#include "help.h"
#include "anet.h"
#include "ae.h"
#include "ccEvent.h"

redis *redis::m_ins = NULL;
redis *redis::getIns(){
	if (!m_ins){
		m_ins = new redis();
	}
	return m_ins;
}

redis::redis(){

}

redis::~redis(){

}

bool redis::initial(std::string redisIp,int redisPort,std::string mypass)
{
	if (redisIp.empty() && mypass.empty()){
		printf("redisip or pass error!\n");
		return false;
	}
	//����redis������
	struct timeval timeout = { 1, 500000 };
	m_pConnect = redisConnectWithTimeout(redisIp.c_str(), redisPort, timeout);
	m_pReply = NULL;
	if (!m_pConnect)
	{
		return false;
	}
	if (m_pConnect != NULL && m_pConnect->err) {
		printf("redis connect failed:err:%d,errstr:%s\n", m_pConnect->err, m_pConnect->errstr);
		return false;
	}
	//���������¼
	m_pReply = (redisReply*)redisCommand(m_pConnect, "AUTH %s", mypass.c_str());
	if (!m_pReply)
	{
		printf("redis exe failed\n");
		return false;
	}

	if (!(m_pReply->type == REDIS_REPLY_STATUS && strcasecmp(m_pReply->str, "OK") == 0))
	{
		printf("redis auth failed\n");
		freeReplyObject(m_pReply);
		m_pReply = NULL;
		return false;
	}

	freeReplyObject(this->m_pReply);
	m_pReply = NULL;
	printf("redis auth success\n");
	return true;
}

void redis::release()
{
	//�ͷ�����
	freeReplyObject(m_pConnect);
	m_pConnect = NULL;
	m_pReply = NULL;
}

void redis::set(std::string key, std::string value)
{
	//����key��value��ϵ������redis
	redisReply* r = (redisReply*)redisCommand(this->m_pConnect, "SET %s %s", key.c_str(), value.c_str());
	if (!r)
	{
		printf("set redis faliled\n");
		return;
	}

	//ִ��ʧ��
	if (!(r->type == REDIS_REPLY_STATUS && strcasecmp(r->str, "OK") == 0))
	{
		printf("set redis faliled\n");
		freeReplyObject(r);
		return;
	}
	printf("set redis success\n");
	freeReplyObject(r);
}

std::string redis::get(std::string key)
{
	//����key��ȡvalue
	m_pReply = (redisReply*)redisCommand(this->m_pConnect, "GET %s", key.c_str());
	if (!m_pReply)
	{
		printf("get value failed\n");
		return "";
	}
	//get�ɹ����ؽ��Ϊ REDIS_REPLY_STRING 
	if (m_pReply->type != REDIS_REPLY_STRING)
	{
		printf("get redis faliled\n");
		freeReplyObject(m_pReply);
		m_pReply = NULL;
		return "";
	}
	printf("get redis success\n");
	std::string valuestr = m_pReply->str;
	freeReplyObject(m_pReply);
	m_pReply = NULL;

	return valuestr;
}

void redis::Hash(std::string key, Message *msg){
	std::vector<std::string>vec = PushDataToRedis(key,msg);
	for (int i = 0; i < vec.size();i++){
		string content = vec.at(i);
		redisReply* r = (redisReply*)redisCommand(this->m_pConnect, content.c_str());
		if (!r)
		{
			printf("set redis faliled\n");
			return;
		}

		//ִ��ʧ��
		if (r->type == REDIS_REPLY_ERROR || r->str)
		{
			printf("set redis faliled\n");
			freeReplyObject(r);
			return;
		}
		printf("set redis success\n");
		freeReplyObject(r);

	}
}

Message *redis::getHash(std::string key, std::string name){
	Message *msg = ccEvent::create_message(key);
	if (name.empty()){
		map<string, string>datas;
		m_pReply = (redisReply*)redisCommand(this->m_pConnect, "hgetall %s", key.c_str());
		if (!m_pReply)
		{
			printf("get value failed\n");
			return msg;
		}
		//get�ɹ����ؽ��Ϊ REDIS_REPLY_STRING 
		if (m_pReply->type == REDIS_REPLY_ERROR)
		{
			printf("get redis faliled\n");
			freeReplyObject(m_pReply);
			m_pReply = NULL;
			return msg;
		}
		int sz = m_pReply->elements;
		for (int i = 0; i < sz;i+=2){
			redisReply *rpname = m_pReply->element[i];
			redisReply *rpvalues = m_pReply->element[i+1];
			string name = rpname->str;
			string value = rpvalues->str;
			if (value.compare("default") == 0){
				value = "";
				datas.insert(make_pair(name, value));
			}
		}
		msg = PopDataFromRedis(key,datas);
	}
	else{

	}
	printf("get redis success\n");
	freeReplyObject(m_pReply);
	m_pReply = NULL;
	return msg;
}

Message *redis::PopDataFromRedis(std::string key, map<string, string>maps){
	char buff[512];
	Message *msg = ccEvent::create_message(key);
	::google::protobuf::Descriptor *des = (::google::protobuf::Descriptor *)msg->GetDescriptor();
	::google::protobuf::Reflection *reflection = (::google::protobuf::Reflection *) msg->GetReflection();
	int sz = des->field_count();
	for (int i = 0; i < sz; i++){
		::google::protobuf::FieldDescriptor *fd = (::google::protobuf::FieldDescriptor *)des->field(i);
		string name = fd->name();
		if (name.compare("cmd") == 0){
			continue;
		}
		if (maps.find(name) != maps.end()){
			string value = maps.at(name);
			::google::protobuf::FieldDescriptor::Type type = fd->type();
			bool ist = false;
			string t;
			switch (type)
			{
			case google::protobuf::FieldDescriptor::TYPE_DOUBLE:
				reflection->SetDouble(msg, fd, atof(value.c_str()));
				break;
			case google::protobuf::FieldDescriptor::TYPE_FLOAT:
				reflection->SetFloat(msg, fd, atof(value.c_str()));
				break;
			case google::protobuf::FieldDescriptor::TYPE_INT64:
				reflection->SetInt64(msg, fd, atol(value.c_str()));
				break;
			case google::protobuf::FieldDescriptor::TYPE_UINT64:
				reflection->SetUInt64(msg, fd, atol(value.c_str()));
				break;
			case google::protobuf::FieldDescriptor::TYPE_INT32:
				reflection->SetInt32(msg, fd, atoi(value.c_str()));
				break;
			case google::protobuf::FieldDescriptor::TYPE_BOOL:
				reflection->SetBool(msg, fd, atoi(value.c_str()));
				break;
			case google::protobuf::FieldDescriptor::TYPE_STRING:
				reflection->SetString(msg, fd, value);
				break;
			case google::protobuf::FieldDescriptor::TYPE_BYTES:
				reflection->SetString(msg, fd, value);
				break;
			case google::protobuf::FieldDescriptor::TYPE_UINT32:
				reflection->SetUInt32(msg, fd, atol(value.c_str()));
				break;

			default:
				ist = true;
				break;
			}
		}
	}
	return msg;
}

vector<string> redis::PushDataToRedis(std::string key, Message *msg){
	char buff[512];
	::google::protobuf::Descriptor *des = (::google::protobuf::Descriptor *)msg->GetDescriptor();
	::google::protobuf::Reflection *reflection = (::google::protobuf::Reflection *) msg->GetReflection();
	int sz = des->field_count();
	vector<string> vec;
	for (int i = 0; i < sz; i++){
		::google::protobuf::FieldDescriptor *fd = (::google::protobuf::FieldDescriptor *)des->field(i);
		string name = fd->name();
		
		if (name.compare("cmd") == 0){
			continue;
		}
		string content = "hset " + key + " ";
		content += name+" ";
		::google::protobuf::FieldDescriptor::Type type = fd->type();
		
		::google::protobuf::Message *msg1 = NULL;
		bool ist=false;
		string t;
		switch (type)
		{
		case google::protobuf::FieldDescriptor::TYPE_DOUBLE:
			sprintf(buff, "%g", reflection->GetDouble(*msg, fd));
			break;
		case google::protobuf::FieldDescriptor::TYPE_FLOAT:
			sprintf(buff, "%g", reflection->GetFloat(*msg, fd));
			break;
		case google::protobuf::FieldDescriptor::TYPE_INT64:
			sprintf(buff, "%ld", reflection->GetInt64(*msg, fd));
			break;
		case google::protobuf::FieldDescriptor::TYPE_UINT64:
			sprintf(buff, "%ld", reflection->GetUInt64(*msg, fd));
			break;
		case google::protobuf::FieldDescriptor::TYPE_INT32:
			sprintf(buff, "%d", reflection->GetInt32(*msg, fd));
			break;
		case google::protobuf::FieldDescriptor::TYPE_BOOL:
			sprintf(buff, "%d", reflection->GetBool(*msg, fd));
			break;
		case google::protobuf::FieldDescriptor::TYPE_STRING:
			t = reflection->GetString(*msg, fd);
			if (t.empty()){
				t = "default";
			}
			sprintf(buff, "%s", t.c_str());
			break;
		case google::protobuf::FieldDescriptor::TYPE_BYTES:
			t = reflection->GetString(*msg, fd);
			if (t.empty()){
				t = "default";
			}
			sprintf(buff, "%s", t.c_str());
			break;
		case google::protobuf::FieldDescriptor::TYPE_UINT32:
			sprintf(buff, "%ld", reflection->GetUInt32(*msg, fd));
			break;
		
		default:
			ist = true;
			break;
		}
		content +=buff;
		if (!ist){
			vec.push_back(content);
		}
	}
	
	
	return vec;
}