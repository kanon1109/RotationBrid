#pragma once
#ifndef _BIRD_VO_
#define _BIRD_VO_
#include "cocos2d.h"
USING_NS_CC;
class BirdVo :public Node
{
public:
	BirdVo(void);
	~BirdVo(void);
	CREATE_FUNC(BirdVo);
	//更新
	void update();
	//坐标
	float x;
	float y;
	//速度
	float vx;
	float vy;
	//重力
	float g;
	//角度
	float angle;
	//跳跃
	void jump();
	//处于区域的索引
	int areaIndex;
};

#endif // !1
