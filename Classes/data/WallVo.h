#pragma once
#ifndef _WALL_VO_
#define _WALL_VO_
#include "cocos2d.h"
USING_NS_CC;
class WallVo:public Node
{
public:
	WallVo();
	~WallVo();
	CREATE_FUNC(WallVo);
	//×ÝÏòËÙ¶È
	float vy;
};
#endif // !1
