
// PICDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "PIC.h"
#include "PICDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CPICDlg �Ի���



CPICDlg::CPICDlg(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_PIC_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CPICDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CPICDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	
	ON_BN_CLICKED(IDC_BUTTON1, &CPICDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDCANCEL, &CPICDlg::OnBnClickedCancel)
END_MESSAGE_MAP()


// CPICDlg ��Ϣ�������

BOOL CPICDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

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

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	//CString filter = L"�����ļ�(*.bmp)|*.bmp|BMP(*.bmp)|*.bmp|";
	//CFileDialog Ofile(TRUE, NULL, NULL, OFN_HIDEREADONLY, filter, NULL);

	//if (IDOK == Ofile.DoModal()) {
	//	CString fPath = Ofile.GetPathName();       // ��ȡ�ļ�·��  
	//	CString fEnt = Ofile.GetFileExt();         // ��ȡ�ļ���չ��  
	//	fEnt.MakeLower();                          // ���ļ���չ��ת��ΪСд��ĸ  
	//HBITMAP hbmp = (HBITMAP)::LoadImage(AfxGetInstanceHandle(),
	//	_T("chn.bmp"),
	//	IMAGE_BITMAP,
	//	0,
	//	0,
	//	LR_CREATEDIBSECTION | LR_LOADFROMFILE);
	////if( hbmp == NULL )
	////    return FALSE;
	//m_bmp.Attach(hbmp);
	//DIBSECTION ds;
	//BITMAPINFOHEADER &bminfo = ds.dsBmih;
	//m_bmp.GetObject(sizeof(ds), &ds);
	//int cx = bminfo.biWidth; //�õ�ͼ����
	//int cy = bminfo.biHeight; //�õ�ͼ��߶�
	//CRect rect;
	//GetDlgItem(IDC_STATIC)->GetWindowRect(&rect);
	//
	//ScreenToClient(&rect);
	//CPICDlg::MoveWindow(rect.left, rect.top, cx + 300, cy + 300, true);
	//
	//GetDlgItem(IDC_STATIC)->MoveWindow(rect.left, rect.top, cx, cy, true);//������С








	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CPICDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CPICDlg::OnPaint()
{

	

		CPaintDC dc(GetDlgItem(IDC_STATIC)); // ���ڻ��Ƶ��豸������
		CRect rcclient;
		GetDlgItem(IDC_STATIC)->GetClientRect(&rcclient); //��ȡ�ؼ��Ĵ�С
		CDC memdc;
		memdc.CreateCompatibleDC(&dc);                //����һ���豸�ڴ���
		CBitmap bitmap;
		bitmap.CreateCompatibleBitmap(&dc, rcclient.Width(), rcclient.Height());//��ʼ��һ��λͼ�����豸��������Ϊ PictureBox��������ͬ�ĵ�ɫ��ͷֱ���
		memdc.SelectObject(&bitmap);
		CWnd::DefWindowProc(WM_PAINT, (WPARAM)memdc.m_hDC, 0);
		CDC maskdc;
		maskdc.CreateCompatibleDC(&dc);
		CBitmap maskbitmap;
		maskbitmap.CreateBitmap(rcclient.Width(),
			rcclient.Height(),
			1,
			1,
			NULL);
		maskdc.SelectObject(&maskbitmap);
		maskdc.BitBlt(0,
			0,
			rcclient.Width(),
			rcclient.Height(),
			&memdc,
			rcclient.left,
			rcclient.top,
			SRCCOPY);

		CBrush brush;
		brush.CreatePatternBrush(&m_bmp);
		dc.FillRect(rcclient, &brush);
		dc.BitBlt(rcclient.left,
			rcclient.top,
			rcclient.Width(),
			rcclient.Height(),
			&memdc,
			rcclient.left,
			rcclient.top,
			SRCPAINT);
		brush.DeleteObject();
	
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CPICDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}




void CPICDlg::OnBnClickedButton1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString filter = L"�����ļ�(*.bmp)|*.bmp|BMP(*.bmp)|*.bmp|";
	CFileDialog Ofile(TRUE, NULL, NULL, OFN_HIDEREADONLY, filter, NULL);

	if (IDOK == Ofile.DoModal()) {
		CString fPath = Ofile.GetPathName();       // ��ȡ�ļ�·��  
		CString fEnt = Ofile.GetFileExt(); // ��ȡ�ļ���չ��  
		fEnt.MakeLower();                          // ���ļ���չ��ת��ΪСд��ĸ  

		HBITMAP hbmp = (HBITMAP)::LoadImage(AfxGetInstanceHandle(),
			fPath,
			IMAGE_BITMAP,
			0,
			0,
			LR_CREATEDIBSECTION | LR_LOADFROMFILE);
		//if( hbmp == NULL )
		//    return FALSE;
		m_bmp.Attach(hbmp);
		DIBSECTION ds;
		BITMAPINFOHEADER &bminfo = ds.dsBmih;
		m_bmp.GetObject(sizeof(ds), &ds);
		int cx = bminfo.biWidth; //�õ�ͼ����
		int cy = bminfo.biHeight; //�õ�ͼ��߶�
		CRect rect;
		GetDlgItem(IDC_STATIC)->GetWindowRect(&rect);

		ScreenToClient(&rect);
		CPICDlg::MoveWindow(rect.left, rect.top, cx + 50, cy + 100, true);

		GetDlgItem(IDC_STATIC)->MoveWindow(rect.left, rect.top, cx, cy, true);//������С
	}
	
}


void CPICDlg::OnBnClickedCancel()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CDialog::OnCancel();
	
}
