
// CRCDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "CRC.h"
#include "CRCDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif



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

	crcTmp2^=618;

	return (crcTmp2^0xFFFFFFFF);
}



BOOL IsFileModified()
{

	DWORD fileSize,OriginalCRC32,NumberOfBytesRW;
	WORD* pMZheader;
	WORD pPEheaderRVA;
	TCHAR  *pBuffer ,szFileName[MAX_PATH]; 
	


	//获得文件名
	GetModuleFileName(NULL,szFileName,MAX_PATH);
	//打开文件
	HANDLE hFile = CreateFile(
		szFileName,
		GENERIC_READ,
		FILE_SHARE_READ, 
		NULL,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL,
		NULL);
	if ( hFile == INVALID_HANDLE_VALUE ) return FALSE;


	//获得文件长度 :
	fileSize = GetFileSize(hFile,NULL);
	if (fileSize == 0xFFFFFFFF) return FALSE;

	pBuffer = new TCHAR [fileSize];     // 申请内存,也可用VirtualAlloc等函数申请内存
	ReadFile(hFile,pBuffer, fileSize, &NumberOfBytesRW, NULL);//读取文件内容
	CloseHandle(hFile);  //关闭文件


	
	pMZheader=(WORD*)pBuffer; //此时pMZheader指向文件头
	pPEheaderRVA = *(WORD*)((byte*)pMZheader+0x3c);//读3ch处的PE文件头指针
	
	//ab.Format("%x",pPEheaderRVA);
	//MessageBox(NULL,ab,0,0);
	//定位到PE文件头（即字串“PE\0\0”处）前4个字节处，并读出储存在这里的CRC-32值：
	OriginalCRC32 =*((DWORD *)((byte*)pMZheader+pPEheaderRVA-4));
	OriginalCRC32^=0x4597563;
	fileSize=fileSize-DWORD(pPEheaderRVA);//将PE文件头前那部分数据去除
	DWORD tmp;
	tmp=pPEheaderRVA;
	pMZheader=(WORD*)((byte*)pMZheader+tmp);//将pMZheader指向PE文件头

	//CString ab;
	//ab.Format("%x",*pMZheader);
	//比较CRC32值
	//MessageBox(NULL,"已修改",ab,NULL);

	if (CRC32((BYTE*)pMZheader,fileSize) == OriginalCRC32 )
	{
		//MessageBox(NULL,"未修改","",NULL);
		return TRUE;
	}
	else
	{
		//CString aa;
		//aa.Format("nowcrc32=%x,old=%x",CRC32((BYTE*)pMZheader,fileSize),OriginalCRC32);
		//MessageBox(NULL,"已修改",aa,NULL);
		return FALSE;
	}

}



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


// CCRCDlg 对话框




CCRCDlg::CCRCDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CCRCDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CCRCDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CCRCDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CCRCDlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// CCRCDlg 消息处理程序

BOOL CCRCDlg::OnInitDialog()
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

void CCRCDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CCRCDlg::OnPaint()
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
HCURSOR CCRCDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


WCHAR Dir[MAX_PATH];

void CCRCDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	_asm nop
	_asm nop
	_asm nop
	if (!IsFileModified())
	{
		MessageBox(L"修改了",0,0);
	}

}
