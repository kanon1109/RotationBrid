#pragma once
#ifndef _BIRD_VO_
#define _BIRD_VO_
#include "cocos2d.h"
using namespace std;
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
	//顶点列表
	vector<Vec2> vects;
	//宽度
	float width;
	//高度
	float height;
	//头部坐标
	Vec2 headBirdPos;
	//尾部坐标
	Vec2 tailBirdPos;
	//设置高宽
	void setSize(float w, float h);
	//初始化
	void initParent(Node* parent);
private:
	Node* parent;
};

#endif // !1
