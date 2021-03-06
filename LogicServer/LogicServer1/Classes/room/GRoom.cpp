﻿#include "GRoom.h"
#include "ClientSocket.h"
#include "EventListen.h"
#include "EventDispatcher.h"
#include "HttpLogic.h"
#include "StatTimer.h"
#include "RoomControl.h"
#include "Common.h"
#include "CLog.h"
GRoom::GRoom():
m_curbao(0),
m_maxcount(4),
m_isbegin(false)
{
	m_isopen = false;
	m_lasttime = 0;
	m_pRoomInfo = RoomInfo::getIns();
	m_pRoomLogicInfo = RoomLogicInfo::getIns();
	memset(m_udata, NULL, sizeof(UData *)*4);
}

GRoom::~GRoom(){
	openUpdate(false);
	openDisTime(false);
	reset();
	for (int i = 0; i < 4; i++){
		if (m_udata[i]){
			delete m_udata[i];
			m_udata[i] = NULL;
		}
	}
}

bool GRoom::init()
{
	reset();
    return true;
}

void GRoom::openUpdate(bool isopen){
	if (!m_isopen&&isopen){
		m_isopen = isopen;
		StatTimer::getIns()->scheduleSelector(this, schedule_selector(GRoom::update), 1.0);
	}
	else if (m_isopen&&!isopen){
		m_isopen = isopen;
		StatTimer::getIns()->unscheduleSelector(this, schedule_selector(GRoom::update));
	}
}

void GRoom::update(float dt){
	if (m_lasttime > 0){
		time_t t = Common::getTime();
		int fl = t-m_lasttime;
		if (!m_tipuid.empty()){
			m_tipuid = "";
		}
		if (fl >= 0){
			m_lasttime = 0;
			VoteResult(true);
		}
	}
}

void GRoom::openDisTime(bool isopen){
	if (!m_isDisTime&&isopen){
		m_isDisTime = isopen;
		StatTimer::getIns()->scheduleSelector(this, schedule_selector(GRoom::DisTime), 1.0);
	}
	else if (m_isDisTime&&!isopen){
		m_isDisTime = isopen;
		StatTimer::getIns()->unscheduleSelector(this, schedule_selector(GRoom::DisTime));
	}
}

void GRoom::reset(){
	m_curbao=0;
	m_curbaoniang = 0;
	m_index = 0;
	m_cards.clear();
	for (int i = 0; i < 4; i++){
		UData *ud = m_udata[i];
		if (ud){
			ud->init();
			if (m_voteuids.find(ud->_uid) != m_voteuids.end()){
				m_voteuids.at(ud->_uid) = 0;
			}
		}
	}
	m_curchu=0;
	m_isgang=false;
	m_curdraw=0;
	m_curdir=-1;
	m_optype=DRAW_TYPE;
	m_dissoveuid = "";
	m_voteuids.clear();
}

void GRoom::PushUData(UData *ud){
	for (int i = 0; i < 4; i++){
		if (!m_udata[i]){
			m_udata[i] = ud;
			m_voteuids.insert(make_pair(ud->_uid,0));
			break;
		}
	}
}

UData *GRoom::getUData(string uid){
	for (int i = 0; i < 4; i++){
		UData *u = m_udata[i];
		if (u&& u->_uid.compare(uid)==0){
			return u;
		}
	}
	return NULL;
}

UData *GRoom::getUData(int pos){
	return m_udata[pos - 1];
}

vector<CPGCardData> GRoom::isPeng(int pos){
	return isPeng(pos, m_curchu);
}

vector<CPGCardData> GRoom::isMoGang(int pos){
	return isMoGang(pos,m_curdraw);
}

vector<CPGCardData> GRoom::isChuGang(int pos){
	return isChuGang(pos, m_curchu);
}

vector<CPGCardData> GRoom::isChi(int pos){
	return isChi(pos, m_curchu);
}

HuItem GRoom::isHu(int pos){
	return isHu(pos, m_optype == DRAW_TYPE ? m_curdraw : m_curchu);
}

