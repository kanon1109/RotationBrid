#include "ColorUtil.h"


ColorUtil::ColorUtil()
{
}


ColorUtil::~ColorUtil()
{
}

cocos2d::Color4F ColorUtil::getColor4F(int r, int g, int b, int a)
{
	Color4F c4f;
	c4f.r =  r / 255.f;
	c4f.g =  g / 255.f;
	c4f.b =  b / 255.f;
	c4f.a =  a / 255.f;
	return c4f;
}
