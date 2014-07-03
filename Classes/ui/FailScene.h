#pragma once
#ifndef _FAIL_SCENE_
#define _FAIL_SCENE_
#include "cocos2d.h"
USING_NS_CC;
class FailScene:public Layer
{
public:
	FailScene(void);
	~FailScene(void);
	CREATE_FUNC(FailScene);
	//…Ë÷√∑÷ ˝
	void setScore(int score, int bestScore);

	enum FailTag
	{
		scoreValTxtTag,
		replayBtnTag,
		menuTag,
		bestScoreValTxtTag
	};
};
#endif