vector<CPGCardData> GRoom::isPeng(int pos, int card){
	vector<CPGCardData> cpgs;
	UData *ud = m_udata[pos - 1];
	int *pai = ud->_hand;
	int count = 0;
	for (int i = 0; i < 14; i++){
		int va = pai[i];
		if (va>0 && va == card&&va != m_curbaoniang){
			count++;
			if (count >= 2){
				int a[2] = { va, va };
				CPGCardData cpg;
				cpg.set_type(2);
				cpg.set_cards(a, 2);
				cpg.set_bei(m_curdir);
				cpgs.push_back(cpg);
				break;
			}
		}
	}
	return cpgs;
}

vector<CPGCardData> GRoom::isMoGang(int pos, int card){
	UData *ud = m_udata[pos - 1];
	vector<CPGCardData> gang;
	//手牌
	int *pai = ud->_hand;
	//暗杠
	map<int, int>paicount;
	for (int i = 0; i < 14; i++){
		int va = pai[i];
		if (va>0){
			if (paicount.find(va) != paicount.end()){
				paicount.at(va)++;
			}
			else{
				paicount.insert(make_pair(va,1));
			}
		}
	}
	auto itr1 = paicount.begin();
	for (itr1; itr1 != paicount.end(); itr1++){
		int va = itr1->first;
		int count = itr1->second;
		if (count == 3 && va == m_curbaoniang){
			char a[3] = { va, va, va };
			CPGCardData cpg;
			cpg.set_cards(a, 3);
			cpg.set_bei(pos);
			cpg.set_type(6);
			gang.push_back(cpg);
		}
		else if (count == 4){
			char a[4] = { va, va, va, va };
			CPGCardData cpg;
			cpg.set_cards(a, 4);
			cpg.set_bei(pos);
			cpg.set_type(4);
			gang.push_back(cpg);
		}
	}

	//明杠
	vector<int>vec;
	auto itr = ud->_cpg.begin();
	for (itr; itr != ud->_cpg.end(); itr++){
		CPGCardData cpgd = *itr;
		int va = cpgd.cards()[0];
		if (cpgd.type() == 2){
			vec.push_back(va);
		}
	}
	
	for (int i = 0; i < 14; i++){
		int va = pai[i];
		for (int j = 0; j<vec.size(); j++){
			if (va>0 && vec.at(j) == va){
				char a[1] = { va};
				CPGCardData cpg;
				cpg.set_cards(a, 1);
				cpg.set_bei(pos);
				cpg.set_type(3);
				gang.push_back(cpg);
				break;
				//return true;
			}
		}
	}
	return gang;
}

vector<CPGCardData> GRoom::isChuGang(int pos, int card){
	vector<CPGCardData> cpgs;
	UData *ud = m_udata[pos - 1];
	if (ud){
		int *pai = ud->_hand;
		int count = 0;
		for (int i = 0; i < 14; i++){
			int va = pai[i];
			if (va>0 && va == card){
				count++;
				if (count == 3 || (count == 2 && m_curbaoniang==va)){
					char a[3] = { va, va, va };
					CPGCardData cpg;
					cpg.set_bei(m_curdir);
					cpg.set_cards(a);
					cpg.set_type(3);
					cpgs.push_back(cpg);
					break;
				}
			}
		}
		//碰
		if (!ud->_cpg.empty()){
			auto itr = ud->_cpg.begin();
			for (itr; itr != ud->_cpg.end(); itr++){
				CPGCardData cpgd = *itr;
				int va = cpgd.cards()[0];
				if (cpgd.type() == 2 && va == card){
					char a[1] = { va};
					CPGCardData cpg;
					cpg.set_bei(m_curdir);
					cpg.set_cards(a);
					cpg.set_type(5);
					cpgs.push_back(cpg);
					break;
				}
			}
		}
	}
	return cpgs;
}

