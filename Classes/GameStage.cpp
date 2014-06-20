#include "GameStage.h"
#include "utils/ColorUtil.h"
#include "utils/Random.h"
#include "data/WallVo.h"
GameStage::GameStage()
{
	//初始化随机种子
	Random::initRandomSeed();

	Size visibleSize = Director::getInstance()->getVisibleSize();
	//绘制背景
	Vec2 points[] = { Vec2(0, 0), Vec2(0, visibleSize.height),
						Vec2(visibleSize.width, visibleSize.height),
						Vec2(visibleSize.width, 0) };
	DrawNode* draw = DrawNode::create();
	//背景
	draw->drawPolygon(points, 4, ColorUtil::getColor4F(0x00 , 0xAD , 0xFF, 0xFF),
							0, ColorUtil::getColor4F(0x00, 0xAD, 0xFF, 0xFF));
	//白色大园
	draw->drawDot(Vec2(visibleSize.width*.5, visibleSize.height*.5), 280,
							ColorUtil::getColor4F(0xFF, 0xFF, 0xFF, 0xFF));
	//中间蓝色小圆形
	draw->drawDot(Vec2(visibleSize.width*.5, visibleSize.height*.5), 80,
						ColorUtil::getColor4F(0x00, 0xAD, 0xFF, 0xFF));
	this->addChild(draw);

	this->rotationBrid = RotationBrid::create();
	this->rotationBrid->retain();

	Node* wallContainer = Node::create();
	wallContainer->setAnchorPoint(Point(.5f, .5f));
	wallContainer->setPosition(Point(Director::getInstance()->getVisibleSize().width * .5,
									 Director::getInstance()->getVisibleSize().height * .5));
	wallContainer->setTag(2);
	this->addChild(wallContainer);

	//绘制墙壁
	int count = this->rotationBrid->wallAry->count();
	//半径
	float r = 360;
	float width = 25;
	float height = 150;
	Vec2 wallPoints[] = { Vec2(-width / 2, 0), Vec2(-width / 2, height),
							Vec2(width / 2, height), Vec2(width / 2, 0),
							Vec2(-width / 2, 0) };
	int index = 0;
	for (int i = 0; i < count; ++i)
	{
		//绘制墙壁
		DrawNode* wall = DrawNode::create();
		wall->setAnchorPoint(Point(.5, 0));
		wall->drawPolygon(wallPoints, 5, ColorUtil::getColor4F(0x00, 0xAD, 0xFF, 0xFF),
										0, ColorUtil::getColor4F(0x00, 0xAD, 0xFF, 0xFF));
		wall->setTag(wallTag + i);
		if (i % 2 == 0)
		{
			float x = cos((index * 90) * M_PI / 180) * r;
			float y = sin((index * 90) * M_PI / 180) * r;
			float angle = atan2(y, x) * 180 / M_PI + 90;
			if (index % 2 == 0) angle = -angle;
			CCLOG("angle %f", angle);
			wall->setPosition(x, y);
			wall->setRotation(angle);
			index++;
		}
		else
		{
			wall->setRotation((i / 2) * 90);
		}
		wallContainer->addChild(wall);
	}

	Node* bridContainer = Node::create();
	bridContainer->setTag(1);
	bridContainer->setAnchorPoint(Point(.5f, .5f));
	bridContainer->setPosition(Point(Director::getInstance()->getVisibleSize().width * .5,
		Director::getInstance()->getVisibleSize().height * .5));
	Sprite* bridSpt = Sprite::create("brid.png");
	bridSpt->setTag(0);
	bridContainer->addChild(bridSpt);
	this->addChild(bridContainer);

	//初始化点击触摸
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_1(GameStage::onTouchBegan, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(listener, 1);

	this->schedule(schedule_selector(GameStage::loop), .03f);
}

bool GameStage::onTouchBegan(Touch* touch)
{
	this->rotationBrid->bVo->jump();
	return true;
}

GameStage::~GameStage()
{
}

void GameStage::loop(float dt)
{
	this->rotationBrid->update();
	this->render();
}

void GameStage::render()
{
	Node* container = (Node*)this->getChildByTag(1);
	container->setRotation(this->rotationBrid->angle);

	Node* wallContainer = (Node*)this->getChildByTag(2);
	wallContainer->setRotation(-this->rotationBrid->angle * .5);

	Sprite* bridSpt = (Sprite*)container->getChildByTag(0);
	bridSpt->setPositionX(this->rotationBrid->bVo->x);
	bridSpt->setPositionY(this->rotationBrid->bVo->y);
	bridSpt->setRotation(this->rotationBrid->bVo->angle);

	int count = this->rotationBrid->wallAry->count();
	for (int i = 0; i < count; ++i)
	{
		WallVo* wVo = (WallVo* )this->rotationBrid->wallAry->objectAtIndex(i);
		DrawNode* wall = (DrawNode*)wallContainer->getChildByTag(wallTag + i);
		wall->setScaleY(wVo->scaleY);
	}
}
