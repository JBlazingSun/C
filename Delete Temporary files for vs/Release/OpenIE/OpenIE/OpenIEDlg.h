
// OpenIEDlg.h : ͷ�ļ�
//

#pragma once


// COpenIEDlg �Ի���
class COpenIEDlg : public CDialogEx
{
// ����
public:
	COpenIEDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_OPENIE_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
//	CString m_start;
//	CString m_end;
	afx_msg void OnBnClickedButton1();
//	long m_strat;
	CString m_stat;
	afx_msg void OnBnClickedButton2();
};
