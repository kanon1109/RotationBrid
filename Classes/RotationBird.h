#pragma once
#ifndef _ROTATION_BRID_
#define _ROTATION_BRID_
#include "data/BirdVo.h"
#include "cocos2d.h"
USING_NS_CC;
class RotationBird:public Node
{
public:
	RotationBird();
	~RotationBird();
	CREATE_FUNC(RotationBird);
	//小鸟数据
	BirdVo* bVo;
	//墙壁数组
	Array* wallAry;
	//小鸟容器角度
	float angle;
	//墙壁角度
	float wallAngle;
	//更新
	void update();
	//判断是否超过边界
	bool outRange();
	//初始化数据
	void initData();
private:
	//创建数据
	void createData();
	//地面高度
	float floorPosY;
	//顶部高度
	float topPosY;
	//墙壁的数量
	int wallCount;
};
#endif
