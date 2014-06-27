#include "GameStage.h"
#include "utils/ColorUtil.h"
#include "utils/Random.h"
#include "utils/MathUtil.h"
#include "utils/ScreenUtil.h"
#include "data/WallVo.h"
#include "ui/StartScene.h"
using namespace brid;
GameStage::GameStage()
{
	//初始化随机种子
	Random::initRandomSeed();
	this->initUI();
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
	//旋转小鸟和墙壁容器
	Node* container = (Node*)this->getChildByTag(bridContainerTag);
	container->setRotation(this->rotationBrid->angle);
	Node* wallContainer = (Node*)this->getChildByTag(wallContainerTag);
	wallContainer->setRotation(this->rotationBrid->wallAngle);

	//更新小鸟的位置和角度
	Sprite* bridSpt = (Sprite*)container->getChildByTag(bridTag);
	bridSpt->setPositionX(this->rotationBrid->bVo->x);
	bridSpt->setPositionY(this->rotationBrid->bVo->y);
	bridSpt->setRotation(this->rotationBrid->bVo->angle);

	if(this->rotationBrid->outRange())
		this->fail();

	vector<Vec2> bridVect;
	GameStage::getBridVertex(bridVect, bridSpt);

	int count = this->rotationBrid->wallAry->count();
	for (int i = 0; i < count; ++i)
	{
		WallVo* wVo = (WallVo* )this->rotationBrid->wallAry->objectAtIndex(i);
		DrawNode* wall = (DrawNode*)wallContainer->getChildByTag(wallTag + i);
		float newHeight = (float)(this->wallHeight * wVo->scaleY);
		wall->setScaleY(wVo->scaleY);
		wall->setContentSize(CCSizeMake(wall->getContentSize().width, newHeight));
		
		vector<Vec2> wallVect;
		GameStage::getWallVertex(wallVect, wall);

		for (unsigned int j = 0; j < bridVect.size(); ++j)
		{
			Vec2 bridV2d = bridVect.at(j);
			
			if(brid::MathUtil::isInsideSquare(wallVect.at(0), 
											  wallVect.at(1), 
											  wallVect.at(2), 
											  wallVect.at(3), 
											  bridV2d))
			{
				this->fail();
				break;
			}	
		}
		
		wallVect.clear();
	}
}

void GameStage::getBridVertex( vector<Vec2> &vect, Node* spt )
{
	float angle = spt->getRotation();
	float x = spt->getPositionX();
	float y = spt->getPositionY();
	Point p1 = Point(x - spt->getContentSize().width * .5, 
					 y - spt->getContentSize().height * .5);

	Point p2 = Point(x - spt->getContentSize().width * .5, 
					 y + spt->getContentSize().height * .5);

	Point p3 = Point(x + spt->getContentSize().width * .5, 
					 y + spt->getContentSize().height * .5);

	Point p4 = Point(x + spt->getContentSize().width * .5, 
					 y - spt->getContentSize().height * .5);
	//点旋转
	vector<float> rotateVect;
	brid::MathUtil::rotate(rotateVect, x, y, p1.x, p1.y, -angle, false);
	p1 = Point(rotateVect.at(0), rotateVect.at(1));
	brid::MathUtil::rotate(rotateVect, x, y, p2.x, p2.y, -angle, false);
	p2 = Point(rotateVect.at(0), rotateVect.at(1));
	brid::MathUtil::rotate(rotateVect, x, y, p3.x, p3.y, -angle, false);
	p3 = Point(rotateVect.at(0), rotateVect.at(1));
	brid::MathUtil::rotate(rotateVect, x, y, p4.x, p4.y, -angle, false);
	p4 = Point(rotateVect.at(0), rotateVect.at(1));

	Vec2 v2d1 = spt->getParent()->convertToWorldSpace(p1);
	Vec2 v2d2 = spt->getParent()->convertToWorldSpace(p2);
	Vec2 v2d3 = spt->getParent()->convertToWorldSpace(p3);
	Vec2 v2d4 = spt->getParent()->convertToWorldSpace(p4);

	vect.push_back(v2d1);
	vect.push_back(v2d2);
	vect.push_back(v2d3);
	vect.push_back(v2d4);
}

void GameStage::getWallVertex(vector<Vec2> &vect, Node* spt)
{
	float angle = spt->getRotation();
	float x = spt->getPositionX();
	float y = spt->getPositionY();

	Point p1 = Point(x + spt->getContentSize().width * .5, y);

	Point p2 = Point(x + spt->getContentSize().width * .5,
					 y + spt->getContentSize().height);

	Point p3 = Point(x - spt->getContentSize().width * .5,
					 y + spt->getContentSize().height);

	Point p4 = Point(x - spt->getContentSize().width * .5, y);

	//旋转
	vector<float> rotateVect;
	brid::MathUtil::rotate(rotateVect, x, y, p1.x, p1.y, -angle, false);
	p1 = Point(rotateVect.at(0), rotateVect.at(1));
	brid::MathUtil::rotate(rotateVect, x, y, p2.x, p2.y, -angle, false);
	p2 = Point(rotateVect.at(0), rotateVect.at(1));
	brid::MathUtil::rotate(rotateVect, x, y, p3.x, p3.y, -angle, false);
	p3 = Point(rotateVect.at(0), rotateVect.at(1));
	brid::MathUtil::rotate(rotateVect, x, y, p4.x, p4.y, -angle, false);
	p4 = Point(rotateVect.at(0), rotateVect.at(1));

	Vec2 v2d1 = spt->getParent()->convertToWorldSpace(p1);
	Vec2 v2d2 = spt->getParent()->convertToWorldSpace(p2);
	Vec2 v2d3 = spt->getParent()->convertToWorldSpace(p3);
	Vec2 v2d4 = spt->getParent()->convertToWorldSpace(p4);

	vect.push_back(v2d1);
	vect.push_back(v2d2);
	vect.push_back(v2d3);
	vect.push_back(v2d4);
}