vector<CPGCardData> GRoom::isChi(int pos, int card){
	vector<CPGCardData> cpgs;
	if (CHI_DEFINE == 1){
		if (card < 0x31){
			UData *ud = m_udata[pos - 1];
			int *pai = ud->_hand;
			vector<int *> vecs;
			int v1 = card - 2;
			int v2 = card - 1;
			int v3 = card + 1;
			int v4 = card + 2;
			int a1[2];
			a1[0] = v1;
			a1[1] = v2;
			vecs.push_back(a1);
			int a2[2];
			a2[0] = v2;
			a2[1] = v3;
			vecs.push_back(a2);
			int a3[2];
			a3[0] = v3;
			a3[1] = v4;
			vecs.push_back(a3);
			for (int i = 0; i < vecs.size(); i++){
				int *a = vecs.at(i);
				char b[3] = {a[0],a[1],0};
				for (int k = 0; k < 2; k++){
					for (int j = 0; j < 14; j++){
						int va = pai[j];
						if (va>0 && va == a[k]){
							a[k] = -1;
							break;
						}
					}
				}
				if (a[0] == -1 && a[1] == -1){
					b[2] = card;
					CPGCardData cpg;
					cpg.set_bei(m_curdir);
					cpg.set_cards(b);
					cpg.set_type(1);
					cpgs.push_back(cpg);
					//return true;
				}
			}
		}
	}
	return cpgs;
}

HuItem GRoom::isHu(int pos, int card){
	UData *ud = m_udata[pos - 1];
	int pai[14];
	memcpy(pai,ud->_hand,sizeof(int )*14);
	for (int i = 0; i < 14; i++){
		int va = ud->_hand[i];
		if (m_optype == DRAW_TYPE&&va == 0){
			pai[i] = card;
		}
		else{
			pai[i] = va;
		}
	}
	HuItem item = ConfigData::getIns()->isHu(pai, m_isgang, m_curbao);
	return item;
}

void GRoom::selectZhuang(){
	SSelectZhuang ssz;
	if (m_leftround == m_roomdata.round()){
		char mm[2] = { rand() % 6 + 1, rand() % 6 + 1 };
		m_zhuangpos = ((mm[0] + mm[1]) % 4) == 0 ? 4 : ((mm[0] + mm[1]) % 4);
		ssz.set_zdice(mm, 2);
	}
	else{
		//一炮双响、一炮三响为放炮的玩家坐庄，其余为胡的人坐庄，流局为原有庄的下一家坐庄
	}
	ssz.set_zhuang(m_zhuangpos);
	ssz.set_zuid(m_udata[m_zhuangpos-1]->_uid);
	m_pRoomLogicInfo->SendSSelectZhuang(ssz);
}

void GRoom::SendDice(string uid){
	m_leftround -= 1;
	if (m_leftround < 0){
		SDice sd;
		sd.set_suid(uid);
		sd.set_err(1);
		m_pRoomLogicInfo->SendSDice(sd);
		return;
	}
	m_roomdata.set_left(m_leftround);
	UData *ud = m_udata[m_zhuangpos-1];
	SDice sd;
	sd.set_suid(uid);
	if (ud&&ud->_uid.compare(uid) == 0){
		char mm[2] = { rand() % 6 + 1, rand() % 6 + 1 };
		sd.set_dice(mm,2);
	}
	else{
		sd.set_err(1);
	}
	m_pRoomLogicInfo->SendSDice(sd);
	StatTimer::getIns()->scheduleSelector(this, schedule_selector(GRoom::HandCardCallBack),3.0);
}

void GRoom::SendZhuangHandCards(){
	UData *ud = m_udata[m_zhuangpos - 1];
	if (ud){
		char pai[14] = { 0 };
		for (int i = 0; i < 14; i++){
			pai[i] = getMJ();
			ud->_hand[i] = pai[i];
		}
		SZhuangCard szc;
		szc.set_cards(pai, 14);
		szc.set_uid(ud->_uid);
		HuItem item = ConfigData::getIns()->isHu(ud->_hand,false);
		szc.set_hu(item._hutype);
		m_pRoomLogicInfo->SendSZhuangCard(szc);
	}
	
}

