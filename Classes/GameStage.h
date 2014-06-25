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
	//�����¼�
	virtual bool onTouchBegan(Touch* touch);
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
		wallTag = 3
	};
	//ǽ�ڵĿ��
	float wallWidth;
	//ǽ�ڵĸ߶�
	float wallHeight;
};
#endif
