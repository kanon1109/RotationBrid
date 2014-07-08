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
	//��ʼ��UI
	void initUI();
	//��ʼ����ϷUI
	void initGameUI();
	//�����¼�
	virtual bool onTouchBegan(Touch* touch);
	//��ѭ��
	void loop(float dt);
	//��Ⱦ
	void render();
	//��תС��
	RotationBird* rotationBird;
	//���Ի���
	DrawNode* debugNode;
	//ǽ�ڵ�ö��
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
	//ǽ�ڵĿ��
	float wallWidth;
	//ǽ�ڵĸ߶�
	float wallHeight;
	//�Ƿ�ʧ��
	bool isFail;
	//ʧ��
	void fail();
	//��ʼ��ť����¼�
	void onClickStartBtn(Ref* sender);
	//���水ť����¼�
	void onClickReplayBtn(Ref* sender);
	//��ʾʧ�ܽ���
	void showFailUI(bool flag);
	//��ʼ��Ϸ
	void startGame();
	//���÷���
	void setScore(int score);
	//������Ϸ����
	void setGameGgColor(Color4F color);
	//����ǽ����ɫ
	void setWallColor(Color3B color);
	//�ӷ����ص�
	void addScoreHandler(Ref* pObj);
	//ʧ�ܻص�
	void failHandler(Ref* pObj);
};
#endif
