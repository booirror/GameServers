﻿
#include "RedisPut.h"

RedisPut *RedisPut::m_ins=NULL;
RedisPut::RedisPut(){
	m_redis = redis::getIns();
}

RedisPut::~RedisPut(){
	if (m_ins){
		delete m_ins;
		m_ins = NULL;
	}
}

RedisPut *RedisPut::getIns(){
	if (!m_ins){
		m_ins = new RedisPut();
		m_ins->init();
	}
	return m_ins;
}

void RedisPut::init(){
	
}



bool RedisPut::PushConfig(string uid, SConfig *scf){
	bool ist = RedisGet::getIns()->SelectDB(REDIS_SCONFIG);
	if (ist){
		RedisGet::getIns()->setSConfig(uid, scf);
		return m_redis->Hash(g_redisdbnames[REDIS_SCONFIG] + uid, scf);
	}
	return ist;
}

bool RedisPut::setConfig(string uid, POINTTIP type, bool ist){
	SConfig *sc = RedisGet::getIns()->getSConfig(uid);
	if (sc){
		switch (type)
		{
		case POINT_MAIL:
			sc->set_mail(ist);
			break;
		case POINT_SHOUCHONG:
			sc->set_firstbuy(ist);
			break;
		case POINT_ACTIVE:
			sc->set_active(ist);
			break;
		case POINT_SHOP:
			
			break;
		case POINT_MAINFEI:
			sc->set_free(ist);
			break;
		case POINT_HAOYOU:
			sc->set_fri(ist);
			break;
		case POINT_RENWU:
			sc->set_task(ist);
			break;
		case POINT_SIGN:
			sc->set_yqs(ist);
			break;
		default:
			break;
		}
	}
	return PushConfig(uid, sc);
}

bool RedisPut::PushUserBase(UserBase *ub){
	RedisGet::getIns()->setUserBase(ub);
	bool ist = RedisGet::getIns()->SelectDB(REIDS_USERBASE);
	if (ist){
		string uid = ub->userid();
		m_redis->Hash(g_redisdbnames[REIDS_USERBASE]+"_user" + uid, ub);
	}
	return ist;
}


bool RedisPut::setUserBase(string uid,string key, string value){
	bool ist = RedisGet::getIns()->SelectDB(REIDS_USERBASE);
	if (ist){
		UserBase *ub = RedisGet::getIns()->getUserBase(uid);
		Descriptor *des = (Descriptor *)ub->GetDescriptor();
		Reflection *reflection = (Reflection *)ub->GetReflection();
		int sz = des->field_count();
		for (int i = 0; i < sz; i++){
			FieldDescriptor *fd = (FieldDescriptor *)des->field(i);
			string name = fd->name();
			FieldDescriptor::Type type = fd->type();
			if (name.compare(key) == 0){
				switch (type)
				{
				case google::protobuf::FieldDescriptor::TYPE_DOUBLE:
					reflection->SetDouble(ub, fd, atof(value.c_str()));
					break;
				case google::protobuf::FieldDescriptor::TYPE_FLOAT:
					reflection->SetFloat(ub, fd, atof(value.c_str()));
					break;
				case google::protobuf::FieldDescriptor::TYPE_INT64:
					reflection->SetInt64(ub, fd, atol(value.c_str()));
					break;
				case google::protobuf::FieldDescriptor::TYPE_UINT64:
					reflection->SetUInt64(ub, fd, atol(value.c_str()));
					break;
				case google::protobuf::FieldDescriptor::TYPE_INT32:
					reflection->SetInt32(ub, fd, atoi(value.c_str()));
					break;
				case google::protobuf::FieldDescriptor::TYPE_BOOL:
					reflection->SetBool(ub, fd, atoi(value.c_str()));
					break;
				case google::protobuf::FieldDescriptor::TYPE_STRING:
					reflection->SetString(ub, fd, value);
					break;
				case google::protobuf::FieldDescriptor::TYPE_BYTES:
					reflection->SetString(ub, fd, value);
					break;
				case google::protobuf::FieldDescriptor::TYPE_UINT32:
					reflection->SetUInt32(ub, fd, atol(value.c_str()));
					break;

				default:
					break;
				}
				break;
			}
		}
		return PushUserBase(ub);
	}
	return ist;
}

