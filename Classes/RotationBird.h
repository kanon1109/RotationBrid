#pragma once
#ifndef _ROTATION_BRID_
#define _ROTATION_BRID_
//�ӷ���Ϣ
#define ADD_SCORE "addScore"
#define FAIL "fail"
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
	//��ʼ������
	void initData();
	//����
	int score;
private:
	//�ж��Ƿ񳬹��߽�
	bool checkFail();
	//��������
	void createData();
	//����߶�
	float floorPosY;
	//�����߶�
	float topPosY;
	//ǽ�ڵ�����
	int wallCount;
	//�Ƿ���ײ���ϰ�
	bool isHit;
	//�жϴ����ϰ�
	void checkThough();
};
#endif