int GRoom::getZhuang(){
	return m_zhuangpos;
}

void GRoom::HandCardCallBack(float dt){
	StatTimer::getIns()->unscheduleSelector(this, schedule_selector(GRoom::HandCardCallBack));
	SendZhuangHandCards();
	SendHandCards();
}

void GRoom::SendHandCards(){
	for (int j = 1; j <= 4; j++){
		UData *ud = m_udata[j - 1];
		if (ud){
			char pai[14] = { 0 };
			for (int i = 0; i < 13; i++){
				pai[i] = getMJ();
				ud->_hand[i] = pai[i];
			}
			SZhuangCard szc;
			szc.set_cards(pai, 13);
			szc.set_uid(ud->_uid);
			HuItem item = ConfigData::getIns()->isHu(ud->_hand, false);
			szc.set_hu(item._hutype);
			m_pRoomLogicInfo->SendSZhuangCard(szc);
		}
	}
}

void GRoom::SendDraw(int pos, int card){
	pos = (pos%5==0)?1:pos;
	UData *ud = m_udata[pos - 1];
	int *pai=ud->_hand;
	for (int i = 13; i >= 0; i--){
		int va = pai[i];
		if (va==0){
			ud->_hand[i] = card;
			break;
		}
	}
	CLog::log("draw:[%d]->[%d]\n", pos, card);
	m_optype = DRAW_TYPE;
	m_curdir = pos;
	SDraw sd;
	sd.set_uid(ud->_uid);
	sd.set_gang(m_isgang);
	sd.set_card(card);
	HuItem item = isHu(pos);
	sd.set_hu(item._hutype);
	sd.set_pos(pos);
	vector<CPGCardData> vec= isMoGang(pos, card);
	for (int i = 0; i < vec.size();i++){
		CPGCardData cpg1 = vec.at(i);
		CPGCardData *cpg = sd.add_cpg();
		cpg->CopyFrom(cpg1);
	}
	m_pRoomLogicInfo->SendSDraw(sd);
}

void GRoom::SendDiscard(int pos, int card){
	UData *ud = m_udata[pos - 1];
	int *pai = ud->_hand;
	for (int i = 13; i >= 0; i--){
		int va = pai[i];
		if (va>0&&va == card){
			ud->_hand[i] = 0;
			break;
		}
	}
	CLog::log("discard:[%d]->[%d]\n", pos, card);
	m_optype = DISCARD_TYPE;
	m_curcpgcard = 0;
	m_isgang = false;
	m_curdir = pos;
	bool ist = false;
	

	for (int i = 1; i <= 4; i++){
		SDiscard sd;
		sd.set_card(card);
		sd.set_position(i);
		sd.set_uid(ud->_uid);
		if (pos != i){
			vector<CPGCardData> cpgs1 = isChi(i,card);
			for (int j = 0; j < cpgs1.size(); j++){
				CPGCardData *c1= sd.add_cpg();
				c1->CopyFrom(cpgs1.at(j));
				ist = true;
			}
			vector<CPGCardData> cpgs2 = isPeng(i, card);
			for (int j = 0; j < cpgs2.size(); j++){
				CPGCardData *c1 = sd.add_cpg();
				c1->CopyFrom(cpgs2.at(j));
				ist = true;
			}
			vector<CPGCardData> cpgs3 = isChuGang(i, card);
			for (int j = 0; j < cpgs3.size(); j++){
				CPGCardData *c1 = sd.add_cpg();
				c1->CopyFrom(cpgs3.at(j));
				ist = true;
			}

			HuItem item = isHu(i, card);
			sd.set_hu(item._hutype);

		}
		m_pRoomLogicInfo->SendSDiscard(sd);
	}
	if (!ist){
		StatTimer::getIns()->scheduleSelector(this, schedule_selector(GRoom::NextFrontDraw), 1.0);
	}
}