bool RedisPut::addUserBase(string uid, string key, int value){
	bool ist = RedisGet::getIns()->SelectDB(REIDS_USERBASE);
	if (ist){
		UserBase *ub1 = RedisGet::getIns()->getUserBase(uid);
		Descriptor *des = (Descriptor *)ub1->GetDescriptor();
		Reflection *reflection = (Reflection *)ub1->GetReflection();
		int sz = des->field_count();
		for (int i = 0; i < sz; i++){
			FieldDescriptor *fd = (FieldDescriptor *)des->field(i);
			string name = fd->name();
			FieldDescriptor::Type type = fd->type();
			if (name.compare(key) == 0){
				if (type == FieldDescriptor::TYPE_INT32){
					reflection->SetInt32(ub1, fd, reflection->GetInt32(*ub1, fd) + value);
				}
				else if (type == FieldDescriptor::TYPE_INT64){
					reflection->SetInt64(ub1, fd, reflection->GetInt64(*ub1, fd) + value);
				}
				else if (type == FieldDescriptor::TYPE_UINT32){
					reflection->SetUInt32(ub1, fd, reflection->GetUInt32(*ub1, fd) + value);
				}
				else if (type == FieldDescriptor::TYPE_UINT64){
					reflection->SetUInt64(ub1, fd, reflection->GetUInt64(*ub1, fd) + value);
				}
				break;
			}
		}
		return PushUserBase(ub1);
	}
	return ist;
}

bool RedisPut::PushUserIndex(int index){
	bool ist = RedisGet::getIns()->SelectDB(REIDS_USERBASE);
	if (ist){
		return m_redis->set(g_redisdbnames[REIDS_USERBASE]+"_userindex",index);
	}
	return ist;
}

bool RedisPut::PushUserLoginTime(string uid){
	if (uid.empty()){
		return false;
	}
	bool ist = RedisGet::getIns()->SelectDB(REIDS_USERBASE);
	if (ist){
		string tt = "logintime";
		char buff[20];
		time_t time = Common::getCurrentTime();
		sprintf(buff, "%ld", time);
		RedisGet::getIns()->setUserLoginTime(uid, time);
		return m_redis->set(g_redisdbnames[REIDS_USERBASE] + tt+uid, buff);
		
	}
	else{
		return false;
	}
}

bool RedisPut::PushPass(string uid, string pass){
	bool ist = RedisGet::getIns()->SelectDB(REIDS_PASS);
	if (ist){
		int len = pass.length();
		RedisGet::getIns()->setPass(uid, pass);
		m_redis->set(g_redisdbnames[REIDS_PASS] + uid, (char *)pass.c_str(), len);
	}
	return ist;
}

bool RedisPut::PushOpenid(string openid, string uid){
	bool ist = RedisGet::getIns()->SelectDB(REIDS_PASS);
	if (ist){
		RedisGet::getIns()->setOpenidPass(openid, uid);
		return m_redis->set(g_redisdbnames[REIDS_PASS] + "openid" + openid, (char *)uid.c_str());
	}
	return ist;
}

bool RedisPut::PushRank(Rank *rk){
	bool ist = RedisGet::getIns()->SelectDB(REIDS_RANK);
	if (ist){
		int type = rk->type();
		RedisGet::getIns()->setRank(rk, type);
		char buff[50];
		sprintf(buff, "%s%d", g_redisdbnames[REIDS_RANK].c_str(), type);
		m_redis->List(buff,rk);
	}
	return ist;
}

bool RedisPut::PushMail(string uid, Mail *mail){
	bool ist = RedisGet::getIns()->SelectDB(REIDS_MAIL);
	if (ist){
		int mid = mail->eid();
		char buff[100];
		sprintf(buff, "%s%s%d", g_redisdbnames[REIDS_MAIL].c_str(), uid.c_str(), mid);
		RedisGet::getIns()->setMail(uid, mail);
		return m_redis->Hash(buff, mail);
	}
	return ist;
}

void RedisPut::PopMail(string uid, Mail *ml){
	bool ist = RedisGet::getIns()->SelectDB(REIDS_MAIL);
	if (ist){
		int mid = ml->eid();
		char buff[100];
		sprintf(buff, "%s%s%d", g_redisdbnames[REIDS_MAIL].c_str(), uid.c_str(), mid);
		m_redis->delKey(buff);
		RedisGet::getIns()->eraseMail(uid, ml);
	}
}

