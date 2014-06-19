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
	//高度
	float height;
	//宽度
	float width;
	//纵向速度
	float vy;
};
#endif // !1
