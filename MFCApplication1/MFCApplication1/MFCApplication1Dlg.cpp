
// MFCApplication1Dlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MFCApplication1.h"
#include "MFCApplication1Dlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

/***********************************����ȫ�ֱ���****************************/
FILE *fp = NULL;//�ļ�ָ��
BYTE *pBmpBuf;//������ָ��
CString fPath;//�ļ�·��
long bmpWidth;
long bmpHeight;
long linebyte;
long max;
int count[256];
void zhifangtu(float *tongji, BYTE *m_pData, long wid, long hei)
{
	int i;
	int j; int huidu[256]; //�Ҷȼ��� int wide,height; //ԭͼ������ //������ʼ��
	memset(huidu, 0, sizeof(huidu));
	long wide = wid;
	long height = hei;
	LPBYTE temp1 = new BYTE[wide*height]; //��ͼ�񻺳��� //����ԭͼ�񵽻��� ͼ��
	memcpy(temp1, m_pData, wide*height);
	for (i = 0; i<height; i++)
	{
		for (j = 0; j<wide; j++)
		{
			unsigned char temp = temp1[wide*i + j]; //�Ҷ�ͳ�Ƽ���
			huidu[temp]++;
		}
	} //����Ҷȷֲ��ܶ�
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
		count[bitmap[i]]++;  //ͳ��ֱ��ͼÿ���Ҷȼ����ֵĴ��� 
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
		//�������洢�ľ����ۼƵĹ�һ��ֱ��ͼ  
	}
	for (int i = 0; i < 256; i++)
	{
		new_color[i] = acum[i] * 255 / acum[255];
		//�����µĻҶȶ�Ӧ���� new_color[i]      
	}
	for (int i = 0; i < nr_pixels; i++)
	{

		bitmap[i] = new_color[bitmap[i]]; //�����е����ذ��վ��⻯�ĻҶȶ�Ӧ�������ת��

	}
	//printf("Enhancing the quality of the picture!\n");
	//return bitmap;
	//return count;
	return 0;
}
//void GrayEqualize(BYTE* pixel, BYTE* tempPixel, UINT width, UINT height)
//{
//
//	// �Ҷ�ӳ���  
//	BYTE map[256];
//	long lCounts[256];
//	
//
//	memset(lCounts, 0, sizeof(long) * 256);
//
//	// ������Ҷ�ֵ����  
//	for (UINT i = 0; i < width * height; i++)
//	{
//		int x = pixel[i * 3];
//		lCounts[x]++;
//	}
//
//	// ���������е���ʱֵ  
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
//	// �任���ֱֵ����ӳ����в���  
//	for (UINT b = 0; b < width * height; i++)
//	{
//		int x = pixel[b * 3];
//
//		tempPixel[b * 3] = tempPixel[b * 3+ 1] = map[x];
//		tempPixel[b * 3 + 2] = 255;
//	}
//}



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


// CMFCApplication1Dlg �Ի���



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


// CMFCApplication1Dlg ��Ϣ�������

BOOL CMFCApplication1Dlg::OnInitDialog()
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CMFCApplication1Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CMFCApplication1Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


