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
	* 设置屏幕大小
	* @width	屏幕参考宽度
	* @height	屏幕参考高度
	*/
	static void setScreenSize(float width = 960, float height = 640, bool isFixHeight = true);

	/*屏幕中心点左边*/
	static Point getCenter();

	/*屏幕左上角左边*/
	static Point getLeftTop();

	/*屏幕左下角左边*/
	static Point getLeftBottom();

	/*屏幕右上角左边*/
	static Point getRightTop();
	
	/*屏幕右下角左边*/
	static Point getRightBottom();

	static float getLeft();

	static float getRight();

	static float getBottom();

	static float getTop();

	//************************************
	// Method:    根据设备参考大小按比例计算当前设备屏幕的坐标
	// Parameter: float x				x坐标
	// Parameter: float y				y坐标
	// Returns:   cocos2d::Point		计算后的坐标
	//************************************
	static Point getScreenPoint(float x, float y);
	//************************************
	// Method:    根据设备参考大小按比例计算当前设备屏幕的x坐标
	// Parameter: float x	x坐标
	// Returns:   float		计算后的x坐标
	//************************************
	static float getScreenX(float x);
	//************************************
	// Method:    根据设备参考大小按比例计算当前设备屏幕的y坐标
	// Parameter: float y	y坐标
	// Returns:   float		计算后的y坐标
	//************************************
	static float getScreenY(float y);

	//获取屏幕宽度
	static float getScreenWidth();

	//获取屏幕高度
	static float getScreenHeight();
};
#endif
