#include "WallVo.h"
#include "utils/MathUtil.h"

WallVo::WallVo()
{
	this->vy = .005f;
	this->scaleY = 1;
	this->width = 0;
	this->height = 0;
	this->x = 0;
	this->y = 0;
	this->angle = 0;
	this->camp = 0;
}


WallVo::~WallVo()
{
}

void WallVo::setSize(float w, float h)
{
	this->width = w;
	this->height = h;
	this->prevHeight = h;
}

void WallVo::update()
{
	if (this->scaleY > this->maxRangeScaleY ||
		this->scaleY < this->minRangeScaleY)
		this->vy = -this->vy;
	if (this->camp == 1)
		this->scaleY += this->vy;
	else
		this->scaleY -= this->vy;
	//高度上下变化
	this->height = this->prevHeight * this->scaleY;

	//获取顶点列表
	this->vects.clear();
	
	Vec2 p1 = Vec2(this->x + this->width * .5, this->y);
	Vec2 p2 = Vec2(this->x + this->width * .5, this->y + this->height);
	Vec2 p3 = Vec2(this->x - this->width * .5, this->y + this->height);
	Vec2 p4 = Vec2(this->x - this->width * .5, this->y);

	//旋转
	vector<float> rotateVect;
	bird::MathUtil::rotate(rotateVect, this->x, this->y, p1.x, p1.y, -this->angle, false);
	p1 = Point(rotateVect.at(0), rotateVect.at(1));
	bird::MathUtil::rotate(rotateVect, this->x, this->y, p2.x, p2.y, -this->angle, false);
	p2 = Point(rotateVect.at(0), rotateVect.at(1));
	bird::MathUtil::rotate(rotateVect, this->x, this->y, p3.x, p3.y, -this->angle, false);
	p3 = Point(rotateVect.at(0), rotateVect.at(1));
	bird::MathUtil::rotate(rotateVect, this->x, this->y, p4.x, p4.y, -this->angle, false);
	p4 = Point(rotateVect.at(0), rotateVect.at(1));

	Vec2 v2d1 = this->parent->convertToWorldSpace(p1);
	Vec2 v2d2 = this->parent->convertToWorldSpace(p2);
	Vec2 v2d3 = this->parent->convertToWorldSpace(p3);
	Vec2 v2d4 = this->parent->convertToWorldSpace(p4);

	this->vects.push_back(v2d1);
	this->vects.push_back(v2d2);
	this->vects.push_back(v2d3);
	this->vects.push_back(v2d4);
	
	//障碍飞跃点
	float x = this->x + cos(bird::MathUtil::dgs2rds(-this->angle + 90)) * this->prevHeight;
	float y = this->y + sin(bird::MathUtil::dgs2rds(-this->angle + 90)) * this->prevHeight;
	this->referenPos = this->parent->convertToWorldSpace(Vec2(x, y));
}

void WallVo::initParent(Node* parent)
{
	this->parent = parent;
}
