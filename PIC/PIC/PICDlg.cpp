
// PICDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "PIC.h"
#include "PICDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
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


// CPICDlg 对话框



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


// CPICDlg 消息处理程序

BOOL CPICDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

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

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	//CString filter = L"所有文件(*.bmp)|*.bmp|BMP(*.bmp)|*.bmp|";
	//CFileDialog Ofile(TRUE, NULL, NULL, OFN_HIDEREADONLY, filter, NULL);

	//if (IDOK == Ofile.DoModal()) {
	//	CString fPath = Ofile.GetPathName();       // 获取文件路径  
	//	CString fEnt = Ofile.GetFileExt();         // 获取文件扩展名  
	//	fEnt.MakeLower();                          // 将文件扩展名转化为小写字母  
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
	//int cx = bminfo.biWidth; //得到图像宽度
	//int cy = bminfo.biHeight; //得到图像高度
	//CRect rect;
	//GetDlgItem(IDC_STATIC)->GetWindowRect(&rect);
	//
	//ScreenToClient(&rect);
	//CPICDlg::MoveWindow(rect.left, rect.top, cx + 300, cy + 300, true);
	//
	//GetDlgItem(IDC_STATIC)->MoveWindow(rect.left, rect.top, cx, cy, true);//调整大小








	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CPICDlg::OnPaint()
{

	

		CPaintDC dc(GetDlgItem(IDC_STATIC)); // 用于绘制的设备上下文
		CRect rcclient;
		GetDlgItem(IDC_STATIC)->GetClientRect(&rcclient); //获取控件的大小
		CDC memdc;
		memdc.CreateCompatibleDC(&dc);                //创建一个设备内存区
		CBitmap bitmap;
		bitmap.CreateCompatibleBitmap(&dc, rcclient.Width(), rcclient.Height());//初始化一个位图，于设备（本例中为 PictureBox）具有相同的调色板和分辨率
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

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CPICDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}




void CPICDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	CString filter = L"所有文件(*.bmp)|*.bmp|BMP(*.bmp)|*.bmp|";
	CFileDialog Ofile(TRUE, NULL, NULL, OFN_HIDEREADONLY, filter, NULL);

	if (IDOK == Ofile.DoModal()) {
		CString fPath = Ofile.GetPathName();       // 获取文件路径  
		CString fEnt = Ofile.GetFileExt(); // 获取文件扩展名  
		fEnt.MakeLower();                          // 将文件扩展名转化为小写字母  

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
		int cx = bminfo.biWidth; //得到图像宽度
		int cy = bminfo.biHeight; //得到图像高度
		CRect rect;
		GetDlgItem(IDC_STATIC)->GetWindowRect(&rect);

		ScreenToClient(&rect);
		CPICDlg::MoveWindow(rect.left, rect.top, cx + 50, cy + 100, true);

		GetDlgItem(IDC_STATIC)->MoveWindow(rect.left, rect.top, cx, cy, true);//调整大小
	}
	
}


void CPICDlg::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialog::OnCancel();
	
}
