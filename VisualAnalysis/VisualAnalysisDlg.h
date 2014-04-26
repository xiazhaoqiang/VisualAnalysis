
// VisualAnalysisDlg.h : ͷ�ļ�
//

#pragma once

#include "cv.h"
#include "highgui.h"
#include "src\CvvImage.h"

// CVisualAnalysisDlg �Ի���
class CVisualAnalysisDlg : public CDialogEx
{
// ����
public:
	CVisualAnalysisDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_VISUALANALYSIS_DIALOG };

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
	afx_msg void OnBnClickedBtnOpenfile();
	// Draw image to the HDC of a picture control
	void DrawImgtoHDC(IplImage * img, UINT ID);
private:
	// A pointer to an image
	IplImage* m_pImg;
};
