﻿#ifndef __LYNX_GAME_SERVER_ConfigData_H__
#define __LYNX_GAME_SERVER_ConfigData_H__
#include "stdafx.h"
#include "redis.h"
using namespace std;

#define CARDNUMBER 120

enum HuTypeEnum
{
	None=0,
	PI,//屁胡
	PENGPENG,//碰碰胡
	QIDUI,//七对
	QINGYISE,//清一色
	QYSPENG,//清一色碰碰胡
	QYSQD,//清一色七对
};

enum HeiOrYing
{
	HEI,
	RUAN,
};

enum HUTYPE{
	ZIMO_TYPE,//自摸
	PAO_TYPE,//放炮
	PAOGANG_TYPE,//抢杠
	ZIMOGANG_TYPE//杠上开花
};

enum OTHERHANDPAO{
	MENQING_PAO,//门清
	KA_DU_PAO,//卡独
	GANGHU_PAO,//杠胡
	HONGBAN_PAO,//红中白板
	KE_PAO,//除去红中白板
};

enum PENGPAO{
	NONE_PAO,
	MGANG_PAO,
	AGANG_PAO,
	PENG_PAO,
};

struct HuItem
{
	HuTypeEnum	_hutype;
	HeiOrYing	_hy;
};

struct PaoItem
{
	map<HUTYPE,int> _hu;
	map<OTHERHANDPAO, int> _handpao;
	map<PENGPAO, int> _pengpao;
	int _fapao;
};

static int g_all_mjkind[] = {
	0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09,
	0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19,
	0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27, 0x28, 0x29,
	0x31, 0x32, 0x33, 0x34,
	0x35, 0x36, 0x37
};

#define g_kind (sizeof(g_all_mjkind)/sizeof(int))

static int g_all_mj[] = {
	g_all_mjkind[0], g_all_mjkind[0], g_all_mjkind[0], g_all_mjkind[0],
	g_all_mjkind[1], g_all_mjkind[1], g_all_mjkind[1], g_all_mjkind[1],
	g_all_mjkind[2], g_all_mjkind[2], g_all_mjkind[2], g_all_mjkind[2],
	g_all_mjkind[3], g_all_mjkind[3], g_all_mjkind[3], g_all_mjkind[3],
	g_all_mjkind[4], g_all_mjkind[4], g_all_mjkind[4], g_all_mjkind[4],
	g_all_mjkind[5], g_all_mjkind[5], g_all_mjkind[5], g_all_mjkind[5],
	g_all_mjkind[6], g_all_mjkind[6], g_all_mjkind[6], g_all_mjkind[6],
	g_all_mjkind[7], g_all_mjkind[7], g_all_mjkind[7], g_all_mjkind[7],
	g_all_mjkind[8], g_all_mjkind[8], g_all_mjkind[8], g_all_mjkind[8],

	g_all_mjkind[9], g_all_mjkind[9], g_all_mjkind[9], g_all_mjkind[9],
	g_all_mjkind[10], g_all_mjkind[10], g_all_mjkind[10], g_all_mjkind[10],
	g_all_mjkind[11], g_all_mjkind[11], g_all_mjkind[11], g_all_mjkind[11],
	g_all_mjkind[12], g_all_mjkind[12], g_all_mjkind[12], g_all_mjkind[12],
	g_all_mjkind[13], g_all_mjkind[13], g_all_mjkind[13], g_all_mjkind[13],
	g_all_mjkind[14], g_all_mjkind[14], g_all_mjkind[14], g_all_mjkind[14],
	g_all_mjkind[15], g_all_mjkind[15], g_all_mjkind[15], g_all_mjkind[15],
	g_all_mjkind[16], g_all_mjkind[16], g_all_mjkind[16], g_all_mjkind[16],
	g_all_mjkind[17], g_all_mjkind[17], g_all_mjkind[17], g_all_mjkind[17],

	g_all_mjkind[18], g_all_mjkind[18], g_all_mjkind[18], g_all_mjkind[18],
	g_all_mjkind[19], g_all_mjkind[19], g_all_mjkind[19], g_all_mjkind[19],
	g_all_mjkind[20], g_all_mjkind[20], g_all_mjkind[20], g_all_mjkind[20],
	g_all_mjkind[21], g_all_mjkind[21], g_all_mjkind[21], g_all_mjkind[21],
	g_all_mjkind[22], g_all_mjkind[22], g_all_mjkind[22], g_all_mjkind[22],
	g_all_mjkind[23], g_all_mjkind[23], g_all_mjkind[23], g_all_mjkind[23],
	g_all_mjkind[24], g_all_mjkind[24], g_all_mjkind[24], g_all_mjkind[24],
	g_all_mjkind[25], g_all_mjkind[25], g_all_mjkind[25], g_all_mjkind[25],
	g_all_mjkind[26], g_all_mjkind[26], g_all_mjkind[26], g_all_mjkind[26],

	g_all_mjkind[27], g_all_mjkind[27], g_all_mjkind[27], g_all_mjkind[27],
	g_all_mjkind[28], g_all_mjkind[28], g_all_mjkind[28], g_all_mjkind[28],
	g_all_mjkind[29], g_all_mjkind[29], g_all_mjkind[29], g_all_mjkind[29],
	g_all_mjkind[30], g_all_mjkind[30], g_all_mjkind[30], g_all_mjkind[30],
	
	g_all_mjkind[31], g_all_mjkind[31], g_all_mjkind[31], g_all_mjkind[31],
	g_all_mjkind[32], g_all_mjkind[32], g_all_mjkind[32], g_all_mjkind[32],
	g_all_mjkind[33], g_all_mjkind[33], g_all_mjkind[33], g_all_mjkind[33],
};

