#include "GameStage.h"
#include "utils/ColorUtil.h"
#include "utils/Random.h"
#include "utils/MathUtil.h"
#include "utils/ScreenUtil.h"
#include "data/WallVo.h"
#include "ui/StartScene.h"
#include "ui/FailScene.h"
#include "SimpleAudioEngine.h"
using namespace CocosDenshion;
using namespace bird;
GameStage::GameStage()
{
	//初始化随机种子
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

	Sprite* centerBg = Sprite::create("centerBg.png");
	centerBg->setTag(centerBgTag);
	centerBg->setPosition(ScreenUtil::getCenter());
	gameLayer->addChild(centerBg);

	Sprite* blueCenterBg = Sprite::create("blueCenterBg.png");
	blueCenterBg->setPosition(ScreenUtil::getCenter());
	blueCenterBg->setTag(blueCenterBgTag);
	gameLayer->addChild(blueCenterBg);

	Node* wallContainer = (Node* )Node::create();
	wallContainer->setAnchorPoint(Point(.5f, .5f));
	wallContainer->setPosition(ScreenUtil::getCenter());
	wallContainer->setTag(wallContainerTag);
	gameLayer->addChild(wallContainer);

	//半径
	float r = 360;
	this->wallWidth = 25;
	this->wallHeight = 150;
	int index = 0;
	//绘制墙壁
	int count = this->rotationBird->wallAry->count();
	for (int i = 0; i < count; ++i)
	{
		WallVo* wVo = (WallVo* )this->rotationBird->wallAry->objectAtIndex(i);
		wVo->initParent(wallContainer);

		Sprite* wall = Sprite::create("wallBg.png");
		//绘制墙壁
		//DrawNode* wall = DrawNode::create();
		wall->setAnchorPoint(Point(.5, 0));
		wall->setContentSize(CCSizeMake(this->wallWidth, this->wallHeight));
		wall->setTag(wallTag + i);
		wall->setPosition(wVo->x, wVo->y);
		wall->setRotation(wVo->angle);
		wallContainer->addChild(wall);
	}

	Node* birdContainer = Node::create();
	birdContainer->setTag(birdContainerTag);
	birdContainer->setAnchorPoint(Point(.5f, .5f));
	birdContainer->setPosition(ScreenUtil::getCenter());
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

	//this->debugNode = DrawNode::create();
	//this->addChild(this->debugNode);

	//初始化点击触摸
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_1(GameStage::onTouchBegan, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(listener, 1);
	//监听加分消息
	NotificationCenter::getInstance()->addObserver(this, callfuncO_selector(GameStage::addScoreHandler), ADD_SCORE, NULL);
	NotificationCenter::getInstance()->addObserver(this, callfuncO_selector(GameStage::failHandler), FAIL, NULL);
}

void GameStage::initUI()
{
	//游戏层
	Layer* gameLayer = Layer::create();
	gameLayer->setTag(gameLayerTag);
	this->addChild(gameLayer);

	//ui层
	Layer* uiLayer = Layer::create();
	uiLayer->setTag(uiLayerTag);
	this->addChild(uiLayer);

	//开始界面
	StartScene* startUI = StartScene::create();
	startUI->setTag(startSceneTag);
	Menu* menu = (Menu* )startUI->getChildByTag(StartScene::menuTag);
	MenuItemLabel* startBtn = (MenuItemLabel* )menu->getChildByTag(StartScene::startBtnTag);
	startBtn->setCallback(CC_CALLBACK_1(GameStage::onClickStartBtn, this));
	uiLayer->addChild(startUI);

	//失败界面
	FailScene* failUI = FailScene::create();
	failUI->setTag(failSceneTag);
	menu = (Menu* )failUI->getChildByTag(FailScene::menuTag);
	MenuItemLabel* replayBtn = (MenuItemLabel* )menu->getChildByTag(FailScene::replayBtnTag);
	replayBtn->setCallback(CC_CALLBACK_1(GameStage::onClickReplayBtn, this));
	uiLayer->addChild(failUI);
	failUI->setVisible(false);

	SimpleAudioEngine::sharedEngine()->preloadEffect("sfx_wing.mp3");
	SimpleAudioEngine::sharedEngine()->preloadEffect("sfx_hit.mp3");
	SimpleAudioEngine::sharedEngine()->preloadEffect("sfx_point.mp3");
	

}

void GameStage::onClickStartBtn( Ref* sender )
{
	Layer* uiLayer = (Layer* )this->getChildByTag(uiLayerTag);
	StartScene* startUI = (StartScene* )uiLayer->getChildByTag(startSceneTag);
	startUI->removeFromParent();
	//startUI->setVisible(false);
	//初始化游戏场景
	this->initGameUI();
	//开始游戏
	this->startGame();
}

bool GameStage::onTouchBegan(Touch* touch)
{
	SimpleAudioEngine::getInstance()->playEffect("sfx_wing.mp3");
	this->rotationBird->bVo->jump();
	return true;
}

GameStage::~GameStage()
{
}

void GameStage::loop(float dt)
{
	this->rotationBird->update();
	this->render();
}

void GameStage::render()
{
	Layer* gameLayer = (Layer* )this->getChildByTag(gameLayerTag);
	//旋转小鸟和墙壁容器
	Node* container = (Node*)gameLayer->getChildByTag(birdContainerTag);
	container->setRotation(this->rotationBird->angle);
	Node* wallContainer = (Node*)gameLayer->getChildByTag(wallContainerTag);
	wallContainer->setRotation(this->rotationBird->wallAngle);

	//更新小鸟的位置和角度
	Sprite* birdSpt = (Sprite*)container->getChildByTag(birdTag);
	birdSpt->setPositionX(this->rotationBird->bVo->x);
	birdSpt->setPositionY(this->rotationBird->bVo->y);
	birdSpt->setRotation(this->rotationBird->bVo->angle);

	Sprite* wingSpt = (Sprite*)birdSpt->getChildByTag(wingTag);
	wingSpt->setPositionX(this->rotationBird->bVo->wingX);
	wingSpt->setPositionY(this->rotationBird->bVo->wingY);

	/*debugNode->clear();
	debugNode->drawDot(this->rotationBird->bVo->headBirdPos, 5, ColorUtil::getColor4F(0xFF, 0x00, 0x00, 0xFF));
	debugNode->drawDot(this->rotationBird->bVo->tailBirdPos, 5, ColorUtil::getColor4F(0xFF, 0x00, 0x00, 0xFF));*/

	//障碍上下移动
	int count = this->rotationBird->wallAry->count();
	for (int i = 0; i < count; ++i)
	{
		WallVo* wVo = (WallVo* )this->rotationBird->wallAry->objectAtIndex(i);
		DrawNode* wall = (DrawNode*)wallContainer->getChildByTag(wallTag + i);
		wall->setScaleY(wVo->scaleY);
		wall->setContentSize(CCSizeMake(wVo->width, wVo->height));
	}
}

void GameStage::fail()
{
	SimpleAudioEngine::getInstance()->playEffect("sfx_hit.mp3");
	Color4F color = ColorUtil::getColor4F(0x00, 0x00, 0x00, 0xFF);
	this->setGameGgColor(color);
	Color3B color3b = Color3B(0x00, 0x00, 0x00);
	this->setWallColor(color3b);
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
		//重置最高分
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
	Color3B color3b = Color3B(0xAD, 0xFF, 0xFF);
	this->setWallColor(color3b);
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
	//绘制背景
	Vec2 points[] = { ScreenUtil::getLeftBottom(), ScreenUtil::getLeftTop(),
					  ScreenUtil::getRightTop(), ScreenUtil::getRightBottom() };
	//背景
	draw->drawPolygon(points, 4, color, 0, color);
}

void GameStage::setWallColor(Color3B color)
{
	Layer* gameLayer = (Layer* )this->getChildByTag(gameLayerTag);
	Node* wallContainer = (Node*)gameLayer->getChildByTag(wallContainerTag);
	wallContainer->setCascadeColorEnabled(true);
	wallContainer->setColor(color);

	Sprite* blueCenterBg = (Sprite*)gameLayer->getChildByTag(blueCenterBgTag);
	blueCenterBg->setColor(color);
}

void GameStage::addScoreHandler( Ref* pObj )
{
	SimpleAudioEngine::getInstance()->playEffect("sfx_point.mp3");
	this->setScore(this->rotationBird->score);
}

void GameStage::failHandler(Ref* pObj)
{
	this->fail();
}
