// Wifi_Free.h : Wifi_Free DLL ����ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CWifi_FreeApp
// �йش���ʵ�ֵ���Ϣ������� Wifi_Free.cpp
//

class CWifi_FreeApp : public CWinApp
{
public:
	CWifi_FreeApp();

// ��д
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