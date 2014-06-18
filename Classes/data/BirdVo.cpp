#include "BirdVo.h"

BirdVo::BirdVo(void)
{
	this->angleSpeed = 0;
	this->angleSpeedAdd = 1;
	this->vx = 0;
	this->vy = 0;
}

BirdVo::~BirdVo(void)
{
}

void BirdVo::update()
{
	this->angleSpeed += this->angleSpeedAdd;
	this->x += this->vx;
	this->y += this->vy;
}