void GRoom::SendChi(int pos, int *chi){
	UData *ud = m_udata[pos - 1];
	int *pai = ud->_hand;
	int ch[2];
	memcpy(ch,chi,sizeof(int)*2);
	
	for (int j = 0; j < 2; j++){
		int card = ch[j];
		for (int i = 13; i >= 0; i--){
			int va = pai[i];
			if (va>0 && va == card){
				ud->_hand[i] = 0;
				pai[i] = 0;
				ch[j] = 0;
				break;
			}
		}
	}
	m_curcpgcard = chi[2];
	m_isgang = false;
	m_curdir = pos;
	
	char a[3] = {chi[0],chi[1],chi[2]};
	SChi sc;
	sc.set_card(a);
	sc.set_pos(pos);
	sc.set_uid(ud->_uid);
	m_pRoomLogicInfo->SendSChi(sc);
}

void GRoom::SendPeng(int pos, int card){
	UData *ud = m_udata[pos - 1];
	int *pai = ud->_hand;
	int ch[2] = {card,card};
	for (int j = 0; j < 2; j++){
		int card1 = ch[j];
		for (int i = 13; i >= 0; i--){
			int va = pai[i];
			if (va>0 && va == card1){
				ud->_hand[i] = 0;
				pai[i] = 0;
				ch[j] = 0;
				break;
			}
		}
	}
	CLog::log("peng:[%d]->[%d]\n", pos, card);
	m_curcpgcard = card;
	m_isgang = false;
	m_curdir = pos;

	SPeng sc;
	sc.set_card(card);
	sc.set_pos(pos);
	sc.set_uid(ud->_uid);
	m_pRoomLogicInfo->SendSPeng(sc);
}

void GRoom::SendMingGang(int pos, int card){
	UData *ud = m_udata[pos - 1];
	int *pai = ud->_hand;
	int ch[3] = { card, card ,card};
	for (int j = 0; j < 3; j++){
		int card1 = ch[j];
		for (int i = 13; i >= 0; i--){
			int va = pai[i];
			if (va>0 && va == card1){
				ud->_hand[i] = 0;
				pai[i] = 0;
				ch[j] = 0;
				break;
			}
		}
	}
	CLog::log("minggang:[%d]->[%d]\n", pos, card);
	m_curcpgcard = card;
	m_isgang = true;
	m_curdir = pos;
	map<int, HuItem> vec;
	for (int i = 1; i <= 4; i++){
		HuItem item = isHu(i, card);
		if (pos!=i && item._hutype!=None){
			vec.insert(make_pair(i,item));
		}
		UData *uda = m_udata[i-1];
		SMingGang smg;
		smg.set_pos(i);
		smg.set_card(card);
		smg.set_uid(uda->_uid);
		smg.set_hu(item._hutype);
		
		m_pRoomLogicInfo->SendSMingGang(smg);
	}
	if (vec.empty()){
		StatTimer::getIns()->scheduleSelector(this, schedule_selector(GRoom::NextBackDraw), 1.0);
	}
	else{
		//提示这些玩家可以胡
		for (auto itr = vec.begin(); itr != vec.end();itr++){
			int ppos = itr->first;
			UData *uda = m_udata[ppos-1];
			HuItem item = itr->second;
			SHu hu;
			hu.set_hu(item._hutype);
			hu.set_pos(ppos);
			hu.set_uid(uda->_uid);
			m_pRoomLogicInfo->SendSHu(hu);
		}
	}
}

void GRoom::SendAnGang(int pos, int card){
	UData *ud = m_udata[pos - 1];
	int *pai = ud->_hand;
	int ch[4] = { card, card, card ,card};
	for (int j = 0; j < 4; j++){
		int card1 = ch[j];
		for (int i = 13; i >= 0; i--){
			int va = pai[i];
			if (va>0 && va == card1){
				ud->_hand[i] = 0;
				pai[i] = 0;
				ch[j] = 0;
				break;
			}
		}
	}
	CLog::log("angang:[%d]->[%d]\n",pos,card);
	m_curcpgcard = card;
	m_isgang = true;
	m_curdir = pos;

	SAnGang sd;
	sd.set_card(card);
	sd.set_pos(pos);
	sd.set_uid(ud->_uid);
	sd.set_type(4);
	m_pRoomLogicInfo->SendSAnGang(sd);

	StatTimer::getIns()->scheduleSelector(this, schedule_selector(GRoom::NextBackDraw), 1.0);
}