bool RedisPut::PushFriend(string uid, Friend *fd){
	bool ist = RedisGet::getIns()->SelectDB(REIDS_FRIEND);
	if (ist){
		char buff[100];
		string fuid = fd->info().userid();
		sprintf(buff, "%s_%s", g_redisdbnames[REIDS_FRIEND].c_str(), uid.c_str());
		Friend *fri = RedisGet::getIns()->getFriend(uid,fuid);
		if (!fri){
			RedisGet::getIns()->setFriend(uid, fd, true);
			return m_redis->List(buff, fd);
		}
		else{
			RedisGet::getIns()->setFriend(uid, fd, true);
			return m_redis->setFriendList(buff, fd);
		}
	}
	return ist;
}

bool RedisPut::eraseFriend(string uid, Friend *fd){
	bool ist = RedisGet::getIns()->SelectDB(REIDS_FRIEND);
	if (ist){
		char buff[100];
		sprintf(buff, "%s_%s", g_redisdbnames[REIDS_FRIEND].c_str(), uid.c_str());
		RedisGet::getIns()->setFriend(uid, fd, false);
		return m_redis->eraseList(buff,fd);
	}
	return ist;
}

bool RedisPut::PushFriendChat(string sui, FriendChat fc){
	bool ist = RedisGet::getIns()->SelectDB(REIDS_FRIEND);
	if (ist){
		string key = g_redisdbnames[REIDS_FRIEND]+"_chat_"+sui;
		FriendChat *fc1 = (FriendChat *)ccEvent::create_message(fc.GetTypeName());
		fc1->CopyFrom(fc);
		RedisGet::getIns()->setFriendChat(sui,fc1);
		return m_redis->List(key, &fc);
	}
	return ist;
}

bool RedisPut::eraseFriendChat(string sui, FriendChat fc){
	bool ist = RedisGet::getIns()->SelectDB(REIDS_FRIEND);
	if (ist){
		string key = g_redisdbnames[REIDS_FRIEND] + "_chat_"+sui;
		RedisGet::getIns()->eraseFriendChat(sui, fc);
		return m_redis->eraseList(key,&fc);
	}
	return ist;
}

bool RedisPut::PushFriendNotice(string uid, FriendNotice *fn){
	bool ist = RedisGet::getIns()->SelectDB(REIDS_FRIEND);
	if (ist){
		char buff[100];
		sprintf(buff, "%s%d", (g_redisdbnames[REIDS_FRIEND] + "notice" + uid).c_str(), fn->nid());
		RedisGet::getIns()->setFriendNotice(uid, fn);
		return m_redis->Hash(buff, fn);
	}
	return ist;
}

bool RedisPut::eraseFriendNotice(string uid, FriendNotice *fn){
	bool ist = RedisGet::getIns()->SelectDB(REIDS_FRIEND);
	if (ist){
		char buff[100];
		sprintf(buff, "%s%d", (g_redisdbnames[REIDS_FRIEND] + "notice" + uid).c_str(), fn->nid());
		RedisGet::getIns()->eraseFriendNotice(uid, fn);
		return m_redis->delKey(buff);
	}
	return ist;
}

bool RedisPut::PushTaskStatus(string uid, int taskid, Status *status){
	bool ist = RedisGet::getIns()->SelectDB(REIDS_TASK);
	if (ist){
		char buff[30];
		sprintf(buff, "%sstatus%d", (g_redisdbnames[REIDS_TASK] + uid).c_str(), taskid);
		RedisGet::getIns()->setTaskStatus(uid, taskid, status);
		return m_redis->Hash(buff, status);
	}
	return ist;
}

bool RedisPut::PushFreeStatus(string uid, int fid, Status *status){
	bool ist = RedisGet::getIns()->SelectDB(REIDS_FREE);
	if (ist){
		char buff[30];
		sprintf(buff, "%sstatus%d", (g_redisdbnames[REIDS_FREE] + uid).c_str(), fid);
		m_redis->Hash(buff, status);
	}
	return ist;
}

bool RedisPut::PushExRecord(string uid, ExRecord *er){
	bool ist = RedisGet::getIns()->SelectDB(REIDS_EXCHANGE);
	if (ist){
		char buff[100];
		sprintf(buff,"%sexrecord%s%d", g_redisdbnames[REIDS_EXCHANGE].c_str(), uid.c_str(), er->eid());
		RedisGet::getIns()->PushExRecord(uid, er);
		m_redis->Hash(buff, er);
	}
	return ist;
}

