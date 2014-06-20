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
	//纵向速度
	float vy;
	//横向缩放
	float scaleY;
	//最小scaleY范围
	float minRangeScaleY;
	//最大scaleY范围
	float maxRangeScaleY;
};
#endif // !1
