
// Wifi_FreeDlgDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Wifi_FreeDlg.h"
#include "Wifi_FreeDlgDlg.h"
#include "afxdialogex.h"
#include "MyApp.h"
#include "Winsvc.h"
#include <windows.h>
#include "wininet.h"
#include "fstream"
#include "iostream"

using namespace std;

#pragma comment(lib,"wininet.lib")


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���




JysNT jy;



void CloseWifi()
{
	CStringA CloseServerCommand="netsh wlan stop hostednetwork";
	CFile file(L"CloseWifi.cmd",CFile::modeCreate |CFile::modeWrite);
	file.Write(CloseServerCommand,strlen(CloseServerCommand));
	file.Write("\r\n",strlen("\r\n"));
	file.Write("del CloseWifi.cmd",strlen("del CloseWifi.cmd"));
	file.Close();
	WinExec("CloseWifi.cmd",SW_HIDE);
}

BOOL CheckInternet()
{
	CString m_url=L"http://www.sina.com.cn";
	BOOL bConn = ::InternetCheckConnection(m_url, 1, 0);  
	if (bConn)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}



class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CWifi_FreeDlgDlg �Ի���

BOOL m_isexitZ;


CWifi_FreeDlgDlg::CWifi_FreeDlgDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CWifi_FreeDlgDlg::IDD, pParent)
	, m_showText(_T(""))
	, m_isexit(FALSE)
	, m_id(_T(""))
	, m_password(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_showText=L"���ڵȴ��ͻ��˵�½..";
	m_isexitZ=m_isexit;
}
void CWifi_FreeDlgDlg::InitIdAndPassWord()
{
	HKEY hKey;
	RegOpenKey(HKEY_LOCAL_MACHINE,L"Software\\Wifi_Free",&hKey);
	if (hKey == 0)
	{
		MessageBox(L"��������WIFI�˺ź�����",0,0);
	}
	else
	{
		LONG DataNum=0;
		RegQueryValue(HKEY_LOCAL_MACHINE,L"SOFTWARE\\Wifi_Free\\ID" ,0,&DataNum);
		WCHAR* pidbuf= new WCHAR[DataNum];
		RegQueryValue(HKEY_LOCAL_MACHINE,L"SOFTWARE\\Wifi_Free\\ID" ,pidbuf,&DataNum);
		m_id=pidbuf;
		UpdateData(0);
		delete [] pidbuf;

		DataNum=0;
		RegQueryValue(HKEY_LOCAL_MACHINE,L"SOFTWARE\\Wifi_Free\\PassWord" ,0,&DataNum);
		WCHAR* ppassbuf= new WCHAR[DataNum];
		RegQueryValue(HKEY_LOCAL_MACHINE,L"SOFTWARE\\Wifi_Free\\PassWord" ,ppassbuf,&DataNum);
		m_password=ppassbuf;
		UpdateData(0);
		delete [] ppassbuf;
	}
	RegCloseKey(hKey);
}
void readRegisexit()
{
	LONG DataNum=0;
	RegQueryValue(HKEY_LOCAL_MACHINE,L"SOFTWARE\\Wifi_Free\\isexit" ,0,&DataNum);
	WCHAR* pidbuf= new WCHAR[DataNum];
	RegQueryValue(HKEY_LOCAL_MACHINE,L"SOFTWARE\\Wifi_Free\\isexit" ,pidbuf,&DataNum);
	if ( pidbuf )
	{
		m_isexitZ=TRUE;
	}
	
	delete [] pidbuf;
}


void StartApp(void * arg1)
{
	CWifi_FreeDlgDlg wifi;
	
	CloseWifi();
	readRegisexit();

	int i=0;
	i=CheckInternet();
	while( !i )
	{
		i=CheckInternet();
		Sleep(500);
	}
	jy.InjectDll(L"DrClient.exe","//Wifi_Free.dll");
	DWORD Wifi_FreedllAddr=jy.EnumProcessesdll(L"DrClient.exe",L"Wifi_Free.dll");

	if (Wifi_FreedllAddr)	//�ж�ע���Ƿ�ɹ�
	{
		if (m_isexitZ)
		{
			ExitProcess(0);
		}
	}
	else
	{
		MessageBox(0,L"����ɱ������Ƿ���ֹ��������������λ��߹ر�ɱ�����",0,0);
		ExitProcess(0);
	}
}


