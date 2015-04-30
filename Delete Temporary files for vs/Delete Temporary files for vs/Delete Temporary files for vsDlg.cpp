
// Delete Temporary files for vsDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Delete Temporary files for vs.h"
#include "Delete Temporary files for vsDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

extern CDeleteTemporaryfilesforvsDlg *deleteDlg ;
 void Searchfile (CString strisdirpath );
 void delete_ReleaseAndDebug(CString ReleaseAndDebugDir);

// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

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


// CDeleteTemporaryfilesforvsDlg 对话框



CDeleteTemporaryfilesforvsDlg::CDeleteTemporaryfilesforvsDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDeleteTemporaryfilesforvsDlg::IDD, pParent)
	, m_edit_path(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CDeleteTemporaryfilesforvsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_edit_path);
}

BEGIN_MESSAGE_MAP(CDeleteTemporaryfilesforvsDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CDeleteTemporaryfilesforvsDlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// CDeleteTemporaryfilesforvsDlg 消息处理程序

void beginSearchfile( void * )
{
	CString strdir;
	WCHAR dir[MAX_PATH];
	GetCurrentDirectory( MAX_PATH , dir ) ;
	strdir= dir;
	Searchfile( strdir );
	MessageBox( deleteDlg->m_hWnd ,L"全部已经删除",0,0);
}

BOOL CDeleteTemporaryfilesforvsDlg::OnInitDialog()
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

	deleteDlg= this;
	// TODO: 在此添加额外的初始化代码




	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CDeleteTemporaryfilesforvsDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CDeleteTemporaryfilesforvsDlg::OnPaint()
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
HCURSOR CDeleteTemporaryfilesforvsDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CDeleteTemporaryfilesforvsDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
		_beginthread( beginSearchfile,0,0);
// 	CFileFind ff;
// 	CString strisdirpath;
// 	CString ReleaseAndDebug;
// 	BOOL Releaseres = ff.FindFile( L"*.*");		//删除 Release Debug  文件夹
// 	while ( Releaseres)
// 	{
// 		Releaseres = ff.FindNextFileW();
// 		if ( ff.IsDots())
// 		{
// 			continue;
// 		}
// 		if ( ff.IsDirectory() )
// 		{
// 			strisdirpath  = ff.GetFileName();
// 			if ( !wcscmp( strisdirpath , L"Release") )
// 			{
// 				SetCurrentDirectory( ff.GetFilePath() );
// 				delete_ReleaseAndDebug( ff.GetFilePath() );
// 				ReleaseAndDebug=ff.GetFilePath();
// 				SetCurrentDirectory( L".." );
// 				RemoveDirectory(ReleaseAndDebug);
// 			}
// 			if ( !wcscmp( strisdirpath , L"Debug") )
// 			{
// 				SetCurrentDirectory( ff.GetFilePath() );
// 				delete_ReleaseAndDebug( ff.GetFilePath() );
// 				ReleaseAndDebug=ff.GetFilePath();
// 				SetCurrentDirectory( L".." );
// 				RemoveDirectory(ReleaseAndDebug);
// 			}
// 		}
// 	}
	

// 	DWORD  i = GetLastError();
// 	CString strdir;
// 	strdir.Format( L"%d", i);
// 	MessageBox( strdir ,0,0);
}
