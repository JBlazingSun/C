
// Delete Temporary files for vs.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CDeleteTemporaryfilesforvsApp:
// �йش����ʵ�֣������ Delete Temporary files for vs.cpp
//

class CDeleteTemporaryfilesforvsApp : public CWinApp
{
public:
	CDeleteTemporaryfilesforvsApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CDeleteTemporaryfilesforvsApp theApp;

