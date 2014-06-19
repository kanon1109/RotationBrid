#include "RotationBrid.h"

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
	this->bVo->vx = 8;
	this->bVo->retain();
}

void RotationBrid::update()
{
	this->angle++;
	this->bVo->y -= this->bVo->vy;
	this->bVo->vy += this->bVo->g;
	//计算鸟身体的角度
	this->bVo->angle = atan2(this->bVo->vy, this->bVo->vx) * 180 / M_PI;
	if (this->bVo->y < this->floorPosY) this->bVo->y = this->floorPosY;
}
