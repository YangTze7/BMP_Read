
// bmpDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "bmp.h"
#include "bmpDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
CString filter;
CString fPath;
//CFileDialog Ofile(TRUE, NULL, NULL, OFN_HIDEREADONLY, filter, NULL);
BITMAPINFO *pBmpInfo;          // 记录图像信息  
BITMAPINFO *pBmpInfo2;
DWORD dataBytes;
BYTE *pBmpData;                // 图像数据  
BYTE *pBmpData2;
BITMAPFILEHEADER bmpHeader;    // 文件头  
BITMAPFILEHEADER bmpHeader2;
BITMAPINFOHEADER bmpInfo;      // 信息头  
BITMAPINFOHEADER bmpInfo2;
int linebyte;
CFile bmpFile; // 定义变量存储图片信息 
CFile bmpFile2;
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


// CbmpDlg 对话框



CbmpDlg::CbmpDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_BMP_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CbmpDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CbmpDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CbmpDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTON1, &CbmpDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CbmpDlg::OnBnClickedButton2)
END_MESSAGE_MAP()


// CbmpDlg 消息处理程序

BOOL CbmpDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

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

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CbmpDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CbmpDlg::OnPaint()
{
	
		CWnd *pwnd = GetDlgItem(IDC_STATIC_PIC);
		CWnd *pwnd2 = GetDlgItem(IDC_STATIC_PIC2);
		CRect rect;
		CRect rect2;
		pwnd->GetClientRect(&rect);
		pwnd->GetClientRect(&rect2);
		CDC *pDC = pwnd->GetDC();// 获取picture控件所在的位置 
		CDC *pDC2 = pwnd2->GetDC();
		pDC->SetStretchBltMode(COLORONCOLOR);
		pDC2->SetStretchBltMode(COLORONCOLOR);
		StretchDIBits(pDC->GetSafeHdc(), 0, 0, rect.Width(), rect.Height()
			, 0, 0, bmpInfo.biWidth, bmpInfo.biHeight, pBmpData, pBmpInfo
			, DIB_RGB_COLORS, SRCCOPY);
		StretchDIBits(pDC2->GetSafeHdc(), 0, 0, rect2.Width(), rect2.Height()
			, 0, 0, bmpInfo2.biWidth, bmpInfo2.biHeight, pBmpData2, pBmpInfo2
			, DIB_RGB_COLORS, SRCCOPY);

	
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CbmpDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CbmpDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	//CDialogEx::OnOK();
    filter = L"所有文件(*.bmp)|*.bmp|BMP(*.bmp)|*.bmp|";
	CFileDialog Ofile(TRUE, NULL, NULL, OFN_HIDEREADONLY, filter, NULL);

	if (IDOK == Ofile.DoModal()) {
		fPath = Ofile.GetPathName();       // 获取文件路径  
		CString fEnt = Ofile.GetFileExt();         // 获取文件扩展名  
		fEnt.MakeLower();                          // 将文件扩展名转化为小写字母  

		if (fEnt.Compare(_T("bmp")) == 0) {        // 如果打开的是bmp文件  
												   // 以只读的方式打开文件 读取bmp图片个部分bmp的文件头，信息和数据  
			if (!bmpFile.Open(fPath, CFile::modeRead | CFile::typeBinary))
				return;
			if (bmpFile.Read(&bmpHeader, sizeof(BITMAPFILEHEADER)) != sizeof(BITMAPFILEHEADER))
				return;
			if (bmpFile.Read(&bmpInfo, sizeof(BITMAPINFOHEADER)) != sizeof(BITMAPINFOHEADER))
				return;
			pBmpInfo = (BITMAPINFO*)new char[sizeof(BITMAPINFOHEADER)];
			int linebyte = (bmpInfo.biWidth* 24 / 8 + 3) / 4 * 4;
			// 为图像数据申请空间  
			memcpy(pBmpInfo, &bmpInfo, sizeof(BITMAPINFOHEADER));
			dataBytes = bmpHeader.bfSize - bmpHeader.bfOffBits;
			pBmpData = (BYTE*)new char[dataBytes];

			bmpFile.Read(pBmpData, dataBytes);
			int nImageSize = pBmpInfo->bmiHeader.biSizeImage;
			bmpFile.Close();
			//

			// 显示图像  
			
		}
	}

}


void CbmpDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	// TODO: 在此添加控件通知处理程序代码
	//CDialogEx::OnOK();
	
			//if (!bmpFile2.Open(fPath, CFile::modeRead | CFile::typeBinary))
			//	return;
			//if (bmpFile2.Read(&bmpHeader2, sizeof(BITMAPFILEHEADER)) != sizeof(BITMAPFILEHEADER))
			//	return;
			//if (bmpFile2.Read(&bmpInfo2, sizeof(BITMAPINFOHEADER)) != sizeof(BITMAPINFOHEADER))
			//	return;
			//pBmpInfo2 = (BITMAPINFO*)new char[sizeof(BITMAPINFOHEADER)];
			//int linebyte = (bmpInfo2.biWidth * 24 / 8 + 3) / 4 * 4;
			//memcpy(pBmpInfo2, &bmpInfo2, sizeof(BITMAPINFOHEADER));
			////DWORD dataBytes2 = bmpHeader2.bfSize - bmpHeader2.bfOffBits;
			//pBmpData2 = (BYTE*)new char[dataBytes];

			bmpFile.Read(pBmpData2, dataBytes);
			for (int i = 0; i < bmpInfo.biHeight; ++i)
			{
				for (int j = 0; j < bmpInfo.biWidth; ++j)
				{
					int a = *(pBmpData2 + i*linebyte + j * 3);
					if (a == 255)
					{
						for (int k = 0; k < 3; k++)//1个像素占3个字节,按顺序分别为B,G,R
							*(pBmpData2 + i* linebyte + j * 3 + k) =
							(*(pBmpData2 + (i - 1)*linebyte + j * 3 + k) +
								*(pBmpData2 + (i + 1)*linebyte + j * 3 + k)) / 2;
					}
				}
			}
			
			//int nImageSize2 = pBmpInfo2->bmiHeader.biSizeImage;
			bmpFile2.Close();
}


void CbmpDlg::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
}
