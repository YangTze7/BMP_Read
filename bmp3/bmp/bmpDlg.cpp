
// bmpDlg.cpp : ʵ���ļ�
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
BITMAPINFO *pBmpInfo;          // ��¼ͼ����Ϣ  
BITMAPINFO *pBmpInfo2;
DWORD dataBytes;
BYTE *pBmpData;                // ͼ������  
BYTE *pBmpData2;
BITMAPFILEHEADER bmpHeader;    // �ļ�ͷ  
BITMAPFILEHEADER bmpHeader2;
BITMAPINFOHEADER bmpInfo;      // ��Ϣͷ  
BITMAPINFOHEADER bmpInfo2;
int linebyte;
CFile bmpFile; // ��������洢ͼƬ��Ϣ 
CFile bmpFile2;
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


// CbmpDlg �Ի���



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


// CbmpDlg ��Ϣ�������

BOOL CbmpDlg::OnInitDialog()
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

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CbmpDlg::OnPaint()
{
	
		CWnd *pwnd = GetDlgItem(IDC_STATIC_PIC);
		CWnd *pwnd2 = GetDlgItem(IDC_STATIC_PIC2);
		CRect rect;
		CRect rect2;
		pwnd->GetClientRect(&rect);
		pwnd->GetClientRect(&rect2);
		CDC *pDC = pwnd->GetDC();// ��ȡpicture�ؼ����ڵ�λ�� 
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

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CbmpDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CbmpDlg::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//CDialogEx::OnOK();
    filter = L"�����ļ�(*.bmp)|*.bmp|BMP(*.bmp)|*.bmp|";
	CFileDialog Ofile(TRUE, NULL, NULL, OFN_HIDEREADONLY, filter, NULL);

	if (IDOK == Ofile.DoModal()) {
		fPath = Ofile.GetPathName();       // ��ȡ�ļ�·��  
		CString fEnt = Ofile.GetFileExt();         // ��ȡ�ļ���չ��  
		fEnt.MakeLower();                          // ���ļ���չ��ת��ΪСд��ĸ  

		if (fEnt.Compare(_T("bmp")) == 0) {        // ����򿪵���bmp�ļ�  
												   // ��ֻ���ķ�ʽ���ļ� ��ȡbmpͼƬ������bmp���ļ�ͷ����Ϣ������  
			if (!bmpFile.Open(fPath, CFile::modeRead | CFile::typeBinary))
				return;
			if (bmpFile.Read(&bmpHeader, sizeof(BITMAPFILEHEADER)) != sizeof(BITMAPFILEHEADER))
				return;
			if (bmpFile.Read(&bmpInfo, sizeof(BITMAPINFOHEADER)) != sizeof(BITMAPINFOHEADER))
				return;
			pBmpInfo = (BITMAPINFO*)new char[sizeof(BITMAPINFOHEADER)];
			int linebyte = (bmpInfo.biWidth* 24 / 8 + 3) / 4 * 4;
			// Ϊͼ����������ռ�  
			memcpy(pBmpInfo, &bmpInfo, sizeof(BITMAPINFOHEADER));
			dataBytes = bmpHeader.bfSize - bmpHeader.bfOffBits;
			pBmpData = (BYTE*)new char[dataBytes];

			bmpFile.Read(pBmpData, dataBytes);
			int nImageSize = pBmpInfo->bmiHeader.biSizeImage;
			bmpFile.Close();
			//

			// ��ʾͼ��  
			
		}
	}

}


void CbmpDlg::OnBnClickedButton1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
						for (int k = 0; k < 3; k++)//1������ռ3���ֽ�,��˳��ֱ�ΪB,G,R
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}
