
// MFCApplication1Dlg.cpp : 实现文件
//

#include "stdafx.h"
#include "MFCApplication1.h"
#include "MFCApplication1Dlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

/***********************************定义全局变量****************************/
FILE *fp = NULL;//文件指针
BYTE *pBmpBuf;//裸数据指针
CString fPath;//文件路径
long bmpWidth;
long bmpHeight;
long linebyte;
long max;
int count[256];
void zhifangtu(float *tongji, BYTE *m_pData, long wid, long hei)
{
	int i;
	int j; int huidu[256]; //灰度计数 int wide,height; //原图长、宽 //变量初始化
	memset(huidu, 0, sizeof(huidu));
	long wide = wid;
	long height = hei;
	LPBYTE temp1 = new BYTE[wide*height]; //新图像缓冲区 //复制原图像到缓存 图像
	memcpy(temp1, m_pData, wide*height);
	for (i = 0; i<height; i++)
	{
		for (j = 0; j<wide; j++)
		{
			unsigned char temp = temp1[wide*i + j]; //灰度统计计数
			huidu[temp]++;
		}
	} //计算灰度分布密度
	for (i = 0; i<256; i++)
		tongji[i] = huidu[i] / (height*wide*1.0f);
}

void fenbujunhenghua(BYTE *bitmap, long wid, long hei)
{
	long i;
	long j;
	float fps_R[256];
	float temp_r[256];
	int nNs_R[256];
	memset(temp_r, 0, sizeof(temp_r));
	LPBYTE p_data;
	p_data = bitmap;
	zhifangtu(fps_R, p_data, wid, hei);
	for (i = 0; i<256; i++)
	{
		if (i == 0)
		{
			temp_r[0] = fps_R[0];
		}
		else
		{
			temp_r[i] = temp_r[i - 1] + fps_R[i];
		}
		nNs_R[i] = (int)(255.0f*temp_r[i] + 0.5f);
	}
	LONG wide = wid;
	LONG height = hei;
	for (i = 0; i<height; i++)
	{
		for (j = 0; j<wide; j++)
		{
			unsigned char temp = *((unsigned char*)p_data + wide*i + j);
			*((unsigned char*)p_data + wide*i + j) = nNs_R[temp];
		}
	}
}



void *Handle_bmp(unsigned char* bitmap, int nr_pixels)
{
	
	int acum[256];

	unsigned char new_color[256];
	memset(count, 0, sizeof(count));  //count the num of the pixel , to count[]  
	for (int i = 0; i<nr_pixels; i++)
	{
		count[bitmap[i]]++;  //统计直方图每个灰度级出现的次数 
	}
	for (int i = 0; i < 256; i++)
	{
		if (count[i] > max)
			max = count[i];
	}
	memcpy(acum, count, sizeof(acum));
	for (int i = 1; i < 256; i++)
	{

		acum[i] += acum[i - 1];
		//这个数组存储的就是累计的归一化直方图  
	}
	for (int i = 0; i < 256; i++)
	{
		new_color[i] = acum[i] * 255 / acum[255];
		//定义新的灰度对应规则 new_color[i]      
	}
	for (int i = 0; i < nr_pixels; i++)
	{

		bitmap[i] = new_color[bitmap[i]]; //对所有的像素按照均衡化的灰度对应规则进行转换

	}
	//printf("Enhancing the quality of the picture!\n");
	//return bitmap;
	//return count;
	return 0;
}
//void GrayEqualize(BYTE* pixel, BYTE* tempPixel, UINT width, UINT height)
//{
//
//	// 灰度映射表  
//	BYTE map[256];
//	long lCounts[256];
//	
//
//	memset(lCounts, 0, sizeof(long) * 256);
//
//	// 计算各灰度值个数  
//	for (UINT i = 0; i < width * height; i++)
//	{
//		int x = pixel[i * 3];
//		lCounts[x]++;
//	}
//
//	// 保存运算中的临时值  
//	long lTemp;
//
//	for (int a = 0; a < 256; a++)
//	{
//		lTemp = 0;
//		for (int j = 0; j <= i; j++)
//			lTemp += lCounts[j];
//
//		map[a] = (BYTE)(lTemp * 255.0f / width / height);
//	}
//
//	// 变换后的值直接在映射表中查找  
//	for (UINT b = 0; b < width * height; i++)
//	{
//		int x = pixel[b * 3];
//
//		tempPixel[b * 3] = tempPixel[b * 3+ 1] = map[x];
//		tempPixel[b * 3 + 2] = 255;
//	}
//}



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


