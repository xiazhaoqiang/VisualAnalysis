
// VisualAnalysisDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "VisualAnalysis.h"
#include "VisualAnalysisDlg.h"
#include "afxdialogex.h"
#include <vector>


#include "Test_ObjectsDetection.h"

using namespace std;


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
	, m_imgDir(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	// Initialize the class variables
	m_pImg = NULL;
	m_filePath = _T("�ļ�·��");
	// dongnanmeneast_15_1920x1080_30_R1
	m_imgDir = _T("E:\\Projects\\Dataset\\PKU-SVD-B_V2.0\\1_1_05(06)_0\\prob\\dongnanmeneast_15_1920x1080_30_R1");
}

void CVisualAnalysisDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_STATIC_FILEPATH, m_filePath);
	DDX_Control(pDX, IDC_PROGRESS_IMG, m_ctrlProcess);
}

BEGIN_MESSAGE_MAP(CVisualAnalysisDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_OPENFILE, &CVisualAnalysisDlg::OnBnClickedBtnOpenfile)
	ON_BN_CLICKED(IDC_BTN_PEDDETECTION, &CVisualAnalysisDlg::OnBnClickedBtnPeddetection)
	ON_BN_CLICKED(IDC_BTN_FACEDETECTION_S, &CVisualAnalysisDlg::OnBnClickedBtnFacedetectionSingle)
	ON_BN_CLICKED(IDCANCEL, &CVisualAnalysisDlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_BTN_FACEDETECTION_M, &CVisualAnalysisDlg::OnBnClickedBtnFacedetectionMultiple)
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
	GetDlgItem(IDC_BTN_PEDDETECTION)->EnableWindow(FALSE);
	GetDlgItem(IDC_BTN_FACEDETECTION_S)->EnableWindow(FALSE);

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

void CVisualAnalysisDlg::CreateXMLFile(char* taskType)
{
	// create a xml file for saving detection reuslts
	int type;
	if(taskType == "fd"){type = 0;}

	int pos = m_imgDir.ReverseFind('\\');
	CString metaFile = m_imgDir.Right(m_imgDir.GetLength()-1-pos);
	CString xmlName = _T(".\\Result\\") + metaFile + _T("_") + taskType + _T(".xml");
	TiXmlDocument* xmlDocument = new TiXmlDocument();	//����һ�������
	TiXmlDeclaration* xmlDeclaration=new TiXmlDeclaration("1.0","gb2312","");	//����xml�ļ�ͷ
	xmlDocument->LinkEndChild(xmlDeclaration);	//�����ļ�ͷ
	
	// ����xml meta��Ϣ
	TiXmlElement* messageNode = new TiXmlElement("Message");	//�������ڵ�
	messageNode->SetAttribute("Version","1.0");
	xmlDocument->LinkEndChild(messageNode);

	TiXmlElement* infoNode = new TiXmlElement("Info");
	infoNode->SetAttribute("evaluateType",type);
	infoNode->SetAttribute("mediaFile",(LPSTR)(LPCTSTR)metaFile);
	messageNode->LinkEndChild(infoNode);

	//TiXmlElement* itemsNode = new TiXmlElement("Items");
	//messageNode->LinkEndChild(itemsNode);

	// д���ļ�
	xmlDocument->SaveFile((LPSTR)(LPCTSTR)xmlName);
	// �ͷ��ڴ�
	delete xmlDocument;
	//delete xmlDeclaration;
	xmlDocument = NULL;
	//xmlDeclaration = NULL;
}


void CVisualAnalysisDlg::SaveDetectionResults(vector<CvRect>* r, CString mediaFile, TiXmlElement* itemsNode, int type)
{
	TiXmlElement* itemNode = new TiXmlElement("Item");
	itemNode->SetAttribute("imageName",(LPSTR)(LPCTSTR)mediaFile);
	itemsNode->LinkEndChild(itemNode);

	int len = r->size();
	CvRect* face;
	for(int i=0;i<len;i++)
	{
		face = &(r->at(i));
		TiXmlElement* labelNode = new TiXmlElement("Label");
		labelNode->SetAttribute("type",type);
		labelNode->SetAttribute("l",face->x);
		labelNode->SetAttribute("t",face->y);
		labelNode->SetAttribute("r",face->x+face->width);
		labelNode->SetAttribute("b",face->y+face->height);
		itemNode->LinkEndChild(labelNode);
	}
	//xml_DetectionResults("fd",infoResults,"ppx_fd.xml",1);

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
		m_filePath = filepath;
	}
	else return;
 
    //����ͼ��
	if(m_pImg != NULL){
		cvReleaseImage(&m_pImg);
		m_pImg = NULL;
	}
    if( (m_pImg = cvLoadImage((LPSTR)(LPCTSTR)filepath, 1)) != 0 )//[[�˴���argc==2�Ƿ���Ҫ�ĳ�argc==1���Ҹ���֮��������гɹ������ţ���]] //  wmzzzz : ��"����"|"debug"|���command arguments ��������(һ��·��:Ҫ�򿪵��ļ�·��) ��ʱ argc==2 �ͺ�����...�������Զ�Ӽ���
    {
		DrawImgtoHDC(m_pImg,IDC_SHOWIMG);
		GetDlgItem(IDC_BTN_PEDDETECTION)->EnableWindow(TRUE);
		GetDlgItem(IDC_BTN_FACEDETECTION_S)->EnableWindow(TRUE);
		UpdateData(FALSE);
    }
 
	return;
}



