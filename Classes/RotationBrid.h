#pragma once
#ifndef _ROTATION_BRID_
#define _ROTATION_BRID_
#include "data/BirdVo.h"
#include "cocos2d.h"
USING_NS_CC;
class RotationBrid:public Node
{
public:
	RotationBrid();
	~RotationBrid();
	CREATE_FUNC(RotationBrid);
	//С������
	BirdVo* bVo;
	//��̨�Ƕ�
	float angle;
	//����
	void update();
private:
	void initData();
	//����߶�
	float floorPosY;
};
#endif