struct PaoNeed
{
	PaoNeed(){
		memset(_handcards,0,sizeof(int)*14);
		memset(_peng, 0, sizeof(int)* 4);
		memset(_ptype, 0, sizeof(PENGPAO)* 4);
		_facount = 0;
		_bao = 0;
		_baoniang = 0;
		_zhua = false;
		_isgang = false;
		_hu = None;
		_hucard = 0;
	}
	int _handcards[14];
	int _peng[4];
	PENGPAO _ptype[4];
	int _facount;
	int _bao;
	int _baoniang;
	bool _zhua;
	bool _isgang;
	HuTypeEnum _hu;
	int _hucard;
};

class ConfigData 
{
public:
	ConfigData();
	virtual ~ConfigData();
	
	static ConfigData *getIns();
	void init();
	void quickSort(int *s, int l, int r);
	int getMJ();
	int getMJ(int index);
	void initMJ();
	
	void setKezi();
	
	void setFengKeTo(int len, map<uint64, int> maps);
	void setShunzi();
	void init3P(int index, int kenum);
	void init3L(int shunnum, int index, vector<int>ww);

	HuItem isHu(int *pai, bool ispengqing);
	HuItem isHu(int *pai, bool ispengqing, int bao);
	uint64 getRedisLastIndex(string key);
	PaoItem getHandOtherPao(PaoNeed pn);//peng
private:
	void setValueZero(int *a, int v, int len,int &baocount);
	HuTypeEnum isFit(vector<int>p, int baocount, HuItem &item,int kind);
	map<int, vector<int>> getKindCard(int *temppai);
	void setLiankeBao(int i);
	vector<int> isTing(int *pai,int bao);
	map<int, vector<int>>chuTing(int *pai,int bao);
	void test();

private:
	
	static ConfigData *m_ins;
	vector<int >m_cards;
	int m_index;
	vector<vector<int>>m_kezi;
	vector<vector<int>>m_shunzi;
	map<int, map<uint64, int>>m_lianke;
	map<int, map<uint64, int>>m_liankebao;
	redis *m_predis;
};


#endif // __LYNX_GAME_SERVER_ConfigData_H__