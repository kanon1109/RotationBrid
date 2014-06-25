#pragma once
#ifndef _GAME_STAGE_
#define _GAME_STAGE_
#include "cocos2d.h"
#include "RotationBrid.h"
using namespace std;
USING_NS_CC;
class GameStage:public Scene
{
public:
	GameStage();
	~GameStage();
	CREATE_FUNC(GameStage);
private:
	//单点事件
	virtual bool onTouchBegan(Touch* touch);
	void loop(float dt);
	//渲染
	void render();
	//旋转小鸟
	RotationBrid* rotationBrid;
	//调试绘制
	DrawNode* debugNode;

	//************************************
	// Method:    getBridVertex				根据brid获取顶点坐标数组
	// Parameter: vector<Vec2>& vect		顶点坐标数组（顺时针）
	// Parameter: Node * spt				显示对象
	//************************************
	void getBridVertex(vector<Vec2> &vect, Node* spt);

	//************************************
	// Description:	获取墙壁的顶点坐标数组
	// Parameter: vector<Vec2> & vect	顶点坐标数组（顺时针）
	// Parameter: Node * spt			显示对象
	// Returns:   void
	//************************************
	void getWallVertex(vector<Vec2> &vect, Node* spt);

	//墙壁的枚举
	enum tag
	{
		wallTag = 3
	};
	//墙壁的宽度
	float wallWidth;
	//墙壁的高度
	float wallHeight;
};
#endif