void CVisualAnalysisDlg::OnBnClickedBtnPeddetection()
{
	// TODO: Add your control notification handler code here
	IplImage * pImg = cvCloneImage(m_pImg);
	m_od.DetectPedestrian(pImg);
	DrawImgtoHDC(pImg,IDC_SHOWIMG);
}


void CVisualAnalysisDlg::OnBnClickedBtnFacedetectionSingle()
{
	// TODO: Add your control notification handler code here
	IplImage * pImg = cvCloneImage(m_pImg);
	m_od.DetectFace(pImg);
	DrawImgtoHDC(pImg,IDC_SHOWIMG);
}


void CVisualAnalysisDlg::OnBnClickedCancel()
{
	// TODO: Add your control notification handler code here
	CDialogEx::OnCancel();
}


void CVisualAnalysisDlg::OnBnClickedBtnFacedetectionMultiple()
{
	// TODO: Add your control notification handler code here
	GetDlgItem(IDC_BTN_FACEDETECTION_M)->EnableWindow(FALSE);

	// generate a folder for the detection results
	if(!PathIsDirectory(_T(".\\Result"))){CreateDirectory(_T(".\\Result"),NULL);};
	CreateXMLFile("fd");

	// check the formatting of  image directory
	int pos = m_imgDir.ReverseFind('\\');
	CString imgPath;
	CString xmlName = m_imgDir.Right(m_imgDir.GetLength()-1-pos);
	xmlName = _T(".\\Result\\") + xmlName + _T("_fd.xml");
	// load xml file
	TiXmlDocument* xmlDocument = new TiXmlDocument((LPSTR)(LPCTSTR)xmlName);
	xmlDocument->LoadFile();
	TiXmlElement * messageNode = xmlDocument->FirstChildElement();
	TiXmlElement* itemsNode = new TiXmlElement("Items");
	messageNode->LinkEndChild(itemsNode);
	
	if(m_imgDir.Right(1) != "\\"){m_imgDir = m_imgDir + "\\";}
	imgPath = m_imgDir + "*.jpg";
	// define a CFileFind class to search images
	CFileFind fileFinder;
	// obtain the total number of images in a directory
	BOOL isAll = fileFinder.FindFile(imgPath);
	int totalNum = 0;
	while(isAll)
	{
		isAll = fileFinder.FindNextFile();
		totalNum ++;
	}
	fileFinder.Close();
	m_ctrlProcess.SetRange(0,totalNum);
	m_ctrlProcess.SetPos(0);

	// detect faces image-by-image
	IplImage * pImg = NULL;
	CString imgName;
	isAll = fileFinder.FindFile(imgPath);
	int i = 0;
	vector<CvRect> faces;
	// traversing the whole folder
	while(isAll)
	{
		isAll = fileFinder.FindNextFile();
		imgPath = fileFinder.GetFilePath();
		imgName = fileFinder.GetFileName();
		m_filePath = imgPath + _T("\r\n");
		if( (pImg = cvLoadImage((LPSTR)(LPCTSTR)imgPath, 1)) != 0 )//
		{
			// detect faces
			m_od.DetectFace(pImg,&faces);
			// save the detection results
			imgPath = _T(".\\Result\\") + imgName;
			//cvSaveImage((LPSTR)(LPCTSTR)imgPath,pImg);
			SaveDetectionResults(&faces,imgName,itemsNode,0);
			cvReleaseImage(&pImg);
			pImg = NULL;
			// update the display of UI:processing bar
			i++;
			m_ctrlProcess.SetPos(i);
			UpdateData(FALSE);
		}
		faces.clear();
		xmlDocument->SaveFile((LPSTR)(LPCTSTR)xmlName);
	}
	fileFinder.Close();
	// �ͷ��ڴ�
	delete xmlDocument;
	xmlDocument = NULL;

	GetDlgItem(IDC_BTN_FACEDETECTION_M)->EnableWindow(TRUE);
}

