#pragma once
#ifndef _SCREEN_UTIL_
#define _SCREEN_UTIL_
#include "cocos2d.h"
USING_NS_CC;
#define sc() ScreenUtil::getCenter()
#define sl() ScreenUtil::getLeft()
#define sr() ScreenUtil::getRight()
#define sb() ScreenUtil::getBottom()
#define st() ScreenUtil::getTop()
#define slt() ScreenUtil::getLeftTop()
#define srt() ScreenUtil::getRightTop()
#define slb() ScreenUtil::getLeftBottom()
#define srb() ScreenUtil::getRightBottom()
#define gsp(__X__,__Y__) ScreenUtil::getScreenPoint((float)(__X__), (float)(__Y__))
#define gsx(__X__) ScreenUtil::getScreenX((float)(__X__))
#define gsy(__Y__) ScreenUtil::getScreenY((float)(__Y__))
class ScreenUtil
{
public:
	ScreenUtil();
	~ScreenUtil();
	/**
	* ������Ļ��С
	* @width	��Ļ�ο����
	* @height	��Ļ�ο��߶�
	*/
	static void setScreenSize(float width = 960, float height = 640, bool isFixHeight = true);

	/*��Ļ���ĵ����*/
	static Point getCenter();

	/*��Ļ���Ͻ����*/
	static Point getLeftTop();

	/*��Ļ���½����*/
	static Point getLeftBottom();

	/*��Ļ���Ͻ����*/
	static Point getRightTop();
	
	/*��Ļ���½����*/
	static Point getRightBottom();

	static float getLeft();

	static float getRight();

	static float getBottom();

	static float getTop();

	//************************************
	// Method:    �����豸�ο���С���������㵱ǰ�豸��Ļ������
	// Parameter: float x				x����
	// Parameter: float y				y����
	// Returns:   cocos2d::Point		����������
	//************************************
	static Point getScreenPoint(float x, float y);
	//************************************
	// Method:    �����豸�ο���С���������㵱ǰ�豸��Ļ��x����
	// Parameter: float x	x����
	// Returns:   float		������x����
	//************************************
	static float getScreenX(float x);
	//************************************
	// Method:    �����豸�ο���С���������㵱ǰ�豸��Ļ��y����
	// Parameter: float y	y����
	// Returns:   float		������y����
	//************************************
	static float getScreenY(float y);

	//��ȡ��Ļ���
	static float getScreenWidth();

	//��ȡ��Ļ�߶�
	static float getScreenHeight();
};
#endif
