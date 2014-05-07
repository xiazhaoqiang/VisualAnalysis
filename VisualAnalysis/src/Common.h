#pragma once

#include <string>
#include "cv.h"

typedef struct FrameInfo
{
	//const char *mediaFile;/*��Ƶ�ļ���*/
	std::string mediaFile; /*��Ƶ�ļ���*/
	int frameSeq; 	/*ͼ��֡���*/
	cv::Mat img;

	FrameInfo()
	:mediaFile("")
	{
		frameSeq = -1; 
		img = cv::Mat();
	}

}FrameInfo;


typedef struct SaveInfo
{
	//const char *mediaFile; /*��Ƶ�ļ���*/
	std::string mediaFile; /*��Ƶ�ļ���*/
	int type;		/*���������ͣ�0-������1-����2-����*/
	int frameSeq; 	/*ͼ��֡���*/
	int left;		/*Ŀ������x ����*/
	int top;		/*Ŀ������y ����*/
	int right;		/*Ŀ������X ����*/
	int bottom;		/*Ŀ������y ����*/
	int id;			/*����Ŀ��*/
	float score;

}SaveInfo;

typedef struct FaceRecogItem
{
public:
	FaceRecogItem()
	{
		img = cv::Mat();
		leftTopX = -1;
		leftTopY = -1;
		rightBottomX = -1;
		rightBottomY = -1;
	}
	~FaceRecogItem() {}

public:
	cv::Mat img;
	int leftTopX;
	int leftTopY;
	int rightBottomX;
	int rightBottomY;

}FaceRecogItem;



//������ֻ����дid��score����
class FaceRecogSaveInfo
{
public:
	FaceRecogSaveInfo()
	{
		
		id = "";
		score = 0.00;
		picName = "";
	}

public:
	std::string id;
	float score;
	std::string picName;
	std::string left;
	std::string right;
	std::string top;
	std::string bottom;
};