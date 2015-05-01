
// CRC_MemoryCheckDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "CRC_MemoryCheck.h"
#include "CRC_MemoryCheckDlg.h"
#include "afxdialogex.h"
#include <windows.h>


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


DWORD CRC32(BYTE*,DWORD);
BOOL CodeSectionCRC32( );

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


// CCRC_MemoryCheckDlg 对话框




CCRC_MemoryCheckDlg::CCRC_MemoryCheckDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CCRC_MemoryCheckDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CCRC_MemoryCheckDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CCRC_MemoryCheckDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CCRC_MemoryCheckDlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// CCRC_MemoryCheckDlg 消息处理程序

BOOL CCRC_MemoryCheckDlg::OnInitDialog()
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

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CCRC_MemoryCheckDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CCRC_MemoryCheckDlg::OnPaint()
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
HCURSOR CCRC_MemoryCheckDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

DWORD CRC32(BYTE* ptr,DWORD Size);

BOOL CodeSectionCRC32( )
{

	PIMAGE_DOS_HEADER	    pDosHeader=NULL;
    PIMAGE_NT_HEADERS       pNtHeader=NULL;
    PIMAGE_SECTION_HEADER   pSecHeader=NULL;

	DWORD					ImageBase,OriginalCRC32;


	ImageBase=(DWORD)GetModuleHandle(NULL);//取基址，其实本例也可直接用0x4000000这个值

	 pDosHeader=(PIMAGE_DOS_HEADER)ImageBase;	 	 
     pNtHeader=(PIMAGE_NT_HEADERS32)((DWORD)pDosHeader+pDosHeader->e_lfanew);
	 //定位到PE文件头（即字串“PE\0\0”处）前4个字节处，并读出储存在这里的CRC-32值：
	 OriginalCRC32 =*((DWORD *)((DWORD)pNtHeader-4));

	 pSecHeader=IMAGE_FIRST_SECTION(pNtHeader);   //得到第一个区块的起始地址  
	
	 //假设第一个区块就是代码区块
	 //是从磁盘文件得到代码块的地址和大小来计算CRC32值
	 if(OriginalCRC32==CRC32((BYTE*) (ImageBase+pSecHeader->VirtualAddress),pSecHeader->Misc.VirtualSize)) 
		return TRUE;
	else
		return FALSE;


	//如果程序从磁盘文件获取第一区块的数据，加壳后，数据将可能不准确，因此对于要加壳的程序来说，
	//直接填上代码区块的地址和大小，方法是先随便填一数据，编译后用PE工具查看生成文件的代码区块的RVA和大小，
	//再填进来重新编译
	/*
	if(OriginalCRC32==CRC32((BYTE*) 0x401000,0x36AE)) 
		return TRUE;
	else
		return FALSE;
*/

}



////////////////////////////////////////////////////////////////
// 计算字符串的CRC32值
// 参数：欲计算CRC32值字符串的首地址和大小
// 返回值: 返回CRC32值

DWORD CRC32(BYTE* ptr,DWORD Size)
{

	DWORD crcTable[256],crcTmp1;
	
	//动态生成CRC-32表
	for (int i=0; i<256; i++)
	 {
		crcTmp1 = i;
		for (int j=8; j>0; j--)
		 {
			if (crcTmp1&1) crcTmp1 = (crcTmp1 >> 1) ^ 0xEDB88320L;
			 else crcTmp1 >>= 1;
		}

		 crcTable[i] = crcTmp1;
	 }
	//计算CRC32值
	DWORD crcTmp2= 0xFFFFFFFF;
	while(Size--)
	{
		crcTmp2 = ((crcTmp2>>8) & 0x00FFFFFF) ^ crcTable[ (crcTmp2^(*ptr)) & 0xFF ];
		ptr++;
	}
		
	return (crcTmp2^0xFFFFFFFF);
}


void CCRC_MemoryCheckDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码

	if(!CodeSectionCRC32())
	{
		MessageBox(L"File corrupted! !",0);
	}

}