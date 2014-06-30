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

	//************************************
	// Method:    getBirdVertex				����bird��ȡ������������
	// Parameter: vector<Vec2>& vect		�����������飨˳ʱ�룩
	// Parameter: Node * spt				��ʾ����
	//************************************
	void getBirdVertex(vector<Vec2> &vect, Node* spt);

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
		birdTag = 0,
		birdContainerTag = 1,
		wallContainerTag = 2,
		wallTag = 3,
		startSceneTag = 9,
		failSceneTag = 10,
		gameLayerTag = 11,
		uiLayerTag = 12,
		scoreTxtTag = 13,
		bgDrawTag = 14
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
	//������Ϸ����
	void setGameGgColor(Color4F color);
	//����ǽ����ɫ
	void setWallColor(Color4F color);
	//�ж��Ƿ񴩹��ϰ�
	void checkThough();
};
#endif
