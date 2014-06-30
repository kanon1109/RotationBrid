#pragma once
#ifndef _ROTATION_BRID_
#define _ROTATION_BRID_
#include "data/BirdVo.h"
#include "cocos2d.h"
USING_NS_CC;
class RotationBird:public Node
{
public:
	RotationBird();
	~RotationBird();
	CREATE_FUNC(RotationBird);
	//С������
	BirdVo* bVo;
	//ǽ������
	Array* wallAry;
	//С�������Ƕ�
	float angle;
	//ǽ�ڽǶ�
	float wallAngle;
	//����
	void update();
	//�ж��Ƿ񳬹��߽�
	bool outRange();
	//��ʼ������
	void initData();
private:
	//��������
	void createData();
	//����߶�
	float floorPosY;
	//�����߶�
	float topPosY;
	//ǽ�ڵ�����
	int wallCount;
};
#endif
