
// PatchC1.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CPatchC1App:
// �йش����ʵ�֣������ PatchC1.cpp
//

class CPatchC1App : public CWinApp
{
public:
	CPatchC1App();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CPatchC1App theApp;