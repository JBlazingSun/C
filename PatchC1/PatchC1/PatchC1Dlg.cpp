
// PatchC1Dlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "PatchC1.h"
#include "PatchC1Dlg.h"
#include "afxdialogex.h"

#include <process.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CPatchC1Dlg �Ի���

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


// CPatchC1Dlg ��Ϣ�������

BOOL CPatchC1Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	SetTimer( mytimer ,2*1000 , *TimerProc );
	
//		CString str;
// 	int i = GetLastError();
// 	str.Format( L"%d" ,i);
// 	MessageBox( str,0,0);

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CPatchC1Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
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
