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
	RotationBrid* rotationBrid;
	//���Ի���
	DrawNode* debugNode;

	//************************************
	// Method:    getBridVertex				����brid��ȡ������������
	// Parameter: vector<Vec2>& vect		�����������飨˳ʱ�룩
	// Parameter: Node * spt				��ʾ����
	//************************************
	void getBridVertex(vector<Vec2> &vect, Node* spt);

	//************************************
	// Description:	��ȡǽ�ڵĶ�����������
	// Parameter: vector<Vec2> & vect	�����������飨˳ʱ�룩
	// Parameter: Node * spt			��ʾ����
	// Returns:   void
	//************************************
	void getWallVertex(vector<Vec2> &vect, Node* spt);
	//ǽ�ڵ�ö��
	enum tag
	{
		bridTag = 0,
		bridContainerTag = 1,
		wallContainerTag = 2,
		wallTag = 3,
		startSceneTag = 9,
		failSceneTag = 10,
		gameLayerTag = 11,
		uiLayerTag = 12,
		scoreTxtTag = 13
	};
	//ǽ�ڵĿ��
	float wallWidth;
	//ǽ�ڵĸ߶�
	float wallHeight;
	//ʧ��
	void fail();
	//��ʼ��ť����¼�
	void GameStage::onClickStartBtn(Ref* sender);
	//���水ť����¼�
	void GameStage::onClickReplayBtn(Ref* sender);
	//��ʾʧ�ܽ���
	void showFailUI(bool flag);
	//��ʼ��Ϸ
	void startGame();
	//���÷���
	void setScore(int score);
};
#endif
