#include "BirdVo.h"

BirdVo::BirdVo(void)
{
	this->angle = 0;
	this->x = 0;
	this->y = 0;
	this->vx = 0;
	this->vy = 0;
	this->g = .4f;
}

BirdVo::~BirdVo(void)
{
}

void BirdVo::jump()
{
	this->vy = -4;
}
