#pragma once
#ifndef _ITEM_VO_
#define _ITEM_VO_
#include "cocos2d.h"
using namespace std;
USING_NS_CC;
//������
class ItemVo :public Node
{
public:
	ItemVo();
	~ItemVo();
	CREATE_FUNC(ItemVo);
	//��ǰ�������� 1����������
	int type;
	//xλ��
	float x;
	//yλ��
	float y;
};
#endif
