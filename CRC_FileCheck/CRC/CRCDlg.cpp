
// CRCDlg.cpp : ʵ���ļ�
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

	//��̬����CRC-32��
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
	//����CRC32ֵ
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
	


	//����ļ���
	GetModuleFileName(NULL,szFileName,MAX_PATH);
	//���ļ�
	HANDLE hFile = CreateFile(
		szFileName,
		GENERIC_READ,
		FILE_SHARE_READ, 
		NULL,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL,
		NULL);
	if ( hFile == INVALID_HANDLE_VALUE ) return FALSE;


	//����ļ����� :
	fileSize = GetFileSize(hFile,NULL);
	if (fileSize == 0xFFFFFFFF) return FALSE;

	pBuffer = new TCHAR [fileSize];     // �����ڴ�,Ҳ����VirtualAlloc�Ⱥ��������ڴ�
	ReadFile(hFile,pBuffer, fileSize, &NumberOfBytesRW, NULL);//��ȡ�ļ�����
	CloseHandle(hFile);  //�ر��ļ�


	
	pMZheader=(WORD*)pBuffer; //��ʱpMZheaderָ���ļ�ͷ
	pPEheaderRVA = *(WORD*)((byte*)pMZheader+0x3c);//��3ch����PE�ļ�ͷָ��
	
	//ab.Format("%x",pPEheaderRVA);
	//MessageBox(NULL,ab,0,0);
	//��λ��PE�ļ�ͷ�����ִ���PE\0\0������ǰ4���ֽڴ��������������������CRC-32ֵ��
	OriginalCRC32 =*((DWORD *)((byte*)pMZheader+pPEheaderRVA-4));
	OriginalCRC32^=0x4597563;
	fileSize=fileSize-DWORD(pPEheaderRVA);//��PE�ļ�ͷǰ�ǲ�������ȥ��
	DWORD tmp;
	tmp=pPEheaderRVA;
	pMZheader=(WORD*)((byte*)pMZheader+tmp);//��pMZheaderָ��PE�ļ�ͷ

	//CString ab;
	//ab.Format("%x",*pMZheader);
	//�Ƚ�CRC32ֵ
	//MessageBox(NULL,"���޸�",ab,NULL);

	if (CRC32((BYTE*)pMZheader,fileSize) == OriginalCRC32 )
	{
		//MessageBox(NULL,"δ�޸�","",NULL);
		return TRUE;
	}
	else
	{
		//CString aa;
		//aa.Format("nowcrc32=%x,old=%x",CRC32((BYTE*)pMZheader,fileSize),OriginalCRC32);
		//MessageBox(NULL,"���޸�",aa,NULL);
		return FALSE;
	}

}



// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

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


// CCRCDlg �Ի���




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


// CCRCDlg ��Ϣ�������

BOOL CCRCDlg::OnInitDialog()
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


	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CCRCDlg::OnPaint()
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
HCURSOR CCRCDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


WCHAR Dir[MAX_PATH];

void CCRCDlg::OnBnClickedButton1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	_asm nop
	_asm nop
	_asm nop
	if (!IsFileModified())
	{
		MessageBox(L"�޸���",0,0);
	}

}
