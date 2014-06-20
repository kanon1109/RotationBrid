#pragma once
#ifndef _GAME_STAGE_
#define _GAME_STAGE_
#include "cocos2d.h"
#include "RotationBrid.h"
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
	//墙壁的枚举
	enum tag
	{
		wallTag = 3
	};
};
#endif
