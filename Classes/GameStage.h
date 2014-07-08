#pragma once
#ifndef _GAME_STAGE_
#define _GAME_STAGE_
#include "cocos2d.h"
#include "RotationBird.h"
using namespace std;
USING_NS_CC;
class GameStage:public Scene
{
public:
	GameStage();
	~GameStage();
	CREATE_FUNC(GameStage);
private:
	//初始化UI
	void initUI();
	//初始化游戏UI
	void initGameUI();
	//单点事件
	virtual bool onTouchBegan(Touch* touch);
	//主循环
	void loop(float dt);
	//渲染
	void render();
	//旋转小鸟
	RotationBird* rotationBird;
	//调试绘制
	DrawNode* debugNode;
	//墙壁的枚举
	enum tag
	{
		birdTag = 0,
		birdContainerTag = 1,
		wallContainerTag = 2,
		wallTag = 3,
		startSceneTag = 9,
		failSceneTag = 10,
		gameLayerTag = 11,
		uiLayerTag = 12,
		scoreTxtTag = 13,
		bgDrawTag = 14,
		wingTag = 15,
		centerBgTag = 16,
		blueCenterBgTag = 17
	};
	//墙壁的宽度
	float wallWidth;
	//墙壁的高度
	float wallHeight;
	//是否失败
	bool isFail;
	//失败
	void fail();
	//开始按钮点击事件
	void onClickStartBtn(Ref* sender);
	//重玩按钮点击事件
	void onClickReplayBtn(Ref* sender);
	//显示失败界面
	void showFailUI(bool flag);
	//开始游戏
	void startGame();
	//设置分数
	void setScore(int score);
	//绘制游戏背景
	void setGameGgColor(Color4F color);
	//设置墙壁颜色
	void setWallColor(Color3B color);
	//加分数回调
	void addScoreHandler(Ref* pObj);
	//失败回调
	void failHandler(Ref* pObj);
};
#endif