void GameStage::fail()
{
	this->unschedule(schedule_selector(GameStage::loop));

}

void GameStage::initGame()
{
	//绘制背景
	Vec2 points[] = { Vec2(0, 0), Vec2(0, ScreenUtil::getScreenHeight()),
						Vec2(ScreenUtil::getScreenWidth(), ScreenUtil::getScreenHeight()),
						Vec2(ScreenUtil::getScreenWidth(), 0) };
	DrawNode* draw = DrawNode::create();
	//背景
	draw->drawPolygon(points, 4, ColorUtil::getColor4F(0x00 , 0xAD , 0xFF, 0xFF),
		0, ColorUtil::getColor4F(0x00, 0xAD, 0xFF, 0xFF));
	//白色大园
	draw->drawDot(Vec2(ScreenUtil::getScreenWidth() *.5, ScreenUtil::getScreenHeight() *.5), 280,
		ColorUtil::getColor4F(0xFF, 0xFF, 0xFF, 0xFF));
	//中间蓝色小圆形
	draw->drawDot(Vec2(ScreenUtil::getScreenWidth() *.5, ScreenUtil::getScreenHeight() *.5), 80,
		ColorUtil::getColor4F(0x00, 0xAD, 0xFF, 0xFF));
	this->addChild(draw);

	this->rotationBrid = RotationBrid::create();
	this->rotationBrid->retain();

	Node* wallContainer = Node::create();
	wallContainer->setAnchorPoint(Point(.5f, .5f));
	wallContainer->setPosition(Point(Director::getInstance()->getVisibleSize().width * .5,
		Director::getInstance()->getVisibleSize().height * .5));
	wallContainer->setTag(wallContainerTag);
	this->addChild(wallContainer);

	//绘制墙壁
	int count = this->rotationBrid->wallAry->count();
	//半径
	float r = 360;
	this->wallWidth = 25;
	this->wallHeight = 150;
	Vec2 wallPoints[] = { Vec2(-this->wallWidth / 2, 0), 
		Vec2(-this->wallWidth / 2, this->wallHeight),
		Vec2(this->wallWidth / 2, this->wallHeight), 
		Vec2(this->wallWidth / 2, 0)};
	int index = 0;
	for (int i = 0; i < count; ++i)
	{
		//绘制墙壁
		DrawNode* wall = DrawNode::create();
		wall->setAnchorPoint(Point(0, 0));
		wall->setContentSize(CCSizeMake(this->wallWidth, this->wallHeight));
		wall->drawPolygon(wallPoints, 4, ColorUtil::getColor4F(0x00, 0xAD, 0xFF, 0xFF),
			0, ColorUtil::getColor4F(0x00, 0xAD, 0xFF, 0xFF));
		wall->setTag(wallTag + i);
		if (i % 2 == 0)
		{
			//外圈
			float x = cos((index * 90) * M_PI / 180) * r;
			float y = sin((index * 90) * M_PI / 180) * r;
			float angle = atan2(y, x) * 180 / M_PI + 90;
			if (index % 2 == 0) angle = -angle;
			wall->setPosition(x, y);
			wall->setRotation(angle);
			index++;
		}
		else
		{
			//内圈
			wall->setRotation((i / 2) * 90);
		}
		wallContainer->addChild(wall);
	}

	Node* bridContainer = Node::create();
	bridContainer->setTag(bridContainerTag);
	bridContainer->setAnchorPoint(Point(.5f, .5f));
	bridContainer->setPosition(Point(Director::getInstance()->getVisibleSize().width * .5,
										Director::getInstance()->getVisibleSize().height * .5));
	Sprite* bridSpt = Sprite::create("brid.png");
	bridSpt->setTag(bridTag);
	bridContainer->addChild(bridSpt);
	this->addChild(bridContainer);

	//初始化点击触摸
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_1(GameStage::onTouchBegan, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(listener, 1);

	wallContainer->setRotation(this->rotationBrid->wallAngle);

	this->schedule(schedule_selector(GameStage::loop), .03f);
}

void GameStage::initUI()
{
	StartScene* start = StartScene::create();
	start->setTag(startSceneTag);
	Menu* menu = (Menu* )start->getChildByTag(StartScene::menuTag);
	MenuItemLabel* startBtn = (MenuItemLabel* )menu->getChildByTag(StartScene::startBtnTag);
	startBtn->setCallback(CC_CALLBACK_1(GameStage::onClickStartBtn, this));
	this->addChild(start);
}

void GameStage::onClickStartBtn( Ref* sender )
{
	StartScene* start = (StartScene* )this->getChildByTag(startSceneTag);
	start->removeFromParent();

	this->initGame();
}