bool RedisPut::setExchangeCode(string code){
	bool ist = RedisGet::getIns()->SelectDB(REIDS_EXCHANGE);
	if (ist){
		return m_redis->set(g_redisdbnames[REIDS_EXCHANGE]+"exrecordcode",(char *)code.c_str());
	}
	return ist;
}

bool RedisPut::setExchangeRecordId(string uid, int id){
	bool ist = RedisGet::getIns()->SelectDB(REIDS_EXCHANGE);
	if (ist){
		return m_redis->set(g_redisdbnames[REIDS_EXCHANGE] + "exrecordid"+uid, id);
	}
	return ist;
}

bool RedisPut::erasePExchangeCode(PExchangeCode *p){
	bool ist = RedisGet::getIns()->SelectDB(REIDS_EXCHANGE);
	if (ist){
		char buff[100];
		sprintf(buff, "%d", p->_id);
		string content = buff;
		content += ",";
		for (int i = 0; i < p->_rewardid.size(); i++){
			sprintf(buff,"%d",p->_rewardid.at(i));
			content += buff;
			if (i < p->_rewardid.size() - 1){
				content += "|";
			}
		}
		content += "," + p->_code;
		return m_redis->eraseList(g_redisdbnames[REIDS_EXCHANGE] + "code", content);
	}
	return ist;
}

bool RedisPut::setSignStatus(SignStatus *ss){
	bool ist = RedisGet::getIns()->SelectDB(REIDS_SIGN);
	if (ist){
		char buff[50];
		string uid = ss->_uid;
		sprintf(buff, "%s", (g_redisdbnames[REIDS_SIGN] + "status" + uid).c_str());
		char buff1[200];
		sprintf(buff1,"%s,%d,%d,%d,%s",uid.c_str(),ss->_signcount,ss->_issign,ss->_left,ss->_time.c_str());
		RedisGet::getIns()->setSignStatus(ss);
		m_redis->set(buff, buff1);
	}
	return ist;
}

bool RedisPut::PushFeedBack(CFeedBack *cfb){
	bool ist = RedisGet::getIns()->SelectDB(REIDS_FEEDBACK);
	if (ist){
		return m_redis->Hash(g_redisdbnames[REIDS_FEEDBACK], cfb);
	}
	return ist;
}

bool RedisPut::setMailID(int mid){
	bool ist = RedisGet::getIns()->SelectDB(REIDS_MAIL);
	if (ist){
		return m_redis->set(g_redisdbnames[REIDS_MAIL]+"mailid",mid);
	}
	return ist;
}

bool RedisPut::setFriendNoticeID(int id){
	bool ist = RedisGet::getIns()->SelectDB(REIDS_FRIEND);
	if (ist){
		return m_redis->set(g_redisdbnames[REIDS_FRIEND] + "friendnoticeid", id);
	}
	return ist;
}

bool RedisPut::setNoTime(string time){
	bool ist = RedisGet::getIns()->SelectDB(REIDS_SHOP);
	if (ist){
		return m_redis->set(g_redisdbnames[REIDS_SHOP] + "notime", (char*)time.c_str());
	}
	return ist;
}

bool RedisPut::setAliOuttradeNo(string num){
	bool ist = RedisGet::getIns()->SelectDB(REIDS_SHOP);
	if (ist){
		return m_redis->set(g_redisdbnames[REIDS_SHOP] + "aliouttradeno", (char*)num.c_str());
	}
	return ist;
}

bool RedisPut::pushAliPayOuttradeno(string uid, string out_trade_no, time_t time, int shopid, map<string, string> requestPairs){
	bool ist = RedisGet::getIns()->SelectDB(REIDS_SHOP);
	if (ist){
		string key = g_redisdbnames[REIDS_SHOP]+"_alipay_no_data";
		char buff[4096];
		sprintf(buff,"%s,%s,%ld,%d,",uid.c_str(),out_trade_no.c_str(),time,shopid);
		string con = buff;
		auto itr = requestPairs.begin();
		int index = 0;
		for (itr; itr != requestPairs.end();itr++){
			string k = itr->first;
			string v = itr->second;
			if (index < requestPairs.size() - 1){
				con += k + "^" + v + "|";
			}
			else{
				con += k + "^" + v;
			}
			index++;
		}
		AliPayNoData *p = new AliPayNoData();
		p->_uid = uid;
		p->_endtime = time;
		p->_maps = requestPairs;
		p->_out_trade_no = out_trade_no;
		p->_shopid = shopid;
		RedisGet::getIns()->setAliPayNoData(p);
		return m_redis->List(key, (char *)con.c_str());
	}
	return false;
}

