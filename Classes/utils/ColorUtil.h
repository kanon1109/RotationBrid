#pragma once
#ifndef _COLOR_UTIL_
#define _COLOR_UTIL_
#include "cocos2d.h"
USING_NS_CC;
class ColorUtil
{
public:
	ColorUtil();
	~ColorUtil();

	//************************************
	// Description:����16���Ʋ�����ȡһ��Color4F����
	// Parameter: int r		��ɫͨ��
	// Parameter: int g		��ɫͨ��
	// Parameter: int b		��ɫͨ��
	// Parameter: int a		͸����ͨ��
	// Returns:   cocos2d::Color4F
	//************************************
	static Color4F getColor4F(int r, int g, int b, int a);
};
#endif