/******************ͼ��򿪲���******************************************************/
void CMFCApplication1Dlg::OnBnClickedOk()
{
	
	CString filter = L"�����ļ�(*.bmp)|*.bmp|BMP(*.bmp)|*.bmp|";//�ļ�ɸѡ
	CFileDialog Ofile(TRUE, NULL, NULL, OFN_HIDEREADONLY, filter, NULL);//�ļ�ɸѡ����
	if (IDOK == Ofile.DoModal()) {
		 fPath = Ofile.GetPathName();       
		
		 int len = WideCharToMultiByte(CP_ACP, 0, fPath, -1, NULL, 0, NULL, NULL);
		 char *ptxtTemp = new char[len + 1];
		 WideCharToMultiByte(CP_ACP, 0, fPath, -1, ptxtTemp, len, NULL, NULL);
		 // ��ȡ�ļ�·��  
		fopen_s(&fp, ptxtTemp, "rb");//�Զ����ƴ��ļ�

		if (fp == 0)
		{
			return;
		}
		BITMAPFILEHEADER fileheader = { 0 };
		fread(&fileheader, sizeof(fileheader), 1, fp);//���ļ�ͷ
		if (fileheader.bfType != 0x4D42)
		{
			fclose(fp);
			return;
		}

		BITMAPINFOHEADER head;
		fread(&head, sizeof(BITMAPINFOHEADER), 1, fp);//���ļ�ͷ
		long bmpWidth = head.biWidth;//ͼ����ߡ�λ��
		long bmpHeight = head.biHeight;
		WORD biBitCount = head.biBitCount;
		if (biBitCount != 24)
		{
			::AfxMessageBox(_T("��ѡ��24λλͼ��"));
			fclose(fp);
			return;
		}
		int linebyte = (bmpWidth*biBitCount + 31) / 32 * 4;//һ���ֽ���
		pBmpBuf = new BYTE[linebyte*bmpHeight];//Ϊͼ�������ݷ����ڴ�ռ�

		
		fread(pBmpBuf, sizeof(char), linebyte*bmpHeight, fp);//��ȡ������

		int i, j;
		CDC* pDC = GetDlgItem(IDC_STATIC1)->GetDC();//��ȡ�ؼ�
		//////////////////��ʾ����
		for (i = bmpHeight; i >0 ; i--)
		{
			for (j = 0; j < bmpWidth; j++)
			{	
				DWORD clr = RGB(*(pBmpBuf + i* linebyte + j * 3 + 2), *(pBmpBuf + i* linebyte + j * 3 + 1), *(pBmpBuf + i* linebyte + j * 3 ));
				pDC->SetPixel(j, bmpHeight - i, clr);//�ڿؼ���ʾ
			}
		}
		delete[] pBmpBuf;
		pBmpBuf = NULL;
		return;
	}
}

/***************************************ͼ������*******************************/

