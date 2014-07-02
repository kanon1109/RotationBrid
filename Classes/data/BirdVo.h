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
	//����
	void update();
	//����
	float x;
	float y;
	//�ٶ�
	float vx;
	float vy;
	//����
	float g;
	//�Ƕ�
	float angle;
	//��Ծ
	void jump();
	//�������������
	int areaIndex;
	//�����б�
	vector<Vec2> vects;
	//���
	float width;
	//�߶�
	float height;
	//ͷ������
	Vec2 headBirdPos;
	//β������
	Vec2 tailBirdPos;
	//���ø߿�
	void setSize(float w, float h);
	//��ʼ��
	void initParent(Node* parent);
private:
	Node* parent;
};

#endif // !1
