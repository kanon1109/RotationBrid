#pragma once
#ifndef _ROTATION_BRID_
#define _ROTATION_BRID_
//�ӷ���Ϣ
#define ADD_SCORE "addScore"
//��ӵ���
#define ADD_ITEM "addItem"
#define FAIL "fail"
#include "data/BirdVo.h"
#include "data/ItemVo.h"
#include "cocos2d.h"
USING_NS_CC;
//��תС�����ݼ�����
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
	//�Ƿ�ʧ��
	bool isFail;
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
	//�ж���ײ
	bool checkWallHit();
	//�жϴ����ϰ�
	void checkThough();
	//��������
	void createItem();
	//�жϵ�����ײ
	bool checkItemHit();
	//��ǰ����
	ItemVo* curItemVo;
};
#endif
