#include "RotationBrid.h"
#include "data/WallVo.h"
#include "utils/Random.h"
RotationBrid::RotationBrid()
{
	this->initData();
}

RotationBrid::~RotationBrid()
{
}

void RotationBrid::initData()
{
	this->angle = 0;
	this->floorPosY = 80;
	this->bVo = BirdVo::create();
	this->bVo->x = 0;
	this->bVo->y = 200;
	this->bVo->vx = 10;
	this->bVo->retain();

	this->wallAry = Array::create();
	this->wallAry->retain();

	this->wallCount = 8;
	for (int i = 0; i < this->wallCount; ++i)
	{
		WallVo* wVo = WallVo::create();
		wVo->minRangeScaleY = 0.7;
		wVo->maxRangeScaleY = 1.3;
		this->wallAry->addObject(wVo);
	}
}

void RotationBrid::update()
{
	this->angle++;
	this->bVo->y -= this->bVo->vy;
	this->bVo->vy += this->bVo->g;
	//计算鸟身体的角度
	this->bVo->angle = atan2(this->bVo->vy, this->bVo->vx) * 180 / M_PI;
	if (this->bVo->y < this->floorPosY) this->bVo->y = this->floorPosY;
	//计算墙壁
	for (int i = 0; i < this->wallCount; ++i)
	{
		WallVo* wVo = (WallVo* )this->wallAry->objectAtIndex(i);
		if (wVo->scaleY > wVo->maxRangeScaleY || 
			wVo->scaleY < wVo->minRangeScaleY) 
			wVo->vy = -wVo->vy;
		/*if (i % 2 == 0)
			wVo->scaleY += wVo->vy;
		else
			wVo->scaleY -= wVo->vy;*/
	}
}
