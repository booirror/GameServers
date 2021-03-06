// stdafx.h : 标准系统包含文件的包含文件，
// 或是经常使用但不常更改的
// 特定于项目的包含文件
//

#pragma once

#include "targetver.h"
#include <stdio.h>
#include <tchar.h>
#include<algorithm>
#include<vector>
#include<iostream>
#include "DBProto.h"
#include "Object.h"
#include <map>
#include <string.h>
#include <xstring>
#include "MD5.h"
#include "XXIconv.h"
#include "YMSocketData.h"
#include "ccEvent.h"
#include "LogicServer.h"
#include "RoomLogic.h"
#include "CLog.h"

using namespace std;
using namespace protocol;


enum ERR_CODE{
	ERR_OK,//正常

	UNKOWN,//未知错误

	LOGIN_PASS_ERR=100,//账户或密码错误
	LOGIN_TOKEN=101,//token已失效

	ROOM_OVER=201,//房间已满
	ROOM_AREDY_IN ,//已经在房间
	ROOM_NOT_IN,//不在房间
	ROOM_NOT_EXIT,//房间号不存在
	ROOM_HAVE_OVER,//房间人数已满
	
	OPERATE_NOT_DISCARD=301,//不该你打牌
	OPERATE_NOT_OP,//你没有碰 杠 胡这些操作

	REQUST_NOT_EXIT=401,//请求的数据格式有错

	CARD_NOT_ENOUCH=501,//房卡不足
};



#define HEADLEN 10
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32) 
#include "iconv.h"
#pragma comment(lib,"./Debug/libiconv.lib") 
#pragma comment(lib,"./Debug/libprotobuf.lib")
#pragma comment(lib,"./Debug/libMessagePack.lib")
#pragma comment(lib,"./Debug/libcrypto.lib")
#endif

#define CC_HTTPFUNC_SELECTOR(_SELECTOR) static_cast<Http_CallFun>(&_SELECTOR)
#define http_handler(_SELECTOR) CC_HTTPFUNC_SELECTOR(_SELECTOR)
typedef void (Object::*Http_CallFun)(YMSocketData );

#define sqlhttp "http://www.lesharecs.com:8080/f137e668f5b5babdd361dcb5966a3fe9"
#define LOGIC_TOKEN "kashdkiuySKJHFKS312skfhksuiie2342"
#define DECKEY "FQ6M1w0GswdKkTuZWcFmM1rU3bDB/CTiw+KrONdCPOg"
#define MAXSTAMP 128
#define HTTP_KEY "f137e668f5b5babdd361dcb5966a3fe9"