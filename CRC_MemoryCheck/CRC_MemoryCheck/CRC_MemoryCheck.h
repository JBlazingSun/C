
// CRC_MemoryCheck.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CCRC_MemoryCheckApp:
// �йش����ʵ�֣������ CRC_MemoryCheck.cpp
//

class CCRC_MemoryCheckApp : public CWinApp
{
public:
	CCRC_MemoryCheckApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CCRC_MemoryCheckApp theApp;