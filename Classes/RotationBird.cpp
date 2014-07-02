#include "RotationBird.h"
#include "data/WallVo.h"
#include "utils/Random.h"
#include "utils/MathUtil.h"
#include "utils/ScreenUtil.h"
RotationBird::RotationBird()
{
	this->createData();
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
	this->bVo->areaIndex = 0;
	this->isHit = false;
}

void RotationBird::update()
{
	this->angle++;
	this->wallAngle -= .5;
	this->bVo->update();
	if (this->bVo->y < this->floorPosY) this->bVo->y = this->floorPosY;
	//¼ÆËãÇ½±Ú
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

	/*for (unsigned int j = 0; j < this->bVo->vects.size(); ++j)
	{
		Vec2 birdV2d = this->bVo->vects.at(j);
		CCLOG("birdV2d.x, birdV2d.y %f %f", birdV2d.x, birdV2d.y);
		vector<float> rotateVect;
		bird::MathUtil::rotate(rotateVect, ScreenUtil::getCenter().x, ScreenUtil::getCenter().y, 
								birdV2d.x, birdV2d.y, this->angle, false);
		birdV2d = Vec2(rotateVect.at(0), rotateVect.at(1));
		
	}*/
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
	//°ë¾¶
	float r = 360;
	for (int i = 0; i < this->wallCount; ++i)
	{
		WallVo* wVo = WallVo::create();
		wVo->setSize(25, 150);
		wVo->minRangeScaleY = 0.7;
		wVo->maxRangeScaleY = 1.3;
		if (i % 2 == 0)
		{
			//ÍâÈ¦
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
			//ÄÚÈ¦
			wVo->camp = 0;
			wVo->angle = (i / 2) * 90;
		}
		this->wallAry->addObject(wVo);
	}
}
