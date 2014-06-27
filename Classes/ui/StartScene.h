#pragma once
#include "cocos2d.h"
USING_NS_CC;
class StartScene:public CCLayer
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

