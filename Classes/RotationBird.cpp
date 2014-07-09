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
	this->isFail = false;
	this->score = 0;
	this->curItemVo = NULL;
}

void RotationBird::update()
{
	if (this->isHit) return;
	this->angle++;
	this->wallAngle -= .5;
	this->bVo->update();
	if (this->bVo->y < this->floorPosY) this->bVo->y = this->floorPosY;
	this->isHit = this->checkWallHit();
	this->checkThough();
	if (this->checkFail())
	{
		this->isFail = true;
		NotificationCenter::getInstance()->postNotification(FAIL);
	}	
}

bool RotationBird::checkFail()
{
	if( this->bVo->y <= this->floorPosY || 
		this->bVo->y >= this->topPosY || 
		this->isHit)
		return true;
	return false;
}

void RotationBird::createData()
{
	this->bVo = BirdVo::create();
	this->bVo->setSize(28, 19);
	this->bVo->retain();

	this->wallAry = Array::create();
	this->wallAry->retain();

	this->wallCount = 8;
	int index = 0;
	//半径
	float r = 370;
	for (int i = 0; i < this->wallCount; ++i)
	{
		WallVo* wVo = WallVo::create();
		wVo->setSize(25, 150);
		wVo->minRangeScaleY = 0.6;
		wVo->maxRangeScaleY = 1.4;
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
	//头部过杆距离大于尾巴过杆距离
	if (this->bVo->headBirdPos.distance(pos) > this->bVo->tailBirdPos.distance(pos))
	{
		this->bVo->areaIndex = nextAreaIndex;	
		this->score++;
		NotificationCenter::getInstance()->postNotification(ADD_SCORE);  
		//创建一个道具
		this->createItem();
	}
	posVect.clear();
}

void RotationBird::createItem()
{
	if (this->curItemVo) return;
	//小于3分之一概率 创建一个道具
	if (Random::boolean(.3))
	{
		//半径
		int r = Random::randomInt(90, 270);
		int angle = 90;
		int area = Random::randomInt(0, 3);
		int randAngle = Random::randomInt(30, 60) + angle * area;
		this->curItemVo = ItemVo::create();
		this->curItemVo->type = 1;
		this->curItemVo->x = cos(bird::MathUtil::dgs2rds(randAngle)) * r;
		this->curItemVo->y = sin(bird::MathUtil::dgs2rds(randAngle)) * r;
		NotificationCenter::getInstance()->postNotification(ADD_ITEM, this->curItemVo);
	}
}

bool RotationBird::checkWallHit()
{
	//计算墙壁
	for (int i = 0; i < this->wallCount; ++i)
	{
		WallVo* wVo = (WallVo*)this->wallAry->objectAtIndex(i);
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
				return true;
			}
		}
	}
	return false;
}

bool RotationBird::checkItemHit()
{
	if (bird::MathUtil::distance(this->curItemVo->x, this->curItemVo->y,
								this->bVo->x, this->bVo->y) < this->bVo->width)
	{
		//hit
		return true;
	}
	return false;
}