// CMFCApplication1Dlg 对话框



CMFCApplication1Dlg::CMFCApplication1Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_MFCAPPLICATION1_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCApplication1Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMFCApplication1Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CMFCApplication1Dlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTON2, &CMFCApplication1Dlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON1, &CMFCApplication1Dlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON3, &CMFCApplication1Dlg::OnBnClickedButton3)
END_MESSAGE_MAP()


// CMFCApplication1Dlg 消息处理程序

BOOL CMFCApplication1Dlg::OnInitDialog()
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

void CMFCApplication1Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CMFCApplication1Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CMFCApplication1Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


/******************图像打开部分******************************************************/
void CMFCApplication1Dlg::OnBnClickedOk()
{
	
	CString filter = L"所有文件(*.bmp)|*.bmp|BMP(*.bmp)|*.bmp|";//文件筛选
	CFileDialog Ofile(TRUE, NULL, NULL, OFN_HIDEREADONLY, filter, NULL);//文件筛选窗口
	if (IDOK == Ofile.DoModal()) {
		 fPath = Ofile.GetPathName();       
		
		 int len = WideCharToMultiByte(CP_ACP, 0, fPath, -1, NULL, 0, NULL, NULL);
		 char *ptxtTemp = new char[len + 1];
		 WideCharToMultiByte(CP_ACP, 0, fPath, -1, ptxtTemp, len, NULL, NULL);
		 // 获取文件路径  
		fopen_s(&fp, ptxtTemp, "rb");//以二进制打开文件

		if (fp == 0)
		{
			return;
		}
		BITMAPFILEHEADER fileheader = { 0 };
		fread(&fileheader, sizeof(fileheader), 1, fp);//读文件头
		if (fileheader.bfType != 0x4D42)
		{
			fclose(fp);
			return;
		}

		BITMAPINFOHEADER head;
		fread(&head, sizeof(BITMAPINFOHEADER), 1, fp);//读文件头
		long bmpWidth = head.biWidth;//图像宽、高、位深
		long bmpHeight = head.biHeight;
		WORD biBitCount = head.biBitCount;
		if (biBitCount != 24)
		{
			::AfxMessageBox(_T("请选择24位位图！"));
			fclose(fp);
			return;
		}
		int linebyte = (bmpWidth*biBitCount + 31) / 32 * 4;//一行字节数
		pBmpBuf = new BYTE[linebyte*bmpHeight];//为图像裸数据分配内存空间

		
		fread(pBmpBuf, sizeof(char), linebyte*bmpHeight, fp);//读取裸数据

		int i, j;
		CDC* pDC = GetDlgItem(IDC_STATIC1)->GetDC();//获取控件
		//////////////////显示部分
		for (i = bmpHeight; i >0 ; i--)
		{
			for (j = 0; j < bmpWidth; j++)
			{	
				DWORD clr = RGB(*(pBmpBuf + i* linebyte + j * 3 + 2), *(pBmpBuf + i* linebyte + j * 3 + 1), *(pBmpBuf + i* linebyte + j * 3 ));
				pDC->SetPixel(j, bmpHeight - i, clr);//在控件显示
			}
		}
		delete[] pBmpBuf;
		pBmpBuf = NULL;
		return;
	}
}

/***************************************图像处理部分*******************************/

