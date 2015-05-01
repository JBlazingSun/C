
// CRC_MemoryCheckDlg.cpp : ʵ���ļ�
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


// CCRC_MemoryCheckDlg �Ի���




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


// CCRC_MemoryCheckDlg ��Ϣ�������

BOOL CCRC_MemoryCheckDlg::OnInitDialog()
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CCRC_MemoryCheckDlg::OnPaint()
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


	ImageBase=(DWORD)GetModuleHandle(NULL);//ȡ��ַ����ʵ����Ҳ��ֱ����0x4000000���ֵ

	 pDosHeader=(PIMAGE_DOS_HEADER)ImageBase;	 	 
     pNtHeader=(PIMAGE_NT_HEADERS32)((DWORD)pDosHeader+pDosHeader->e_lfanew);
	 //��λ��PE�ļ�ͷ�����ִ���PE\0\0������ǰ4���ֽڴ��������������������CRC-32ֵ��
	 OriginalCRC32 =*((DWORD *)((DWORD)pNtHeader-4));

	 pSecHeader=IMAGE_FIRST_SECTION(pNtHeader);   //�õ���һ���������ʼ��ַ  
	
	 //�����һ��������Ǵ�������
	 //�ǴӴ����ļ��õ������ĵ�ַ�ʹ�С������CRC32ֵ
	 if(OriginalCRC32==CRC32((BYTE*) (ImageBase+pSecHeader->VirtualAddress),pSecHeader->Misc.VirtualSize)) 
		return TRUE;
	else
		return FALSE;


	//�������Ӵ����ļ���ȡ��һ��������ݣ��ӿǺ����ݽ����ܲ�׼ȷ����˶���Ҫ�ӿǵĳ�����˵��
	//ֱ�����ϴ�������ĵ�ַ�ʹ�С���������������һ���ݣ��������PE���߲鿴�����ļ��Ĵ��������RVA�ʹ�С��
	//����������±���
	/*
	if(OriginalCRC32==CRC32((BYTE*) 0x401000,0x36AE)) 
		return TRUE;
	else
		return FALSE;
*/

}



////////////////////////////////////////////////////////////////
// �����ַ�����CRC32ֵ
// ������������CRC32ֵ�ַ������׵�ַ�ʹ�С
// ����ֵ: ����CRC32ֵ

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
		
	return (crcTmp2^0xFFFFFFFF);
}


void CCRC_MemoryCheckDlg::OnBnClickedButton1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	if(!CodeSectionCRC32())
	{
		MessageBox(L"File corrupted! !",0);
	}

}