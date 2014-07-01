#include "RotationBird.h"
#include "data/WallVo.h"
#include "utils/Random.h"
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
		if (wVo->scaleY > wVo->maxRangeScaleY || 
			wVo->scaleY < wVo->minRangeScaleY) 
			wVo->vy = -wVo->vy;
		if (i % 2 == 0)
			wVo->scaleY += wVo->vy;
		else
			wVo->scaleY -= wVo->vy;
	}
}

bool RotationBird::outRange()
{
	if(this->bVo->y <= this->floorPosY || 
	   this->bVo->y >= this->topPosY)
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
	for (int i = 0; i < this->wallCount; ++i)
	{
		WallVo* wVo = WallVo::create();
		wVo->minRangeScaleY = 0.7;
		wVo->maxRangeScaleY = 1.3;
		this->wallAry->addObject(wVo);
	}
}
