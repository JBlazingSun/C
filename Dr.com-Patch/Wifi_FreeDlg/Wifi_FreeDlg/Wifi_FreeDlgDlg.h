
// Wifi_FreeDlgDlg.h : ͷ�ļ�
//

#pragma once


// CWifi_FreeDlgDlg �Ի���
class CWifi_FreeDlgDlg : public CDialogEx
{
// ����
public:
	CWifi_FreeDlgDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_WIFI_FREEDLG_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��

	CToolTipCtrl m_tooltip;
	BOOL m_bTooltipActived;

	

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
	afx_msg void OnBnClickedButton1();
	void InitIdAndPassWord();
	CString m_showText;
	BOOL m_isexit;
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	CString m_id;
	CString m_password;
	virtual void OnCancel();
};
