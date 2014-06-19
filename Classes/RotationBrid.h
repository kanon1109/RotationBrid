#pragma once
#ifndef _ROTATION_BRID_
#define _ROTATION_BRID_
#include "data/BirdVo.h"
#include "cocos2d.h"
USING_NS_CC;
class RotationBrid:public Node
{
public:
	RotationBrid();
	~RotationBrid();
	CREATE_FUNC(RotationBrid);
	//小鸟数据
	BirdVo* bVo;
	//舞台角度
	float angle;
	//更新
	void update();
private:
	void initData();
	//地面高度
	float floorPosY;
};
#endif
