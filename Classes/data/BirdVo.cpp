#include "BirdVo.h"


BirdVo::BirdVo(void)
{
}


BirdVo::~BirdVo(void)
{
}

void BirdVo::update()
{
	this->x += this->vx;
	this->y += this->vy;
}
