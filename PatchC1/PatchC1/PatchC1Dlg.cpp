
// PatchC1Dlg.cpp : 实现文件
//

#include "stdafx.h"
#include "PatchC1.h"
#include "PatchC1Dlg.h"
#include "afxdialogex.h"

#include <process.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CPatchC1Dlg 对话框

// void *copythread( void *)
// {
// 	CFile file;
// 	file.Open( L" I:\\c1.txt" ,CFile:: modeCreate );
// 	if ( !file )
// 	{
// 		file.Open( L"I:\\c1.txt" ,CFile:: modeCreate | CFile:: modeReadWrite);
// 	}
// 	else
// 	{
// 		file.Remove( file.GetFileName(),0);
// 	}
// }
const int mytimer = 123;

void CALLBACK TimerProc( HWND hWnd,UINT nMsg,UINT nTimerid,DWORD dwTime )
{
	CFile file;
	CopyFile( L"c1.exe" , L"copyfile.exe" ,TRUE);

	file.Open( L"copyfile.exe", CFile::modeReadWrite);
	file.Close();
	DeleteFile( L"copyfile.exe");

	::ShowWindow( AfxGetMainWnd()->m_hWnd , SW_HIDE );

}

CPatchC1Dlg::CPatchC1Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CPatchC1Dlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CPatchC1Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CPatchC1Dlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CPatchC1Dlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// CPatchC1Dlg 消息处理程序

BOOL CPatchC1Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	SetTimer( mytimer ,2*1000 , *TimerProc );
	
//		CString str;
// 	int i = GetLastError();
// 	str.Format( L"%d" ,i);
// 	MessageBox( str,0,0);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CPatchC1Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CPatchC1Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CPatchC1Dlg::OnBnClickedButton1()
{
// 	CString str;
// 	CFile file;
// 
// 	CopyFile( L"I:\\c1.exe" , L"I:\\copyfile.exe" ,TRUE);
// 
// 	file.Open( L"I:\\copyfile.exe", CFile::modeReadWrite);
// 	Sleep(3000);
// 	file.Close();
// 	DeleteFile( L"I:\\copyfile.exe");
	CPatchC1Dlg *pDlg=new CPatchC1Dlg;
	CString str;

	int i = GetLastError();
	str.Format( L"%d" ,i);
	MessageBox( str,0,0);

}
