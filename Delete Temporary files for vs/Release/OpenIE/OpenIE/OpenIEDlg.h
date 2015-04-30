
// OpenIEDlg.h : 头文件
//

#pragma once


// COpenIEDlg 对话框
class COpenIEDlg : public CDialogEx
{
// 构造
public:
	COpenIEDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_OPENIE_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
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
