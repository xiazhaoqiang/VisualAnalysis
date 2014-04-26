
// VisualAnalysisDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "VisualAnalysis.h"
#include "VisualAnalysisDlg.h"
#include "afxdialogex.h"
//#include "opencv.hpp"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//using namespace cv;	// opencv2.x usage

// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CVisualAnalysisDlg �Ի���




CVisualAnalysisDlg::CVisualAnalysisDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CVisualAnalysisDlg::IDD, pParent)
	, m_pImg(NULL)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CVisualAnalysisDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CVisualAnalysisDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_OPENFILE, &CVisualAnalysisDlg::OnBnClickedBtnOpenfile)
END_MESSAGE_MAP()


// CVisualAnalysisDlg ��Ϣ�������

BOOL CVisualAnalysisDlg::OnInitDialog()
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

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CVisualAnalysisDlg::OnSysCommand(UINT nID, LPARAM lParam)
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
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CVisualAnalysisDlg::OnPaint()
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
HCURSOR CVisualAnalysisDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

// Draw image to the HDC of a picture control
void CVisualAnalysisDlg::DrawImgtoHDC(IplImage * img, UINT ID)
{
	// get a dc
	CDC* pDC = GetDlgItem(ID)->GetDC();
	HDC hDC = pDC->GetSafeHdc();
	CRect rect;
	GetDlgItem(ID)->GetClientRect(&rect);
	CvvImage cvImg;
	cvImg.CopyOf(img);
	cvImg.DrawToHDC(hDC,&rect);
	ReleaseDC(pDC);
}

/****************** ��Ϣ��Ӧ���� **********************/
void CVisualAnalysisDlg::OnBnClickedBtnOpenfile()
{
	// TODO: Add your control notification handler code here
	// Open File Dialog
	CString filepath;
	CFileDialog dlg( TRUE, _T(".jpg"), NULL, OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST | OFN_HIDEREADONLY,
		_T("image files (*.bmp; *.jpg) |*.bmp;*.jpg| All Files (*.*) |*.*||"), NULL );
	dlg.m_ofn.lpstrTitle = _T("Load Image"); 
	if( dlg.DoModal() == IDOK )
	{
		filepath = dlg.GetPathName();
	}
	else return;
 
    //����ͼ��
    if( (m_pImg = cvLoadImage((LPSTR)(LPCTSTR)filepath, 1)) != 0 )//[[�˴���argc==2�Ƿ���Ҫ�ĳ�argc==1���Ҹ���֮��������гɹ������ţ���]] //  wmzzzz : ��"����"|"debug"|���command arguments ��������(һ��·��:Ҫ�򿪵��ļ�·��) ��ʱ argc==2 �ͺ�����...�������Զ�Ӽ���
    {
		DrawImgtoHDC(m_pImg,IDC_SHOWIMG);
    }
 
	return;
}