void CMFCApplication1Dlg::OnBnClickedButton2()
{
	
	int len = WideCharToMultiByte(CP_ACP, 0, fPath, -1, NULL, 0, NULL, NULL);
	char *ptxtTemp = new char[len + 1];
	WideCharToMultiByte(CP_ACP, 0, fPath, -1, ptxtTemp, len, NULL, NULL);
	//将路径名由cstring转为string

	fopen_s(&fp, ptxtTemp, "rb");//以二进制打开文件

	if (fp == 0)
	{
		return;
	}
	BITMAPFILEHEADER fileheader = { 0 };
	fread(&fileheader, sizeof(fileheader), 1, fp);//读文件头
	if (fileheader.bfType != 0x4D42)
	{
		fclose(fp);
		return;
	}

	BITMAPINFOHEADER head;
	fread(&head, sizeof(BITMAPINFOHEADER), 1, fp);//读信息头
	long bmpWidth = head.biWidth;
	long bmpHeight = head.biHeight;
	WORD biBitCount = head.biBitCount;
	if (biBitCount != 24)
	{
		::AfxMessageBox(_T("请选择24位位图！"));
		fclose(fp);
		return;
	}
	int linebyte = (bmpWidth*biBitCount + 31) / 32 * 4;//一行字节数
	pBmpBuf = new unsigned char[linebyte*bmpHeight];//为裸数据分配内存

	fread(pBmpBuf, sizeof(char), linebyte*bmpHeight, fp);//读取原图像裸数据
	Handle_bmp(pBmpBuf, linebyte*bmpHeight);
	//pBmpBuf = Handle_bmp(pBmpBuf, linebyte*bmpHeight);
	/////////////////去白色条纹
	//for (int i = 0; i < bmpHeight-1; ++i)
	//{
	//	for (int j = 0; j < bmpWidth-1; ++j)
	//	{
	//		int a = *(pBmpBuf + i*linebyte + j * 3);//读取每列第一个像素值
	//		if (a == 255)//判断是否为条纹
	//		if(i>0&&j>0)
	//		{
	//			for (int k = 0; k < 3; k++)//1个像素占3个字节,按顺序分别为B,G,R
	//				*(pBmpBuf + i* linebyte + j * 3 + k) =
	//				(*(pBmpBuf + (i - 1)*linebyte + j * 3 + k) +
	//					*(pBmpBuf + (i + 1)*linebyte + j * 3 + k)) / 2;
	//			//用上下像元值平均值填充

	//		//	for (int k = 0; k<3; k++)
	//		//		*(pBmpBuf + i* linebyte + j * 3 + k) = 
	//		//		(*(pBmpBuf + i* linebyte + j * 3 + k)
	//		//		+*(pBmpBuf + (i - 1)*linebyte + j * 3 + k) + *(pBmpBuf + (i + 1)*linebyte + j * 3 + k)
	//		//		+*(pBmpBuf + i *linebyte + (j-1) * 3 + k)+*(pBmpBuf + i*linebyte + (j +1) * 3 + k)
	//		//		+ *(pBmpBuf + (i+1) *linebyte + (j + 1) * 3 + k) + *(pBmpBuf + (i+1)*linebyte + (j - 1) * 3 + k)
	//		//		+ *(pBmpBuf + (i-1) *linebyte + (j + 1) * 3 + k) + *(pBmpBuf + (i-1)*linebyte + (j - 1) * 3 + k)) / 9;
	//		//////////均值滤波9*9
	//		}
	//	}
	//}
	
	fclose(fp);

	int i, j;
	CDC* pDC = GetDlgItem(IDC_STATIC2)->GetDC();
	for (i = bmpHeight; i >0; i--)
	{
		for (j = 0; j < bmpWidth; j++)
		{

			DWORD clr = RGB(*(pBmpBuf + i* linebyte + j * 3 + 2), *(pBmpBuf + i* linebyte + j * 3 + 1), *(pBmpBuf + i* linebyte + j * 3));
			pDC->SetPixel(j, bmpHeight - i, clr);
		}
	}
	delete[] pBmpBuf;
	pBmpBuf = NULL;
	return;
}


