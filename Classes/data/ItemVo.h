#pragma once
#ifndef _ITEM_VO_
#define _ITEM_VO_
#include "cocos2d.h"
using namespace std;
USING_NS_CC;
//道具类
class ItemVo :public Node
{
public:
	ItemVo();
	~ItemVo();
	CREATE_FUNC(ItemVo);
	//当前道具类型 1，分数翻倍
	int type;
	//x位置
	float x;
	//y位置
	float y;
};
#endif
