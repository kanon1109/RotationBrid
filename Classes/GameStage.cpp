#include "GameStage.h"
#include "utils/ColorUtil.h"
#include "utils/Random.h"
#include "utils/MathUtil.h"
#include "utils/ScreenUtil.h"
#include "data/WallVo.h"
#include "ui/StartScene.h"
#include "ui/FailScene.h"
using namespace bird;
GameStage::GameStage()
{
	//��ʼ���������
	Random::initRandomSeed();
	this->initUI();
}

void GameStage::initGameUI()
{
	Layer* gameLayer = (Layer* )this->getChildByTag(gameLayerTag);
	this->rotationBird = RotationBird::create();
	this->rotationBird->retain();

	DrawNode* draw = DrawNode::create();
	draw->setTag(bgDrawTag);
	gameLayer->addChild(draw);

	Node* wallContainer = (Node* )Node::create();
	wallContainer->setAnchorPoint(Point(.5f, .5f));
	wallContainer->setPosition(ScreenUtil::getCenter());
	wallContainer->setTag(wallContainerTag);
	gameLayer->addChild(wallContainer);

	//�뾶
	float r = 360;
	this->wallWidth = 25;
	this->wallHeight = 150;
	int index = 0;
	//����ǽ��
	int count = this->rotationBird->wallAry->count();
	for (int i = 0; i < count; ++i)
	{
		WallVo* wVo = (WallVo* )this->rotationBird->wallAry->objectAtIndex(i);
		wVo->initParent(wallContainer);
		//����ǽ��
		DrawNode* wall = DrawNode::create();
		wall->setAnchorPoint(Point(0, 0));
		wall->setContentSize(CCSizeMake(this->wallWidth, this->wallHeight));
		wall->setTag(wallTag + i);
		wall->setPosition(wVo->x, wVo->y);
		wall->setRotation(wVo->angle);
		wallContainer->addChild(wall);
	}

	Node* birdContainer = Node::create();
	birdContainer->setTag(birdContainerTag);
	birdContainer->setAnchorPoint(Point(.5f, .5f));
	//birdContainer->setRotation(this->rotationBird->angle);
	birdContainer->setPosition(Point(Director::getInstance()->getVisibleSize().width * .5,
									Director::getInstance()->getVisibleSize().height * .5));
	this->rotationBird->bVo->initParent(birdContainer);

	Sprite* birdSpt = Sprite::create("bird.png");
	birdSpt->setTag(birdTag);
	birdContainer->addChild(birdSpt);

	Sprite* wingSpt = Sprite::create("wing.png");
	wingSpt->setTag(wingTag);
	birdSpt->addChild(wingSpt);
	gameLayer->addChild(birdContainer);

	LabelTTF* scoreTxt = LabelTTF::create("0", "Arial", 60);
	scoreTxt->setTag(scoreTxtTag);
	scoreTxt->setAnchorPoint(Point(.5, .5));
	scoreTxt->setPosition(ScreenUtil::getCenter());
	gameLayer->addChild(scoreTxt);

	this->debugNode = DrawNode::create();
	this->addChild(this->debugNode);

	//��ʼ���������
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_1(GameStage::onTouchBegan, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(listener, 1);
	//�����ӷ���Ϣ
	NotificationCenter::getInstance()->addObserver(this, callfuncO_selector(GameStage::addScoreHandler), ADD_SCORE, NULL);  
}

void GameStage::initUI()
{
	//��Ϸ��
	Layer* gameLayer = Layer::create();
	gameLayer->setTag(gameLayerTag);
	this->addChild(gameLayer);

	//ui��
	Layer* uiLayer = Layer::create();
	uiLayer->setTag(uiLayerTag);
	this->addChild(uiLayer);

	//��ʼ����
	StartScene* startUI = StartScene::create();
	startUI->setTag(startSceneTag);
	Menu* menu = (Menu* )startUI->getChildByTag(StartScene::menuTag);
	MenuItemLabel* startBtn = (MenuItemLabel* )menu->getChildByTag(StartScene::startBtnTag);
	startBtn->setCallback(CC_CALLBACK_1(GameStage::onClickStartBtn, this));
	uiLayer->addChild(startUI);

	//ʧ�ܽ���
	FailScene* failUI = FailScene::create();
	failUI->setTag(failSceneTag);
	menu = (Menu* )failUI->getChildByTag(FailScene::menuTag);
	MenuItemLabel* replayBtn = (MenuItemLabel* )menu->getChildByTag(FailScene::replayBtnTag);
	replayBtn->setCallback(CC_CALLBACK_1(GameStage::onClickReplayBtn, this));
	uiLayer->addChild(failUI);
	failUI->setVisible(false);
}

void GameStage::onClickStartBtn( Ref* sender )
{
	Layer* uiLayer = (Layer* )this->getChildByTag(uiLayerTag);
	StartScene* startUI = (StartScene* )uiLayer->getChildByTag(startSceneTag);
	startUI->setVisible(false);
	//��ʼ����Ϸ����
	this->initGameUI();
	//��ʼ��Ϸ
	this->startGame();
}

bool GameStage::onTouchBegan(Touch* touch)
{
	this->rotationBird->bVo->jump();
	return true;
}

GameStage::~GameStage()
{
}

void GameStage::loop(float dt)
{
	if(this->rotationBird->checkFail()) this->fail();
	this->rotationBird->update();
	this->render();
}

void GameStage::render()
{
	Layer* gameLayer = (Layer* )this->getChildByTag(gameLayerTag);
	//��תС���ǽ������
	Node* container = (Node*)gameLayer->getChildByTag(birdContainerTag);
	container->setRotation(this->rotationBird->angle);
	Node* wallContainer = (Node*)gameLayer->getChildByTag(wallContainerTag);
	wallContainer->setRotation(this->rotationBird->wallAngle);

	//����С���λ�úͽǶ�
	Sprite* birdSpt = (Sprite*)container->getChildByTag(birdTag);
	birdSpt->setPositionX(this->rotationBird->bVo->x);
	birdSpt->setPositionY(this->rotationBird->bVo->y);
	birdSpt->setRotation(this->rotationBird->bVo->angle);

	Sprite* wingSpt = (Sprite*)birdSpt->getChildByTag(wingTag);
	wingSpt->setPositionX(this->rotationBird->bVo->wingX);
	wingSpt->setPositionY(this->rotationBird->bVo->wingY);

	/*debugNode->clear();
	debugNode->drawDot(this->rotationBird->bVo->headBirdPos, 5, ColorUtil::getColor4F(0xFF, 0x00, 0x00, 0xFF));
	debugNode->drawDot(this->rotationBird->bVo->tailBirdPos, 5, ColorUtil::getColor4F(0xFF, 0x00, 0x00, 0xFF));
	*/

	//�ϰ������ƶ�
	int count = this->rotationBird->wallAry->count();
	for (int i = 0; i < count; ++i)
	{
		WallVo* wVo = (WallVo* )this->rotationBird->wallAry->objectAtIndex(i);
		DrawNode* wall = (DrawNode*)wallContainer->getChildByTag(wallTag + i);
		wall->setScaleY(wVo->scaleY);
		wall->setContentSize(CCSizeMake(wVo->width, wVo->height));

		/*if(i == 3)
		{
			CCLOG("referenPos %f %f", wVo->referenPos.x, wVo->referenPos.y);
			debugNode->drawDot(wVo->referenPos, 5, ColorUtil::getColor4F(0xFF, 0x00, 0x00, 0xFF));
		}*/
	}
}

void GameStage::fail()
{
	Color4F color = ColorUtil::getColor4F(0x00, 0x00, 0x00, 0xFF);
	this->setGameGgColor(color);
	this->setWallColor(color);
	this->unschedule(schedule_selector(GameStage::loop));
	this->showFailUI(true);
}

void GameStage::onClickReplayBtn( Ref* sender )
{
	this->showFailUI(false);
	this->startGame();
}

void GameStage::showFailUI( bool flag )
{
	Layer* uiLayer = (Layer* )this->getChildByTag(uiLayerTag);
	FailScene* failUI = (FailScene* )uiLayer->getChildByTag(failSceneTag);
	failUI->setVisible(flag);
	int bestScore = UserDefault::getInstance()->getIntegerForKey("best", 0);
	if(this->rotationBird->score > bestScore)
	{
		//������߷�
		UserDefault::getInstance()->setIntegerForKey("best", this->rotationBird->score);
	}
	failUI->setScore(this->rotationBird->score, bestScore);
}

void GameStage::startGame()
{
	this->rotationBird->initData();
	Layer* gameLayer = (Layer* )this->getChildByTag(gameLayerTag);
	Node* wallContainer = (Node* ) gameLayer->getChildByTag(wallContainerTag);
	wallContainer->setRotation(this->rotationBird->wallAngle);

	Node* birdContainer = (Node* ) gameLayer->getChildByTag(birdContainerTag);
	birdContainer->setRotation(this->rotationBird->angle);
	Sprite* birdSpt = (Sprite*)birdContainer->getChildByTag(birdTag);
	Sprite* wingSpt = (Sprite*)birdSpt->getChildByTag(wingTag);
	wingSpt->setPositionX(this->rotationBird->bVo->wingX);
	wingSpt->setPositionY(this->rotationBird->bVo->wingY);

	this->setScore(this->rotationBird->score);
	Color4F color = ColorUtil::getColor4F(0x00, 0xAD, 0xFF, 0xFF);
	this->setGameGgColor(color);
	this->setWallColor(color);
	this->schedule(schedule_selector(GameStage::loop), .03f);	
}

void GameStage::setScore( int score )
{
	String* str = String::createWithFormat("%d", score);
	Layer* gameLayer = (Layer* )this->getChildByTag(gameLayerTag);
	LabelTTF* scoreValTxt = (LabelTTF* )gameLayer->getChildByTag(scoreTxtTag);
	scoreValTxt->setString(str->_string);
}

void GameStage::setGameGgColor(Color4F color)
{
	Layer* gameLayer = (Layer* )this->getChildByTag(gameLayerTag);
	DrawNode* draw = (DrawNode* )gameLayer->getChildByTag(bgDrawTag);
	draw->clear();
	//���Ʊ���
	Vec2 points[] = { Vec2(0, 0), Vec2(0, ScreenUtil::getScreenHeight()),
					  Vec2(ScreenUtil::getScreenWidth(), ScreenUtil::getScreenHeight()),
					  Vec2(ScreenUtil::getScreenWidth(), 0) };
	
	//����
	draw->drawPolygon(points, 4, color, 0, color);
	//��ɫ��԰
	draw->drawDot(Vec2(ScreenUtil::getScreenWidth() *.5, ScreenUtil::getScreenHeight() *.5), 280,
						ColorUtil::getColor4F(0xFF, 0xFF, 0xFF, 0xFF));
	//�м���ɫСԲ��
	draw->drawDot(Vec2(ScreenUtil::getScreenWidth() *.5, ScreenUtil::getScreenHeight() *.5), 80, color);
}

void GameStage::setWallColor( Color4F color )
{
	Layer* gameLayer = (Layer* )this->getChildByTag(gameLayerTag);
	Node* wallContainer = (Node*)gameLayer->getChildByTag(wallContainerTag);
	Vec2 wallPoints[] = { Vec2(-this->wallWidth / 2, 0), 
							Vec2(-this->wallWidth / 2, this->wallHeight),
							Vec2(this->wallWidth / 2, this->wallHeight), 
							Vec2(this->wallWidth / 2, 0)};
	int count = this->rotationBird->wallAry->count();
	for (int i = 0; i < count; ++i)
	{
		DrawNode* wall = (DrawNode* ) wallContainer->getChildByTag(wallTag + i);
		wall->clear();
		wall->drawPolygon(wallPoints, 4, color, 0, color);
	}
}

void GameStage::addScoreHandler( Ref* pObj )
{
	this->setScore(this->rotationBird->score);
}