void CMFCApplication1Dlg::OnBnClickedButton1()
{
	int len = WideCharToMultiByte(CP_ACP, 0, fPath, -1, NULL, 0, NULL, NULL);
	char *ptxtTemp = new char[len + 1];
	WideCharToMultiByte(CP_ACP, 0, fPath, -1, ptxtTemp, len, NULL, NULL);
	//将路径名由cstring转为string

	fopen_s(&fp, ptxtTemp, "rb");//以二进制打开文件

	if (fp == 0)
	{
		return;
	}
	BITMAPFILEHEADER fileheader = { 0 };
	fread(&fileheader, sizeof(fileheader), 1, fp);//读文件头
	if (fileheader.bfType != 0x4D42)
	{
		fclose(fp);
		return;
	}

	BITMAPINFOHEADER head;
	fread(&head, sizeof(BITMAPINFOHEADER), 1, fp);//读信息头
	long bmpWidth = head.biWidth;
	long bmpHeight = head.biHeight;
	WORD biBitCount = head.biBitCount;
	if (biBitCount != 24)
	{
		::AfxMessageBox(_T("请选择24位位图！"));
		fclose(fp);
		return;
	}
	int linebyte = (bmpWidth*biBitCount + 31) / 32 * 4;//一行字节数
	pBmpBuf = new unsigned char[linebyte*bmpHeight];//为裸数据分配内存

	fread(pBmpBuf, sizeof(char), linebyte*bmpHeight, fp);//读取原图像裸数据
	Handle_bmp(pBmpBuf, linebyte*bmpHeight);
	CPaintDC dc(this); // device context for painting  

					   // TODO: Add your message handler code here  

					   /********************************************************************************/
					   /* 重点知识:(百度)
					   /* 如何在View.cpp中把一个变量的值传给其它对话框
					   /*
					   /* 错误一:在View.h中定义的pubic变量只能在View.cpp中用
					   /* 错误二:定义一个Struct.h中存全局变量,在2个函数中分别调用#include "Struct.h"
					   /*
					   /* 解决方法一: (CSDN 不会)参数用 A& a 两个对话框里都可以访问a
					   /* 解决方法二: (CSDN 不会)重载
					   /*
					   /* 解决:在View.cpp中定义全局变量 void CBmpDrawView::OnZftYt() 前面 并函数中操作
					   /*      在dialog的cpp中即void CTestZFTDlg::OnPaint()中在定义一个extern int a
					   /********************************************************************************/

	 //int Red[256], Green[256], Blue[256];

	/*写在该空间中可以省略Invalidate()语句*/
	/*获取控件的CDC指针*/
	CRect rectpic;
	GetDlgItem(IDC_STATIC3)->GetWindowRect(&rectpic);

	int x, y;
	x = rectpic.Width();
	y = rectpic.Height();

	CWnd *pWnd = GetDlgItem(IDC_STATIC3);
	CDC *pDC = pWnd->GetDC();

	/***********************/
	/*重点:画直方图 红色
	/**********************/
	CPen *RedPen = new CPen();                              //创建画笔对象  
	RedPen->CreatePen(PS_SOLID, 1, RGB(255, 0, 0));           //红色画笔  
	CGdiObject *RedOlderPen = pDC->SelectObject(RedPen);    //选中当前红色画笔并保存以前的画笔  

															/*画图*/
	pDC->Rectangle(9, 16, 312, 147);      //画一个矩形框  
	pDC->MoveTo(15, 20);                //绘制坐标轴  
	pDC->LineTo(15, 128);               //Y竖轴  
	pDC->LineTo(305, 128);              //X横轴  

	pDC->MoveTo(305, 128);              //绘制X箭头  
	pDC->LineTo(300, 123);              //绘制上边箭头  
	pDC->MoveTo(305, 128);
	pDC->LineTo(300, 133);              //绘制下边箭头  

	pDC->MoveTo(15, 20);                //绘制Y箭头  
	pDC->LineTo(10, 25);                //绘制左边箭头  
	pDC->MoveTo(15, 20);
	pDC->LineTo(20, 25);                //绘制右边箭头  

										/**********************************************************************/
										/* TextOut函数功能:
										/* 该函数用当前选择的字体、背景颜色和正文颜色将一个字符串写到指定位置
										/* BOOL TextOut(HDC hdc,int x,int y,LPCTSTR str,int numStr)
										/* 表示:x起始坐标,y起始坐标,字符串,字符串中字符个数
										/*
										/* SetTextColor函数功能:
										/* 设置指定设备环境(HDC)的字体颜色
										/* SetTextColor (HDC, COLORREF) 如:SetTextColor(HDC,RGB(255,0,0));
										/**********************************************************************/

	CString str;
	int i;
	for (i = 0; i <= 5; i++)                    //写X轴刻度线  
	{
		str.Format(_T("%d"), i * 50);               //0-255之间添加6个刻度值  
		pDC->SetTextColor(RGB(255, 0, 255));   //设置字体颜色  
		pDC->TextOut(15 + 48 * i, 130, str);       //输出字体  
		pDC->MoveTo(15 + 48 * i, 128);            //绘制X轴刻度  
		pDC->LineTo(15 + 48 * i, 125);
	}
	for (i = 0; i <= 5; i++)                        //写Y轴刻度线  
	{
		pDC->MoveTo(15, 128 - 20 * i);            //绘制Y轴刻度  
		pDC->LineTo(18, 128 - 20 * i);
	}

	///*绘制直方图主要的代码*/
	for (i = 0; i<256; i++)
	{
		pDC->MoveTo(15 + i, 128);
		//if ((128 - 16) >(Red[i] / 40000000))
		//if(Red[i])
		unsigned long a = 128-(unsigned long)((float)count[i] / max*700);

		//int a = ((Red[i]/ max));
		//int a = 128 - (Red[i] / 10000000);
		//if(a>=16&&a<=128)
		pDC->LineTo(15 + i, a);
		//if(a<16)
		//	pDC->LineTo(15 + i, 16);
		//if(a>128)
		//	pDC->LineTo(15 + i, 128);
		//else
			//pDC->LineTo(15 + i, 16);
	}
	pDC->SelectObject(RedOlderPen);
	delete RedPen;
	return;
	// TODO: 在此添加控件通知处理程序代码
}