bool RedisPut::eraseAliPayOuttradeno(string out_trade_no){
	bool ist = RedisGet::getIns()->SelectDB(REIDS_SHOP);
	if (ist){
		string key = g_redisdbnames[REIDS_SHOP] + "_alipay_no_data";
		AliPayNoData *p = RedisGet::getIns()->getAliPayNoData(out_trade_no);
		if (p){
			char buff[4096];
			sprintf(buff, "%s,%s,%ld,%d,", p->_uid.c_str(), p->_out_trade_no.c_str(), p->_endtime, p->_shopid);
			string con = buff;
			auto itr = p->_maps.begin();
			int index = 0;
			for (itr; itr != p->_maps.end(); itr++){
				string k = itr->first;
				string v = itr->second;
				if (index < p->_maps.size() - 1){
					con += k + "^" + v + "|";
				}
				else{
					con += k + "^" + v;
				}
				index++;
			}
			RedisGet::getIns()->eraseAliPayNoData(out_trade_no);
			return m_redis->eraseList(key, con);
		}
	}
	return ist;
}

bool RedisPut::PushPayRecord(PayRecord pr){
	bool ist = RedisGet::getIns()->SelectDB(REIDS_SHOP);
	if (ist){
		string uid = pr.userid();
		string key = g_redisdbnames[REIDS_SHOP] + "_PayRecord_"+uid;
		RedisGet::getIns()->setPayRecord(&pr);
		return m_redis->List(key, &pr);
	}
	return ist;
}

bool RedisPut::setWXNonceid(int nonceid){
	bool ist = RedisGet::getIns()->SelectDB(REIDS_SHOP);
	if (ist){
		string key = g_redisdbnames[REIDS_SHOP] + "_nonceid";
		RedisGet::getIns()->setWXNonceid(nonceid);
		return m_redis->set(key,nonceid);
	}
	return ist;
}

bool RedisPut::PushWXPayNoData(WXPayNoData *p){
	bool ist = RedisGet::getIns()->SelectDB(REIDS_SHOP);
	if (ist){
		string key = g_redisdbnames[REIDS_SHOP] + "_wxouttradeno";
		char buff[200];
		sprintf(buff,"%s,%ld,%s",p->_uid.c_str(),p->_endtime,p->_out_trade_no.c_str());
		return m_redis->List(key, buff);
	}
	return ist;
}

bool RedisPut::eraseWXPayNoData(WXPayNoData *p){
	bool ist = RedisGet::getIns()->SelectDB(REIDS_SHOP);
	if (ist){
		string key = g_redisdbnames[REIDS_SHOP] + "_wxouttradeno";
		char buff[200];
		sprintf(buff, "%s,%ld,%s", p->_uid.c_str(), p->_endtime, p->_out_trade_no.c_str());
		return m_redis->eraseList(key, buff);
	}
	return ist;
}

void RedisPut::ZeroChange(char *&data, int sz){
	for (int i = 0; i < sz; i++){
		if (data[i] == ZERO_STR){
			data[i] = '\0';
		}
	}
}

bool RedisPut::PushHus(map<int, map<uint64, int>> mps, int type, map<int, map<uint64, int>>mm){
	char buff[100];
	sprintf(buff,"hulist%d",type);
	string key = buff;
	auto itr = mps.begin();
	int index = 0;
	for (itr; itr != mps.end(); itr++){
		auto vec = &itr->second;
		int len = itr->first;
		map<uint64, int> *vv1=NULL;
		if (mm.find(len) != mm.end()){
			vv1 = &mm.at(len);
		}
		auto itr1 = vec->begin();
		for (itr1; itr1 != vec->end(); itr1++){
			uint64 va = itr1->first;
			if (vv1&&vv1->find(va) != vv1->end()){
				continue;
			}
			sprintf(buff,"%d,%lld",len,va);
			m_redis->List(key, buff);
			printf("[%d][%d].{%s}\n",type,index++,buff);
		}
	}
	return true;
}