void CWifi_FreeDlgDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT3, m_showText);
	DDX_Check(pDX, IDC_CHECK1, m_isexit);
	DDX_Text(pDX, IDC_EDIT1, m_id);
	DDX_Text(pDX, IDC_EDIT2, m_password);
}

BEGIN_MESSAGE_MAP(CWifi_FreeDlgDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CWifi_FreeDlgDlg::OnBnClickedButton1)
END_MESSAGE_MAP()



// CWifi_FreeDlgDlg ��Ϣ�������

BOOL CWifi_FreeDlgDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	fstream _file;
	_file.open(L"Wifi_Free.dll",ios::in);
	if (!_file)
	{
		MessageBox(L"��� Wifi_Free.dll ����ͬһĿ¼���ٴ򿪱�����",0,0);
		ExitProcess(0);
	}

	this->InitIdAndPassWord();
	HKEY hKey;
	RegOpenKey(HKEY_LOCAL_MACHINE,L"Software\\Wifi_Free",&hKey);
	if (hKey == 0)
	{
		MessageBox(L"��������WIFI�˺ź�����",0,0);
	}
	else
	{
		_beginthread(StartApp,0,0);
	}


	m_tooltip.Create(this,0);
	m_tooltip.AddTool(GetDlgItem(IDC_BUTTON1));
	m_bTooltipActived=TRUE;

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CWifi_FreeDlgDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CWifi_FreeDlgDlg::OnPaint()
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
HCURSOR CWifi_FreeDlgDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CWifi_FreeDlgDlg::OnBnClickedButton1()
{
	
	if (m_bTooltipActived)
	{
		m_tooltip.UpdateTipText(L"��Ӻ�׼��������WIFI�˺ź����룬����˰�ť�Ὣ��Ϣ���棬���������ϢҲ���ظ��˲���",GetDlgItem(IDC_BUTTON1));
	}
	HKEY hKey;
	CString data_set=L"Software\\Wifi_Free";
	UpdateData(1);
	
	if (RegCreateKey(HKEY_LOCAL_MACHINE,data_set,&hKey) == ERROR_SUCCESS)
	{
		if (RegSetValue(hKey,L"ID",REG_SZ,m_id,wcslen(m_id)+1) == ERROR_SUCCESS && RegSetValue(hKey,L"PassWord",REG_SZ,m_password,wcslen(m_password)+1) == ERROR_SUCCESS)
		{
			RegCloseKey(hKey);
			MessageBox(L"���óɹ�",L"���óɹ�",0);
		}
	}
	else
	{
		RegCloseKey(hKey);
		MessageBox(L"����ʧ��",0,0);
	}
	
}


BOOL CWifi_FreeDlgDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: �ڴ����ר�ô����/����û���
	m_tooltip.Activate(TRUE);
	if (m_tooltip.GetSafeHwnd()!=0)
	{
		m_tooltip.RelayEvent(pMsg);
	}
	if(pMsg-> wParam==VK_ESCAPE) 
	{ 
		return   TRUE; 
	} 
	if(pMsg-> wParam==VK_RETURN) 
	{ 
		return   TRUE; 
	} 

	return CDialogEx::PreTranslateMessage(pMsg);
}


void CWifi_FreeDlgDlg::OnCancel()
{
	// TODO: �ڴ����ר�ô����/����û���
	if (m_isexit)
	{
		HKEY hKey;
		CString data_set=L"Software\\Wifi_Free";
		if (RegCreateKey(HKEY_LOCAL_MACHINE,data_set,&hKey) == ERROR_SUCCESS)
		{
			if (RegSetValue(hKey,L"isexit",REG_SZ,L"1",wcslen(L"1")+1) == ERROR_SUCCESS )
			{
				RegCloseKey(hKey);
			}
		}

		MessageBox(L"�´�����ʱ�Զ��˳���Ч",0,0);
	}
	else
	{
		HKEY hKey;
		CString data_set=L"Software\\Wifi_Free";
		if (RegCreateKey(HKEY_LOCAL_MACHINE,data_set,&hKey) == ERROR_SUCCESS)
		{
			if (RegSetValue(hKey,L"isexit",REG_SZ,L"0",wcslen(L"0")+1) == ERROR_SUCCESS )
			{
				RegCloseKey(hKey);
			}
		}
	}
	


	CDialogEx::OnCancel();
}