void GRoom::SendHu(int pos){
	UData *ud = m_udata[pos - 1];
	HuItem item = isHu(pos);
	if (item._hutype!=None){
		//可以胡
		CLog::log("hu hu hu\n");
		SHu hu;
		hu.set_hu(item._hutype);
		hu.set_pos(pos);
		hu.set_uid(ud->_uid);
		m_pRoomLogicInfo->SendSHu(hu);
	}
}

void GRoom::NextFrontDraw(float dt){
	StatTimer::getIns()->unscheduleSelector(this, schedule_selector(GRoom::NextFrontDraw));
	int card = getMJ();
	if (card > 0){
		SendDraw(m_curdir + 1, card);
	}
	else{
		CLog::log("end!!!\n");
	}
}

void GRoom::NextBackDraw(float dt){
	StatTimer::getIns()->unscheduleSelector(this, schedule_selector(GRoom::NextBackDraw));
	int card = getMJ();
	if (card > 0){
		SendDraw(m_curdir, card);
	}
	else{
		CLog::log("end!!!\n");
	}
}

void GRoom::Begin(string uid,int type){
	SBegin sb;
	if (m_fangzhuuid.compare(uid) == 0){
		m_isbegin = true;
		reset();
		initMJ();
		sb.set_type(type);
		sb.set_uid(uid);
		m_pRoomInfo->SendSBegin(sb);
		selectZhuang();
	}
	
}

void GRoom::Ready(string uid, bool ready){
	CLog::log("33333\n");
	SReady sr;
	UData *ud = getUData(uid);
	if (ud&&ud->_ready!=ready){
		ud->_ready = ready;
		CLog::log("444444\n");
		sr.set_ready(ready);
		sr.set_position(getPosition(uid));
		sr.set_uid(uid);
	}
	else{
		CLog::log("5555555\n");
		sr.set_err(1);
		sr.set_uid(uid);
	}
	RoomInfo::getIns()->SendSReady(sr);
}

void GRoom::Leave(string uid, bool zhudong){
	if (zhudong){
		SLeave sl;
		sl.set_uid(uid);
		UData *ud = getUData(uid);
		if (ud&&!m_isbegin){
			PopUData(ud);
			sl.set_err(0);
		}
		else{
			sl.set_err(1);
		}
		m_pRoomInfo->SendSLeave(sl);
	}
	else{
		if (!m_isbegin){
			SLeave sl;
			sl.set_uid(uid);
			UData *ud = getUData(uid);
			if (ud){
				PopUData(ud);
				sl.set_err(0);
			}
			else{
				sl.set_err(1);
			}
			m_pRoomInfo->SendSLeave(sl);
		}
		else{
			onLine(uid, false);
		}
	}
	
	
}

void GRoom::PopUData(UData *ud){
	int sz = 0;
	for (int i = 0; i < 4;i++){
		if (m_udata[i]){
			if (m_udata[i] == ud){
				
				string uid = ud->_uid;
				if (m_voteuids.find(uid) != m_voteuids.end()){
					m_voteuids.erase(m_voteuids.find(uid));
				}
				delete m_udata[i];
				m_udata[i] = NULL;

				//return;
			}
			else{
				sz++;
			}
		}
	}
	
	if (sz == 0 && m_lasttime == 0){
		m_lasttime = Common::getTime();
		openUpdate(true);
	}
}

