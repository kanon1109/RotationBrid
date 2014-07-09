#pragma once
#ifndef _ROTATION_BRID_
#define _ROTATION_BRID_
//加分消息
#define ADD_SCORE "addScore"
//添加道具
#define ADD_ITEM "addItem"
#define FAIL "fail"
#include "data/BirdVo.h"
#include "data/ItemVo.h"
#include "cocos2d.h"
USING_NS_CC;
//旋转小鸟纯数据计算类
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
	//初始化数据
	void initData();
	//分数
	int score;
	//是否失败
	bool isFail;
private:
	//判断是否超过边界
	bool checkFail();
	//创建数据
	void createData();
	//地面高度
	float floorPosY;
	//顶部高度
	float topPosY;
	//墙壁的数量
	int wallCount;
	//是否碰撞到障碍
	bool isHit;
	//判断碰撞
	bool checkWallHit();
	//判断穿过障碍
	void checkThough();
	//创建道具
	void createItem();
	//判断道具碰撞
	bool checkItemHit();
	//当前道具
	ItemVo* curItemVo;
};
#endif
