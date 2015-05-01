
// Wifi_FreeDlgDlg.h : 头文件
//

#pragma once


// CWifi_FreeDlgDlg 对话框
class CWifi_FreeDlgDlg : public CDialogEx
{
// 构造
public:
	CWifi_FreeDlgDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_WIFI_FREEDLG_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持

	CToolTipCtrl m_tooltip;
	BOOL m_bTooltipActived;

	

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
	afx_msg void OnBnClickedButton1();
	void InitIdAndPassWord();
	CString m_showText;
	BOOL m_isexit;
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	CString m_id;
	CString m_password;
	virtual void OnCancel();
};