void CMFCApplication1Dlg::OnBnClickedButton2()
{
	
	int len = WideCharToMultiByte(CP_ACP, 0, fPath, -1, NULL, 0, NULL, NULL);
	char *ptxtTemp = new char[len + 1];
	WideCharToMultiByte(CP_ACP, 0, fPath, -1, ptxtTemp, len, NULL, NULL);
	//��·������cstringתΪstring

	fopen_s(&fp, ptxtTemp, "rb");//�Զ����ƴ��ļ�

	if (fp == 0)
	{
		return;
	}
	BITMAPFILEHEADER fileheader = { 0 };
	fread(&fileheader, sizeof(fileheader), 1, fp);//���ļ�ͷ
	if (fileheader.bfType != 0x4D42)
	{
		fclose(fp);
		return;
	}

	BITMAPINFOHEADER head;
	fread(&head, sizeof(BITMAPINFOHEADER), 1, fp);//����Ϣͷ
	long bmpWidth = head.biWidth;
	long bmpHeight = head.biHeight;
	WORD biBitCount = head.biBitCount;
	if (biBitCount != 24)
	{
		::AfxMessageBox(_T("��ѡ��24λλͼ��"));
		fclose(fp);
		return;
	}
	int linebyte = (bmpWidth*biBitCount + 31) / 32 * 4;//һ���ֽ���
	pBmpBuf = new unsigned char[linebyte*bmpHeight];//Ϊ�����ݷ����ڴ�

	fread(pBmpBuf, sizeof(char), linebyte*bmpHeight, fp);//��ȡԭͼ��������
	Handle_bmp(pBmpBuf, linebyte*bmpHeight);
	//pBmpBuf = Handle_bmp(pBmpBuf, linebyte*bmpHeight);
	/////////////////ȥ��ɫ����
	//for (int i = 0; i < bmpHeight-1; ++i)
	//{
	//	for (int j = 0; j < bmpWidth-1; ++j)
	//	{
	//		int a = *(pBmpBuf + i*linebyte + j * 3);//��ȡÿ�е�һ������ֵ
	//		if (a == 255)//�ж��Ƿ�Ϊ����
	//		if(i>0&&j>0)
	//		{
	//			for (int k = 0; k < 3; k++)//1������ռ3���ֽ�,��˳��ֱ�ΪB,G,R
	//				*(pBmpBuf + i* linebyte + j * 3 + k) =
	//				(*(pBmpBuf + (i - 1)*linebyte + j * 3 + k) +
	//					*(pBmpBuf + (i + 1)*linebyte + j * 3 + k)) / 2;
	//			//��������Ԫֵƽ��ֵ���

	//		//	for (int k = 0; k<3; k++)
	//		//		*(pBmpBuf + i* linebyte + j * 3 + k) = 
	//		//		(*(pBmpBuf + i* linebyte + j * 3 + k)
	//		//		+*(pBmpBuf + (i - 1)*linebyte + j * 3 + k) + *(pBmpBuf + (i + 1)*linebyte + j * 3 + k)
	//		//		+*(pBmpBuf + i *linebyte + (j-1) * 3 + k)+*(pBmpBuf + i*linebyte + (j +1) * 3 + k)
	//		//		+ *(pBmpBuf + (i+1) *linebyte + (j + 1) * 3 + k) + *(pBmpBuf + (i+1)*linebyte + (j - 1) * 3 + k)
	//		//		+ *(pBmpBuf + (i-1) *linebyte + (j + 1) * 3 + k) + *(pBmpBuf + (i-1)*linebyte + (j - 1) * 3 + k)) / 9;
	//		//////////��ֵ�˲�9*9
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
	//��·������cstringתΪstring

	fopen_s(&fp, ptxtTemp, "rb");//�Զ����ƴ��ļ�

	if (fp == 0)
	{
		return;
	}
	BITMAPFILEHEADER fileheader = { 0 };
	fread(&fileheader, sizeof(fileheader), 1, fp);//���ļ�ͷ
	if (fileheader.bfType != 0x4D42)
	{
		fclose(fp);
		return;
	}

	BITMAPINFOHEADER head;
	fread(&head, sizeof(BITMAPINFOHEADER), 1, fp);//����Ϣͷ
	long bmpWidth = head.biWidth;
	long bmpHeight = head.biHeight;
	WORD biBitCount = head.biBitCount;
	if (biBitCount != 24)
	{
		::AfxMessageBox(_T("��ѡ��24λλͼ��"));
		fclose(fp);
		return;
	}
	int linebyte = (bmpWidth*biBitCount + 31) / 32 * 4;//һ���ֽ���
	pBmpBuf = new unsigned char[linebyte*bmpHeight];//Ϊ�����ݷ����ڴ�

	fread(pBmpBuf, sizeof(char), linebyte*bmpHeight, fp);//��ȡԭͼ��������
	Handle_bmp(pBmpBuf, linebyte*bmpHeight);
	CPaintDC dc(this); // device context for painting  

					   // TODO: Add your message handler code here  

					   /********************************************************************************/
					   /* �ص�֪ʶ:(�ٶ�)
					   /* �����View.cpp�а�һ��������ֵ���������Ի���
					   /*
					   /* ����һ:��View.h�ж����pubic����ֻ����View.cpp����
					   /* �����:����һ��Struct.h�д�ȫ�ֱ���,��2�������зֱ����#include "Struct.h"
					   /*
					   /* �������һ: (CSDN ����)������ A& a �����Ի����ﶼ���Է���a
					   /* ���������: (CSDN ����)����
					   /*
					   /* ���:��View.cpp�ж���ȫ�ֱ��� void CBmpDrawView::OnZftYt() ǰ�� �������в���
					   /*      ��dialog��cpp�м�void CTestZFTDlg::OnPaint()���ڶ���һ��extern int a
					   /********************************************************************************/

	 //int Red[256], Green[256], Blue[256];

	/*д�ڸÿռ��п���ʡ��Invalidate()���*/
	/*��ȡ�ؼ���CDCָ��*/
	CRect rectpic;
	GetDlgItem(IDC_STATIC3)->GetWindowRect(&rectpic);

	int x, y;
	x = rectpic.Width();
	y = rectpic.Height();

	CWnd *pWnd = GetDlgItem(IDC_STATIC3);
	CDC *pDC = pWnd->GetDC();

	/***********************/
	/*�ص�:��ֱ��ͼ ��ɫ
	/**********************/
	CPen *RedPen = new CPen();                              //�������ʶ���  
	RedPen->CreatePen(PS_SOLID, 1, RGB(255, 0, 0));           //��ɫ����  
	CGdiObject *RedOlderPen = pDC->SelectObject(RedPen);    //ѡ�е�ǰ��ɫ���ʲ�������ǰ�Ļ���  

															/*��ͼ*/
	pDC->Rectangle(9, 16, 312, 147);      //��һ�����ο�  
	pDC->MoveTo(15, 20);                //����������  
	pDC->LineTo(15, 128);               //Y����  
	pDC->LineTo(305, 128);              //X����  

	pDC->MoveTo(305, 128);              //����X��ͷ  
	pDC->LineTo(300, 123);              //�����ϱ߼�ͷ  
	pDC->MoveTo(305, 128);
	pDC->LineTo(300, 133);              //�����±߼�ͷ  

	pDC->MoveTo(15, 20);                //����Y��ͷ  
	pDC->LineTo(10, 25);                //������߼�ͷ  
	pDC->MoveTo(15, 20);
	pDC->LineTo(20, 25);                //�����ұ߼�ͷ  

										/**********************************************************************/
										/* TextOut��������:
										/* �ú����õ�ǰѡ������塢������ɫ��������ɫ��һ���ַ���д��ָ��λ��
										/* BOOL TextOut(HDC hdc,int x,int y,LPCTSTR str,int numStr)
										/* ��ʾ:x��ʼ����,y��ʼ����,�ַ���,�ַ������ַ�����
										/*
										/* SetTextColor��������:
										/* ����ָ���豸����(HDC)��������ɫ
										/* SetTextColor (HDC, COLORREF) ��:SetTextColor(HDC,RGB(255,0,0));
										/**********************************************************************/

	CString str;
	int i;
	for (i = 0; i <= 5; i++)                    //дX��̶���  
	{
		str.Format(_T("%d"), i * 50);               //0-255֮�����6���̶�ֵ  
		pDC->SetTextColor(RGB(255, 0, 255));   //����������ɫ  
		pDC->TextOut(15 + 48 * i, 130, str);       //�������  
		pDC->MoveTo(15 + 48 * i, 128);            //����X��̶�  
		pDC->LineTo(15 + 48 * i, 125);
	}
	for (i = 0; i <= 5; i++)                        //дY��̶���  
	{
		pDC->MoveTo(15, 128 - 20 * i);            //����Y��̶�  
		pDC->LineTo(18, 128 - 20 * i);
	}

	///*����ֱ��ͼ��Ҫ�Ĵ���*/
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}


