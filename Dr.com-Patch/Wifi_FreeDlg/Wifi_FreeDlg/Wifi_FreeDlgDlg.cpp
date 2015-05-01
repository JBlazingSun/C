
// Wifi_FreeDlgDlg.cpp : 实现文件
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


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框




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

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
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


// CWifi_FreeDlgDlg 对话框

BOOL m_isexitZ;


CWifi_FreeDlgDlg::CWifi_FreeDlgDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CWifi_FreeDlgDlg::IDD, pParent)
	, m_showText(_T(""))
	, m_isexit(FALSE)
	, m_id(_T(""))
	, m_password(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_showText=L"正在等待客户端登陆..";
	m_isexitZ=m_isexit;
}
void CWifi_FreeDlgDlg::InitIdAndPassWord()
{
	HKEY hKey;
	RegOpenKey(HKEY_LOCAL_MACHINE,L"Software\\Wifi_Free",&hKey);
	if (hKey == 0)
	{
		MessageBox(L"请先设置WIFI账号和密码",0,0);
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

	if (Wifi_FreedllAddr)	//判断注入是否成功
	{
		if (m_isexitZ)
		{
			ExitProcess(0);
		}
	}
	else
	{
		MessageBox(0,L"请检查杀毒软件是否阻止本程序，请添加信任或者关闭杀毒软件",0,0);
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



// CWifi_FreeDlgDlg 消息处理程序

BOOL CWifi_FreeDlgDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
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

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	fstream _file;
	_file.open(L"Wifi_Free.dll",ios::in);
	if (!_file)
	{
		MessageBox(L"请把 Wifi_Free.dll 放在同一目录，再打开本程序",0,0);
		ExitProcess(0);
	}

	this->InitIdAndPassWord();
	HKEY hKey;
	RegOpenKey(HKEY_LOCAL_MACHINE,L"Software\\Wifi_Free",&hKey);
	if (hKey == 0)
	{
		MessageBox(L"请先设置WIFI账号和密码",0,0);
	}
	else
	{
		_beginthread(StartApp,0,0);
	}


	m_tooltip.Create(this,0);
	m_tooltip.AddTool(GetDlgItem(IDC_BUTTON1));
	m_bTooltipActived=TRUE;

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CWifi_FreeDlgDlg::OnPaint()
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
HCURSOR CWifi_FreeDlgDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CWifi_FreeDlgDlg::OnBnClickedButton1()
{
	
	if (m_bTooltipActived)
	{
		m_tooltip.UpdateTipText(L"添加好准备创建的WIFI账号和密码，点击此按钮会将信息保存，如需更改信息也是重复此步骤",GetDlgItem(IDC_BUTTON1));
	}
	HKEY hKey;
	CString data_set=L"Software\\Wifi_Free";
	UpdateData(1);
	
	if (RegCreateKey(HKEY_LOCAL_MACHINE,data_set,&hKey) == ERROR_SUCCESS)
	{
		if (RegSetValue(hKey,L"ID",REG_SZ,m_id,wcslen(m_id)+1) == ERROR_SUCCESS && RegSetValue(hKey,L"PassWord",REG_SZ,m_password,wcslen(m_password)+1) == ERROR_SUCCESS)
		{
			RegCloseKey(hKey);
			MessageBox(L"设置成功",L"设置成功",0);
		}
	}
	else
	{
		RegCloseKey(hKey);
		MessageBox(L"设置失败",0,0);
	}
	
}


BOOL CWifi_FreeDlgDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 在此添加专用代码和/或调用基类
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
	// TODO: 在此添加专用代码和/或调用基类
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

		MessageBox(L"下次启动时自动退出生效",0,0);
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
