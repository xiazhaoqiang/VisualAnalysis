/**************************************************************
* Type: .h file
* Class Name: CObjectDetection
* Function: detect objects in an image, such as pedestrian, face and son
* Create date: 2014.4.26
* Creator�� Zhaoqiang Xia (xiazhaoqiang@gmail.com)
***************************************************************/
#pragma once

#include <opencv2/opencv.hpp> 
#include <vector>
#include <string>

using namespace cv;
using namespace std;

// construct a color table for displaying
static CvScalar colors[ ] = {
        {{0,0,255}},
        {{0,128,255}},
        {{0,255,255}},
        {{0,255,0}},
        {{255,128,0}},
        {{255,255,0}},
        {{255,0,0}},
        {{255,0,255}}
    };

class CObjectDetection
{
private:

public:
	CObjectDetection();
	void DetectPedestrian(IplImage * pImg, vector<CvRect>* peopleRegion = NULL);	// detect pedestrian
	void DetectFace(IplImage* pImg, vector<CvRect>* faceRegion = NULL);		// detect face
	void TrainModelFR(vector<Mat>& imgMats, vector<int>& labelMats, string recMethod = "FisherFace");
	double predictFR(vector<Mat>& imgMats, vector<int>& labelMats, string recMethod = "FisherFace");
	void NormalizeDataset(vector<string> imgDirs, vector<string> labelFiles, char* taskName = NULL);
	double scaling;	// ͼ������ϵ��
	double pyramidCoef;	// ������ͼ������ű���
	double SkinColorModelFilter(Mat& faceRect);
	CvHaarClassifierCascade* frontalFaceCascade;
	CvHaarClassifierCascade* bodyCascade;
	HOGDescriptor hog;
	int hogType; /*hogType:0-None;1-human*/
};
