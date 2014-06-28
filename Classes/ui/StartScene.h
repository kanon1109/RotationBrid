#pragma once
#ifndef _START_SCENE_
#define _START_SCENE_
#include "cocos2d.h"
USING_NS_CC;
class StartScene:public Layer
{
public:
	StartScene(void);
	~StartScene(void);
	CREATE_FUNC(StartScene);
	enum startTag
	{
		startBtnTag,
		menuTag
	};
};
#endif
