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
	// Description:根据16进制参数获取一个Color4F对象
	// Parameter: int r		红色通道
	// Parameter: int g		绿色通道
	// Parameter: int b		蓝色通道
	// Parameter: int a		透明度通道
	// Returns:   cocos2d::Color4F
	//************************************
	static Color4F getColor4F(int r, int g, int b, int a);
};
#endif