void CMFCApplication1Dlg::OnBnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码
	int len = WideCharToMultiByte(CP_ACP, 0, fPath, -1, NULL, 0, NULL, NULL);
	char *ptxtTemp = new char[len + 1];
	WideCharToMultiByte(CP_ACP, 0, fPath, -1, ptxtTemp, len, NULL, NULL);
	//将路径名由cstring转为string

	fopen_s(&fp, ptxtTemp, "rb");//以二进制打开文件

	if (fp == 0)
	{
		return;
	}
	BITMAPFILEHEADER fileheader = { 0 };
	fread(&fileheader, sizeof(fileheader), 1, fp);//读文件头
	if (fileheader.bfType != 0x4D42)
	{
		fclose(fp);
		return;
	}

	BITMAPINFOHEADER head;
	fread(&head, sizeof(BITMAPINFOHEADER), 1, fp);//读信息头
	long bmpWidth = head.biWidth;
	long bmpHeight = head.biHeight;
	WORD biBitCount = head.biBitCount;
	if (biBitCount != 24)
	{
		::AfxMessageBox(_T("请选择24位位图！"));
		fclose(fp);
		return;
	}
	int linebyte = (bmpWidth*biBitCount + 31) / 32 * 4;//一行字节数
	pBmpBuf = new unsigned char[linebyte*bmpHeight];//为裸数据分配内存

	fread(pBmpBuf, sizeof(char), linebyte*bmpHeight, fp);//读取原图像裸数据
	for (int i = 0; i < bmpHeight - 1; ++i)
	{
		for (int j = 0; j < bmpWidth - 1; ++j)
		{
			int a = *(pBmpBuf + i*linebyte + j * 3);//读取每列第一个像素值
			if (a == 255)//判断是否为条纹
				if (i > 0 && j > 0)
				{
					for (int k = 0; k < 3; k++)//1个像素占3个字节,按顺序分别为B,G,R
						*(pBmpBuf + i* linebyte + j * 3 + k) =
						(*(pBmpBuf + (i - 1)*linebyte + j * 3 + k) +
							*(pBmpBuf + (i + 1)*linebyte + j * 3 + k)) / 2;
					//用上下像元值平均值填充
				}
		}
	}
	int i, j;
	CDC* pDC = GetDlgItem(IDC_STATIC5)->GetDC();
	for (i = bmpHeight; i >0; i--)
	{
		for (j = 0; j < bmpWidth; j++)
		{

			DWORD clr = RGB(*(pBmpBuf + i* linebyte + j * 3 + 2), *(pBmpBuf + i* linebyte + j * 3 + 1), *(pBmpBuf + i* linebyte + j * 3));
			pDC->SetPixel(j, bmpHeight - i, clr);
		}
	}
	delete[] pBmpBuf;
	pBmpBuf = NULL;
	return;
}
