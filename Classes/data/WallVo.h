#pragma once
#ifndef _WALL_VO_
#define _WALL_VO_
#include "cocos2d.h"
using namespace std;
USING_NS_CC;
class WallVo:public Node
{
public:
	WallVo();
	~WallVo();
	CREATE_FUNC(WallVo);
	//�����ٶ�
	float vy;
	//��������
	float scaleY;
	//��СscaleY��Χ
	float minRangeScaleY;
	//���scaleY��Χ
	float maxRangeScaleY;
	//���
	float width;
	//�߶�
	float height;
	//����ĸ߶�
	float prevHeight;
	//�Ƕ�
	float angle;
	//xλ��
	float x;
	//yλ��
	float y;
	//���ø߿�
	void setSize(float w, float h);
	//��ʼ��
	void initParent(Node* parent);
	//����
	void update();
	//�����б�
	vector<Vec2> vects;
	//������Ȧ������Ȧ 0��Ȧ��1��Ȧ
	int camp;
	//��Խ�ϰ��õĲο���
	Vec2 referenPos;
private:
	Node* parent;
};
#endif // !1