void GRoom::onLine(string uid, bool online){
	SLine sl;
	sl.set_uid(uid);
	UData *ud = getUData(uid);
	if (ud){
		ud->_online = online;
		sl.set_err(0);
	}
	else{
		sl.set_err(1);
	}
	m_pRoomInfo->SendSLine(sl);
	if (!online&&m_isbegin&&m_lasttime==0){
		m_tipuid = uid;
		m_lasttime = Common::getTime();
		openUpdate(true);
	}
	else if (online){
		if (m_tipuid.compare(uid) == 0){
			m_tipuid = "";
		}
	}
}

bool GRoom::DissolveRoom(string uid){
	SDissolveRoom sd;
	sd.set_uid(uid);
	sd.set_rid(m_roomdata.roomid());
	UData *ud = getUData(uid);
	if (ud){
		if (m_dissoveuid.empty()){
			m_distime = 10*60;
			openDisTime(true);
			m_dissoveuid = uid;
			sd.set_position(getPosition(uid));
			sd.set_time(Common::getTime());
			m_pRoomInfo->SendSDissolveRoom(sd);
			if (m_voteuids.find(uid) != m_voteuids.end()){
				m_voteuids.at(uid) = 1;
			}
			else{
				m_voteuids.insert(make_pair(uid, 1));
			}
			if (m_voteuids.size() <= 1){
				VoteResult(true);
			}
			return true;
		}
		else{
			sd.set_err(1);
		}
	}
	else{
		sd.set_err(1);
	}
	m_pRoomInfo->SendSDissolveRoom(sd);
	return false;
}

void GRoom::DisTime(float dt){
	if (m_distime > 0){
		m_distime -= 1;
		if (m_distime == 0){
			VoteResult(true);
		}
	}
}

bool GRoom::Agree(string uid, bool isagree){
	SVote sv;
	sv.set_uid(uid);
	UData *ud = getUData(uid);
	if (ud){
		auto itr = m_voteuids.find(uid);
		if (itr != m_voteuids.end()){
			itr->second = isagree ? 1 : 2;
		}
		else{
			m_voteuids.insert(make_pair(uid, isagree ? 1 : 2));
		}
	}
	sv.set_agree(isagree);
	m_pRoomInfo->SendSVote(sv);

	auto itr = m_voteuids.find(uid);
	int acount = 0;
	int dcount = 0;
	int count = m_voteuids.size();
	int tcount = 0;
	for (itr; itr != m_voteuids.end(); itr++){
		if (itr->second == 1){
			acount++;
			tcount++;
		}
		else if (itr->second == 2){
			dcount++;
			tcount++;
		}
	}
	if (acount == count||acount==3||(tcount==count&&acount>count/2)){
		VoteResult(true);
	}
	else if ((count == 2 && dcount == 1) || dcount > count / 2 || (tcount == count&&dcount>count / 2)){
		VoteResult(false);
	}
	else if(tcount==count){
		VoteResult(false);
	}
	return true;
}

void GRoom::VoteResult(bool isDissolve){
	openDisTime(false);
	SVoteResult svr;
	svr.set_dissolve(isDissolve);
	svr.set_uid(m_dissoveuid);
	m_pRoomInfo->SendSVoteResult(svr);
	if (isDissolve){
		m_distime = -1;
		openUpdate(false);
		m_voteuids.clear();
		RoomControl::getIns()->eraseRoom(m_roomdata.roomid());
	}
	else{
		m_distime = -1;
		m_dissoveuid = "";
		m_voteuids.clear();
	}
}

int GRoom::getPosition(string uid){
	for (int i = 1; i <= 4; i++){
		UData *ud = m_udata[i-1];
		if (ud&&ud->_uid.compare(uid) == 0){
			return i;
		}
	}
	return -1;
}

void GRoom::initMJ(){
	m_cards.clear();
	for (int i = 0; i < CARDNUMBER; i++){
		m_cards.push_back(g_all_mj[i]);
	}
	random_shuffle(m_cards.begin(), m_cards.end());
}

int GRoom::getMJ(){
	if (m_index >= m_cards.size()){
		return -1;
	}
	return m_cards.at(m_index++);
}

int GRoom::getMJ(int index){
	if (index<m_cards.size()){
		return m_cards.at(index);
	}
	return -1;
}