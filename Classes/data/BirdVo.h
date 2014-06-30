#pragma once
#ifndef _BIRD_VO_
#define _BIRD_VO_
#include "cocos2d.h"
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
};

#endif // !1
