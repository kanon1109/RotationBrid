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
	//�����¼�
	virtual bool onTouchBegan(Touch* touch);
	void loop(float dt);
	//��Ⱦ
	void render();
	RotationBrid* rotationBrid;
};
#endif
