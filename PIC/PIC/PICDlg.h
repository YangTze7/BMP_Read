
// PICDlg.h : ͷ�ļ�
//

#pragma once


// CPICDlg �Ի���
class CPICDlg : public CDialog
{
// ����
public:
	CPICDlg(CWnd* pParent = NULL);	// ��׼���캯��
	CBitmap m_bmp;

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PIC_DIALOG };
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
	afx_msg void OnFileOpen();
	afx_msg void OnBnClickedMfcmenubutton2();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedCancel();
};
