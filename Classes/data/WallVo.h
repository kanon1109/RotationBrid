#pragma once
#ifndef _WALL_VO_
#define _WALL_VO_
#include "cocos2d.h"
using namespace std;
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
	//宽度
	float width;
	//高度
	float height;
	//最初的高度
	float prevHeight;
	//角度
	float angle;
	//x位置
	float x;
	//y位置
	float y;
	//设置高宽
	void setSize(float w, float h);
	//初始化
	void initParent(Node* parent);
	//更新
	void update();
	//顶点列表
	vector<Vec2> vects;
	//属于内圈还是外圈 0内圈，1外圈
	int camp;
	//穿越障碍用的参考点
	Vec2 referenPos;
private:
	Node* parent;
};
#endif // !1
