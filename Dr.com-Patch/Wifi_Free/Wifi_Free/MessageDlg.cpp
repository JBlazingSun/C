// MessageDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Wifi_Free.h"
#include "MessageDlg.h"
#include "afxdialogex.h"


// CMessageDlg �Ի���


IMPLEMENT_DYNAMIC(CMessageDlg, CDialogEx)

CMessageDlg::CMessageDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMessageDlg::IDD, pParent)
{

}

CMessageDlg::~CMessageDlg()
{
}
int nTimer=0;
VOID CALLBACK TimerProc(
	HWND hwnd,     // handle of window for timer messages
	UINT uMsg,     // WM_TIMER message
	UINT idEvent,  // timer identifier
	DWORD dwTime   // current system time
	)
{
	nTimer++;
	if ( nTimer==3)
	{
		HWND hWnd=::FindWindowW( 0,L"Kill Dr.Com");
		::SendMessageW(hWnd, WM_CLOSE ,0,0);
		KillTimer(hwnd,ntimeID);
		nTimer=0;
	}

}

void CMessageDlg::DoDataExchange(CDataExchange* pDX)
{
	SetTimer( ntimeID, 1*1000, &TimerProc);

	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CMessageDlg, CDialogEx)

	ON_BN_CLICKED(IDC_BUTTON1, &CMessageDlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// CMessageDlg ��Ϣ�������


void CMessageDlg::OnBnClickedButton1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	HWND hWnd=::FindWindowW( 0,L"Kill Dr.Com");
	::SendMessageW(hWnd, WM_CLOSE ,0,0);

}
