
// Wifi_FreeDlg.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CWifi_FreeDlgApp:
// �йش����ʵ�֣������ Wifi_FreeDlg.cpp
//

class CWifi_FreeDlgApp : public CWinApp
{
public:
	CWifi_FreeDlgApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CWifi_FreeDlgApp theApp;