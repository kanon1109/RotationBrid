#pragma once
#ifndef _WALL_VO_
#define _WALL_VO_
#include "cocos2d.h"
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
};
#endif // !1
