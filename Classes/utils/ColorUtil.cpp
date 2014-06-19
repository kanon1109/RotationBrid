#include "ColorUtil.h"


ColorUtil::ColorUtil()
{
}


ColorUtil::~ColorUtil()
{
}

cocos2d::Color4F ColorUtil::getColor4F(int r, int g, int b, int a)
{
	Color4F c4f = { r / 255.f, g / 255.f, b / 255.f, a / 255.f };
	return c4f;
}
