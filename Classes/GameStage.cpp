#include "GameStage.h"
#include "utils/ColorUtil.h"
#include "utils/Random.h"
#include "utils/MathUtil.h"
#include "data/WallVo.h"
using namespace brid;
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
		wall->drawPolygon(wallPoints, 4, ColorUtil::getColor4F(0x00, 0xDA, 0xFF, 0xFF),
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
		if(i == 6) 
		{
			Point pp = wall->getParent()->convertToWorldSpace(wall->getPosition());
			CCLOG("pp.x, pp.y %f %f", pp.x, pp.y);
		}
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

	this->debugNode = DrawNode::create();
	this->debugNode->drawDot(Vec2(0, 0), 3, ColorUtil::getColor4F(0xFF, 0x00, 0x00, 0xFF));
	this->addChild(this->debugNode);

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
	//旋转小鸟和墙壁容器
	Node* container = (Node*)this->getChildByTag(1);
	//container->setRotation(this->rotationBrid->angle);
	Node* wallContainer = (Node*)this->getChildByTag(2);
	//wallContainer->setRotation(-this->rotationBrid->angle * .5);

	//更新小鸟的位置和角度
	Sprite* bridSpt = (Sprite*)container->getChildByTag(0);
	bridSpt->setPositionX(this->rotationBrid->bVo->x);
	bridSpt->setPositionY(this->rotationBrid->bVo->y);
	bridSpt->setRotation(this->rotationBrid->bVo->angle);

	vector<Vec2> bridVect;
	GameStage::getBridVertex(bridVect, bridSpt);

	this->debugNode->clear();

	Vec2 bridPoints[] = { bridVect.at(0), bridVect.at(1),
							bridVect.at(2), bridVect.at(3) };
	this->debugNode->drawPolygon(bridPoints, 4, ColorUtil::getColor4F(0x00, 0xAD, 0xFF, 0x00),
											 1, ColorUtil::getColor4F(0xFF, 0x00, 0x00, 0xFF));
	int count = this->rotationBrid->wallAry->count();
	for (int i = 0; i < count; ++i)
	{
		WallVo* wVo = (WallVo* )this->rotationBrid->wallAry->objectAtIndex(i);
		DrawNode* wall = (DrawNode*)wallContainer->getChildByTag(wallTag + i);
		//float newHeight = (float)(this->wallHeight * wVo->scaleY);
		//wall->setScaleY(wVo->scaleY);
		//wall->setContentSize(CCSizeMake(wall->getContentSize().width, newHeight));
		
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
				CCLOG("hit %i %i", i, j);
				this->debugNode->drawDot(bridV2d, 5, ColorUtil::getColor4F(0xFF, 0x00, 0x00, 0xFF));
				break;
			}	
		}
		
		if (i == 6)
		{
			CCLOG("wall %f", wall->getRotation());
			CCLOG("wallVect.at(0) %f %f", wallVect.at(0).x, wallVect.at(0).y);
			CCLOG("wallVect.at(1) %f %f", wallVect.at(1).x, wallVect.at(1).y);
			CCLOG("wallVect.at(2) %f %f", wallVect.at(2).x, wallVect.at(2).y);
			CCLOG("wallVect.at(3) %f %f", wallVect.at(3).x, wallVect.at(3).y);

			CCLOG("wall getPositionX %f %f", wall->getPositionX(), wall->getPositionY());

			Vec2 wallPoints[] = { wallVect.at(0), wallVect.at(1),
								  wallVect.at(2), wallVect.at(3) };
			this->debugNode->drawPolygon(wallPoints, 4, ColorUtil::getColor4F(0x00, 0xAD, 0xFF, 0x00),
													1, ColorUtil::getColor4F(0xFF, 0x00, 0x00, 0xFF));
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

	Point p1 = Point(x - spt->getContentSize().width * .5, 0);

	Point p2 = Point(x - spt->getContentSize().width * .5,
					 y + spt->getContentSize().height);

	Point p3 = Point(x + spt->getContentSize().width * .5,
					 y + spt->getContentSize().height);

	Point p4 = Point(x + spt->getContentSize().width * .5, 0);

	//旋转
	/*vector<float> rotateVect;
	brid::MathUtil::rotate(rotateVect, x, y, p1.x, p1.y, -angle, false);
	p1 = Point(rotateVect.at(0), rotateVect.at(1));
	brid::MathUtil::rotate(rotateVect, x, y, p2.x, p2.y, -angle, false);
	p2 = Point(rotateVect.at(0), rotateVect.at(1));
	brid::MathUtil::rotate(rotateVect, x, y, p3.x, p3.y, -angle, false);
	p3 = Point(rotateVect.at(0), rotateVect.at(1));
	brid::MathUtil::rotate(rotateVect, x, y, p4.x, p4.y, -angle, false);
	p4 = Point(rotateVect.at(0), rotateVect.at(1));*/

	Vec2 v2d1 = spt->getParent()->convertToWorldSpace(p1);
	Vec2 v2d2 = spt->getParent()->convertToWorldSpace(p2);
	Vec2 v2d3 = spt->getParent()->convertToWorldSpace(p3);
	Vec2 v2d4 = spt->getParent()->convertToWorldSpace(p4);

	vect.push_back(v2d1);
	vect.push_back(v2d2);
	vect.push_back(v2d3);
	vect.push_back(v2d4);
}
