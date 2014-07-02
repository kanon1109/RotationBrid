#include "BirdVo.h"
#include "utils/MathUtil.h"
BirdVo::BirdVo(void)
{
	this->angle = 0;
	this->x = 0;
	this->y = 0;
	this->vx = 0;
	this->vy = 0;
	this->g = .6f;
	this->areaIndex = 0;
	this->width = 0;
	this->height = 0;
	this->parent = NULL;
}

BirdVo::~BirdVo(void)
{
}

void BirdVo::jump()
{
	this->vy = -5;
}

void BirdVo::setSize( float w, float h )
{
	this->width = w;
	this->height = h;
}

void BirdVo::update()
{
	this->y -= this->vy;
	this->vy += this->g;
	//计算鸟身体的角度
	this->angle = atan2(this->vy, this->vx) * 180 / M_PI;
	this->vects.clear();
	this->vects.push_back(Vec2(x - this->width * 0.5f, y - this->height * 0.5f));
	this->vects.push_back(Vec2(x - this->width * 0.5f, y + this->height * 0.5f));
	this->vects.push_back(Vec2(x + this->width * 0.5f, y + this->height * 0.5f));
	this->vects.push_back(Vec2(x + this->width * 0.5f, y - this->height * 0.5f));
	for (int i = 0; i < this->vects.size(); ++i)
	{
		Vec2 pos = this->vects.at(i);
		vector<float> rotateVect;
		bird::MathUtil::rotate(rotateVect, x, y, pos.x, pos.y, -this->angle, false);
		this->vects.at(i).x = rotateVect.at(0);
		this->vects.at(i).y = rotateVect.at(1);
		if (this->parent)
		{
			pos = this->parent->convertToWorldSpace(pos);
			this->vects.at(i).x = pos.x;
			this->vects.at(i).y = pos.y;
		}
	}
}

void BirdVo::initParent(Node* parent)
{
	this->parent = parent;
}
