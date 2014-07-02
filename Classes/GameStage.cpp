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
		//绘制墙壁
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
	birdContainer->setPosition(Point(Director::getInstance()->getVisibleSize().width * .5,
									Director::getInstance()->getVisibleSize().height * .5));
	birdContainer->setRotation(this->rotationBird->angle);
	this->rotationBird->bVo->initParent(birdContainer);

	Sprite* birdSpt = Sprite::create("bird.png");
	birdSpt->setTag(birdTag);
	birdContainer->addChild(birdSpt);
	gameLayer->addChild(birdContainer);

	LabelTTF* scoreTxt = LabelTTF::create("0", "Arial", 60);
	scoreTxt->setTag(scoreTxtTag);
	scoreTxt->setAnchorPoint(Point(.5, .5));
	scoreTxt->setPosition(ScreenUtil::getCenter());
	gameLayer->addChild(scoreTxt);

	this->debugNode = DrawNode::create();
	this->addChild(this->debugNode);

	//初始化点击触摸
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_1(GameStage::onTouchBegan, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(listener, 1);
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
}

void GameStage::onClickStartBtn( Ref* sender )
{
	Layer* uiLayer = (Layer* )this->getChildByTag(uiLayerTag);
	StartScene* startUI = (StartScene* )uiLayer->getChildByTag(startSceneTag);
	startUI->setVisible(false);
	//初始化游戏场景
	this->initGameUI();
	//开始游戏
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
	this->checkThough();
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

	debugNode->clear();
	int count = this->rotationBird->wallAry->count();

	for (int i = 0; i < count; ++i)
	{
		WallVo* wVo = (WallVo* )this->rotationBird->wallAry->objectAtIndex(i);
		DrawNode* wall = (DrawNode*)wallContainer->getChildByTag(wallTag + i);
		wall->setScaleY(wVo->scaleY);
		wall->setContentSize(CCSizeMake(wVo->width, wVo->height));

		debugNode->drawDot(wVo->vects.at(0), 5, ColorUtil::getColor4F(0xFF, 0x00, 0x00, 0xFF));
		debugNode->drawDot(wVo->vects.at(1), 5, ColorUtil::getColor4F(0xFF, 0x00, 0x00, 0xFF));
		debugNode->drawDot(wVo->vects.at(2), 5, ColorUtil::getColor4F(0xFF, 0x00, 0x00, 0xFF));
		debugNode->drawDot(wVo->vects.at(3), 5, ColorUtil::getColor4F(0xFF, 0x00, 0x00, 0xFF));
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
	failUI->setScore(this->score);
}

void GameStage::startGame()
{
	this->rotationBird->initData();
	Layer* gameLayer = (Layer* )this->getChildByTag(gameLayerTag);
	Node* wallContainer = (Node* ) gameLayer->getChildByTag(wallContainerTag);
	wallContainer->setRotation(this->rotationBird->wallAngle);
	
	this->score = 0;
	this->setScore(this->score);
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
	//绘制背景
	Vec2 points[] = { Vec2(0, 0), Vec2(0, ScreenUtil::getScreenHeight()),
					  Vec2(ScreenUtil::getScreenWidth(), ScreenUtil::getScreenHeight()),
					  Vec2(ScreenUtil::getScreenWidth(), 0) };
	
	//背景
	draw->drawPolygon(points, 4, color, 0, color);
	//白色大园
	draw->drawDot(Vec2(ScreenUtil::getScreenWidth() *.5, ScreenUtil::getScreenHeight() *.5), 280,
						ColorUtil::getColor4F(0xFF, 0xFF, 0xFF, 0xFF));
	//中间蓝色小圆形
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

void GameStage::checkThough()
{
	Layer* gameLayer = (Layer* )this->getChildByTag(gameLayerTag);
	//旋转小鸟和墙壁容器
	Node* container = (Node*)gameLayer->getChildByTag(birdContainerTag);
	//更新小鸟的位置和角度
	Sprite* birdSpt = (Sprite*)container->getChildByTag(birdTag);
	float birdAngle = birdSpt->getRotation();
	float birdRad = bird::MathUtil::dgs2rds(birdAngle);
	float dis = birdSpt->getContentSize().width * .5;
	float bx = dis * cos(birdRad);
	float by = dis * sin(birdRad);
	//debugNode->clear();
	//头部坐标
	Vec2 headBirdPos = Vec2(birdSpt->getPositionX() + dis,
							birdSpt->getPositionY());
	//尾部坐标
	Vec2 tailBirdPos = Vec2(birdSpt->getPositionX() - dis,
							birdSpt->getPositionY());

	headBirdPos = birdSpt->getParent()->convertToWorldSpace(headBirdPos);
	tailBirdPos = birdSpt->getParent()->convertToWorldSpace(tailBirdPos);

	debugNode->drawDot(headBirdPos, 5, ColorUtil::getColor4F(0xFF, 0x00, 0x00, 0xFF));
	debugNode->drawDot(tailBirdPos, 5, ColorUtil::getColor4F(0xFF, 0xCC, 0x00, 0xFF));

	Node* wallContainer = (Node*)gameLayer->getChildByTag(wallContainerTag);
	
	vector<Vec2> posVect;
	int count = this->rotationBird->wallAry->count();
	int areaIndex = 0;
	for (int i = 0; i < count; ++i)
	{
		if(i % 2 != 0)
		{
			//内圈
			DrawNode* wall = (DrawNode* )wallContainer->getChildByTag(wallTag + i);
			float x = wall->getPositionX() + cos(bird::MathUtil::dgs2rds(-wall->getRotation() + 90)) * this->wallHeight;
			float y = wall->getPositionY() + sin(bird::MathUtil::dgs2rds(-wall->getRotation() + 90)) * this->wallHeight;
			Vec2 p = wall->getParent()->convertToWorldSpace(Vec2(x, y));
			posVect.push_back(p);
		}
	}
	int nextAreaIndex = this->rotationBird->bVo->areaIndex + 1;
	if (nextAreaIndex >= posVect.size()) nextAreaIndex = 0;
	Vec2 pos = posVect.at(nextAreaIndex);
	debugNode->drawDot(pos, 5, ColorUtil::getColor4F(0xFF, 0x00, 0x00, 0xFF));
	//头部过杆距离大于尾巴过杆距离
	if (headBirdPos.distance(pos) > tailBirdPos.distance(pos))
	{
		this->rotationBird->bVo->areaIndex = nextAreaIndex;	
		this->score++;
		this->setScore(this->score);
	}
	posVect.clear();
}
