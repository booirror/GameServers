#include "HttpLogic.h"
#include "CSVDataInfo.h"
#include "HttpEvent.h"
#include "LibEvent.h"
#include "Common.h"
#include "ClientSocket.h"
#include "LoginInfo.h"
#include "aes.h"


int HttpLogic::SERVER_PORT=0;
string HttpLogic::SERVER_CODE="";
HttpLogic *HttpLogic::m_Ins = NULL;



void HttpLogic::aes_decrypt(char* in, int inlen, char* out)
{
	if (!in || !out) return;
	unsigned char *iv = new unsigned char[AES_BLOCK_SIZE];
	memcpy(iv, DECKEY, AES_BLOCK_SIZE);

	AES_KEY aes;
	if (AES_set_encrypt_key((unsigned char*)DECKEY, 128, &aes) < 0)
	{
		return;
	}

	int num = 0;
	AES_cfb128_encrypt((unsigned char*)in, (unsigned char*)out, inlen, &aes, iv, &num, AES_DECRYPT);
	inlen = inlen / AES_BLOCK_SIZE*AES_BLOCK_SIZE;
	out[inlen + num] = '\0';

}

void HttpLogic::aes_encrypt(char* in, int inlen, char* out)
{
	if (!in || !out) return;
	unsigned char *iv = new unsigned char[AES_BLOCK_SIZE];
	memcpy(iv, DECKEY, AES_BLOCK_SIZE);
	AES_KEY aes;
	if (AES_set_encrypt_key((unsigned char*)DECKEY, 128, &aes) < 0)
	{
		return;
	}
	int num = 0;
	AES_cfb128_encrypt((unsigned char*)in, (unsigned char*)out, inlen, &aes, iv, &num, AES_ENCRYPT);
	inlen = inlen / AES_BLOCK_SIZE*AES_BLOCK_SIZE;
	out[inlen + num] = '\0';

}



HttpLogic::HttpLogic(){
	//this->scheduleUpdate(0.5, 1.0);
}
HttpLogic::~HttpLogic(){
	
}

bool HttpLogic::init()
{
	
    return true;
}

HttpLogic *HttpLogic::getIns(){
	if (!m_Ins){
		m_Ins = new HttpLogic();
		m_Ins->init();
	}
	return m_Ins;
}

void HttpLogic::update(float dt){
	CLog::log("httplogic-update\n");
}

void HttpLogic::respondleLogic(YMSocketData sd){
	int cmd = sd["cmd"].asInt();
	if (cmd == 0x0B){
		GateDataCall(sd);
	}
	else if (cmd == 0x0A){
		ManagerDataCall(sd);
	}
}

void HttpLogic::HandleLogic(YMSocketData sd, char *&buff, int &sz){
	CLog::log("socketdata:%s", sd.getJsonString().c_str());
}

void HttpLogic::requestGateData(){
	string url=sqlhttp;
	YMSocketData sd;
	sd["cmd"] = 0x0B;
	sd["type"] = 3;
	HttpEvent::getIns()->requestData(url,sd);
}

DWORD WINAPI threadClient1(int lPVOID){
	LibEvent *clib = LibEvent::getIns();
	clib->StartServer(HttpLogic::SERVER_PORT, 2, 5000, 600, 600);
	getchar();
	clib->StopServer();
	return GetCurrentThreadId();
}

void HttpLogic::ChangeZero(char *&data, int sz){
	
}

void HttpLogic::GateDataCall(YMSocketData sd){
	int err = sd["err"].asInt();
	if (err == 0){
		SERVER_PORT = sd["port"].asInt();
		SERVER_CODE = sd["name"].asString();
		CLog::log("\n/************************************************/\n");
		CLog::log("socket[%s] start:%d", SERVER_CODE.c_str(), SERVER_PORT);
		CLog::log("/************************************************/\n");
		thread t1(&threadClient1, NULL);
		t1.detach();
	}
	else{
		CLog::log("GateDataCall未获取到数据\n");
	}
}

void HttpLogic::requestManagerData(){
	string url = sqlhttp;
	YMSocketData sd;
	sd["cmd"] = 0x0A;
	sd["type"] = 3;
	HttpEvent::getIns()->requestData(url,sd);
}


DWORD WINAPI threadClient(int lPVOID){
	HttpLogic *p = HttpLogic::getIns();
	ClientSocket::getIns()->connect(p->m_logicmnip.c_str(), p->m_logicmnport);
	return GetCurrentThreadId();
}

void HttpLogic::ManagerDataCall(YMSocketData sd){
	int err = sd["err"].asInt();
	if (err == 0){
		unsigned int port;
		m_logicmnip =Common::getHostNameIp(sd["ip"].asString(),port);
		m_logicmnport = sd["port"].asInt();
		m_servername = sd["name"].asString();
		CLog::log("\n/************************************************/\n");
		CLog::log("client socket start:[ip]:%s,[port]:%d", m_logicmnip.c_str(), m_logicmnport);
		CLog::log("/************************************************/\n");
		thread t1(&threadClient, NULL);
		t1.detach();
	}
	else{
		CLog::log("ManagerDataCall未获取到数据\n");
	}
}