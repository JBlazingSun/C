// Wifi_Free.h : Wifi_Free DLL 的主头文件
//

#pragma once

#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含“stdafx.h”以生成 PCH 文件"
#endif

#include "resource.h"		// 主符号


// CWifi_FreeApp
// 有关此类实现的信息，请参阅 Wifi_Free.cpp
//

class CWifi_FreeApp : public CWinApp
{
public:
	CWifi_FreeApp();

// 重写
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
void PatchMem(void *arg1);

class MyWifi
{
	
public:

//	MyWifi();
//	~MyWifi();
	CString strgetid;
	CString m_getregid,m_getregpassword;
	BOOL CheckId();
	void GetId();
	

};