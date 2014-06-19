#include "GameStage.h"
#include "utils/ColorUtil.h"
GameStage::GameStage()
{
	this->angle = 1;

	Size visibleSize = Director::getInstance()->getVisibleSize();
	//»æÖÆ±³¾°
	Vec2 points[] = { Vec2(0, 0), Vec2(0, visibleSize.height), 
					Vec2(visibleSize.width, visibleSize.height),
					Vec2(visibleSize.width, 0)};
	DrawNode* draw = DrawNode::create();
	draw->drawPolygon(points, 4, ColorUtil::getColor4F(0x00 , 0xAD , 0xFF, 0xFF),
							4, ColorUtil::getColor4F(0x00, 0xAD, 0xFF, 0xFF));

	draw->drawDot(Vec2(visibleSize.width*.5, visibleSize.height*.5), 280, ColorUtil::getColor4F(0xFF, 0xFF, 0xFF, 0xFF));
	this->addChild(draw);

	Node* container = Node::create();
	container->setAnchorPoint(Point(.5f, .5f));
	container->setPosition(Point(Director::getInstance()->getVisibleSize().width * .5, 
								Director::getInstance()->getVisibleSize().height * .5));
	
	container->setTag(1);
	this->addChild(container);
	Sprite* bridSpt = Sprite::create("brid.png");
	bridSpt->setTag(0);
	container->addChild(bridSpt);

	this->rotationBrid = RotationBrid::create();
	this->rotationBrid->retain();

	//³õÊ¼»¯µã»÷´¥Ãþ
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_1(GameStage::onTouchBegan, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(listener, 1);

	
	//DrawPrimitives::drawRect(Vec2(0, 0), Vec2(visibleSize.width, visibleSize.height));
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
	Sprite* bridSpt = (Sprite*)container->getChildByTag(0);
	bridSpt->setPositionX(this->rotationBrid->bVo->x);
	bridSpt->setPositionY(this->rotationBrid->bVo->y);
	bridSpt->setRotation(this->rotationBrid->bVo->angle);
}
