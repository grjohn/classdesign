
// MFCApplication1Dlg.h : ͷ�ļ�
//

#pragma once
#include "mscomm1.h"


// CMFCApplication1Dlg �Ի���
class CMFCApplication1Dlg : public CDialogEx
{
// ����
public:
	CMFCApplication1Dlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCAPPLICATION1_DIALOG };
#endif

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
	CMscomm1 m_ctrlComm;
	CString m_strRXData;
	CString m_strTXData;
	DECLARE_EVENTSINK_MAP()
//	void OnCommMscomm1();
	void OnComm();
	afx_msg void OnBnClickedButtonManualsend();
	afx_msg void OnBnClickedButton2();
	CMscomm1 m_ctrlComm1;
	CString m_strRXData1;
	CString m_strTXData1;
	void OnComm1();
	afx_msg void OnBnClickedButtonManualsend1();
	afx_msg void OnBnClickedButton3();
};