void CMFCApplication1Dlg::OnBnClickedButton3()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int len = WideCharToMultiByte(CP_ACP, 0, fPath, -1, NULL, 0, NULL, NULL);
	char *ptxtTemp = new char[len + 1];
	WideCharToMultiByte(CP_ACP, 0, fPath, -1, ptxtTemp, len, NULL, NULL);
	//��·������cstringתΪstring

	fopen_s(&fp, ptxtTemp, "rb");//�Զ����ƴ��ļ�

	if (fp == 0)
	{
		return;
	}
	BITMAPFILEHEADER fileheader = { 0 };
	fread(&fileheader, sizeof(fileheader), 1, fp);//���ļ�ͷ
	if (fileheader.bfType != 0x4D42)
	{
		fclose(fp);
		return;
	}

	BITMAPINFOHEADER head;
	fread(&head, sizeof(BITMAPINFOHEADER), 1, fp);//����Ϣͷ
	long bmpWidth = head.biWidth;
	long bmpHeight = head.biHeight;
	WORD biBitCount = head.biBitCount;
	if (biBitCount != 24)
	{
		::AfxMessageBox(_T("��ѡ��24λλͼ��"));
		fclose(fp);
		return;
	}
	int linebyte = (bmpWidth*biBitCount + 31) / 32 * 4;//һ���ֽ���
	pBmpBuf = new unsigned char[linebyte*bmpHeight];//Ϊ�����ݷ����ڴ�

	fread(pBmpBuf, sizeof(char), linebyte*bmpHeight, fp);//��ȡԭͼ��������
	for (int i = 0; i < bmpHeight - 1; ++i)
	{
		for (int j = 0; j < bmpWidth - 1; ++j)
		{
			int a = *(pBmpBuf + i*linebyte + j * 3);//��ȡÿ�е�һ������ֵ
			if (a == 255)//�ж��Ƿ�Ϊ����
				if (i > 0 && j > 0)
				{
					for (int k = 0; k < 3; k++)//1������ռ3���ֽ�,��˳��ֱ�ΪB,G,R
						*(pBmpBuf + i* linebyte + j * 3 + k) =
						(*(pBmpBuf + (i - 1)*linebyte + j * 3 + k) +
							*(pBmpBuf + (i + 1)*linebyte + j * 3 + k)) / 2;
					//��������Ԫֵƽ��ֵ���
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
