#include "RotationBird.h"
#include "data/WallVo.h"
#include "utils/Random.h"
#include "utils/MathUtil.h"
#include "utils/ScreenUtil.h"
RotationBird::RotationBird()
{
	this->createData();
	this->initData();
}

RotationBird::~RotationBird()
{
}

void RotationBird::initData()
{
	this->angle = 0;
	this->wallAngle = -20;
	this->floorPosY = 80;
	this->topPosY = 270;
	this->bVo->x = 0;
	this->bVo->y = 240;
	this->bVo->vx = 10;
	this->bVo->vy = 0;
	this->bVo->wingX = 8;
	this->bVo->wingY = 9;
	this->bVo->areaIndex = 0;
	this->isHit = false;
	this->score = 0;
}

void RotationBird::update()
{
	this->angle++;
	this->wallAngle -= .5;
	this->bVo->update();
	if (this->bVo->y < this->floorPosY) this->bVo->y = this->floorPosY;
	//计算墙壁
	for (int i = 0; i < this->wallCount; ++i)
	{
		WallVo* wVo = (WallVo* )this->wallAry->objectAtIndex(i);
		wVo->update();
		for (unsigned int j = 0; j < this->bVo->vects.size(); ++j)
		{
			Vec2 birdV2d = this->bVo->vects.at(j);
			if (bird::MathUtil::isInsideSquare(wVo->vects.at(0),
												wVo->vects.at(1),
												wVo->vects.at(2),
												wVo->vects.at(3),
												birdV2d))
			{
				this->isHit = true;
				break;
			}
		}
	}
	this->checkThough();
}

bool RotationBird::checkFail()
{
	if(this->bVo->y <= this->floorPosY || 
		this->bVo->y >= this->topPosY || 
		this->isHit)
		return true;
	return false;
}

void RotationBird::createData()
{
	this->bVo = BirdVo::create();
	this->bVo->setSize(31, 22);
	this->bVo->retain();

	this->wallAry = Array::create();
	this->wallAry->retain();

	this->wallCount = 8;
	int index = 0;
	//半径
	float r = 360;
	for (int i = 0; i < this->wallCount; ++i)
	{
		WallVo* wVo = WallVo::create();
		wVo->setSize(25, 150);
		wVo->minRangeScaleY = 0.7;
		wVo->maxRangeScaleY = 1.3;
		if (i % 2 == 0)
		{
			//外圈
			wVo->x = cos((index * 90) * M_PI / 180) * r;
			wVo->y = sin((index * 90) * M_PI / 180) * r;
			float angle = atan2(wVo->y, wVo->x) * 180 / M_PI + 90;
			if (index % 2 == 0) angle = -angle;
			wVo->angle = angle;
			wVo->camp = 1;
			index++;
		}
		else
		{
			//内圈
			wVo->camp = 0;
			wVo->angle = (i / 2) * 90;
		}
		this->wallAry->addObject(wVo);
	}
}

void RotationBird::checkThough()
{
	vector<Vec2> posVect;
	int count = this->wallAry->count();
	int areaIndex = 0;
	for (int i = 0; i < count; ++i)
	{
		WallVo* wVo = (WallVo* )this->wallAry->objectAtIndex(i);
		if(wVo->camp == 0)
		{
			//内圈
			posVect.push_back(wVo->referenPos);
		}
	}
	int nextAreaIndex = this->bVo->areaIndex + 1;
	if (nextAreaIndex >= posVect.size()) nextAreaIndex = 0;
	Vec2 pos = posVect.at(nextAreaIndex);
	CCLOG("this->bVo->headBirdPos %f %f", this->bVo->headBirdPos.x, this->bVo->headBirdPos.y);
	CCLOG("this->bVo->tailBirdPos %f %f", this->bVo->tailBirdPos.x, this->bVo->tailBirdPos.y);
	CCLOG("pos %f %f", pos.x, pos.y);
	//CCLOG("this->bVo->headBirdPos.distance(pos) %f", this->bVo->headBirdPos.distance(pos));
	//CCLOG("this->bVo->tailBirdPos.distance(pos) %f", this->bVo->tailBirdPos.distance(pos));
	//头部过杆距离大于尾巴过杆距离
	if (this->bVo->headBirdPos.distance(pos) > this->bVo->tailBirdPos.distance(pos))
	{
		this->bVo->areaIndex = nextAreaIndex;	
		this->score++;
		NotificationCenter::getInstance()->postNotification(ADD_SCORE);  
	}
	posVect.clear();
}
