#include "StartScene.h"
#include "ColorUtil.h"
#include "utils/ScreenUtil.h"

StartScene::StartScene(void)
{
	Vec2 points[] = { Vec2(0, 0), Vec2(0, ScreenUtil::getScreenHeight()),
					  Vec2(ScreenUtil::getScreenWidth(), ScreenUtil::getScreenHeight()),
					  Vec2(ScreenUtil::getScreenWidth(), 0) };
	DrawNode* draw = DrawNode::create();
	//±³¾°
	draw->drawPolygon(points, 4, ColorUtil::getColor4F(0x00 , 0xAD , 0xFF, 0xFF),
							0, ColorUtil::getColor4F(0x00, 0xAD, 0xFF, 0xFF));
	this->addChild(draw);

	Sprite* bg = Sprite::create("startBg.png");
	bg->setPositionX(ScreenUtil::getCenter().x);
	bg->setPositionY(ScreenUtil::getCenter().y + 40);
	this->addChild(bg);

	LabelTTF* txt = LabelTTF::create("Start Game", "Arial", 45);
	MenuItemLabel* startBtn = MenuItemLabel::create(txt);
	startBtn->setTag(startBtnTag);

	Menu* menu = Menu::create(startBtn,  NULL);
	menu->setAnchorPoint(ccp(.5, .5));
	menu->setPositionX(ScreenUtil::getCenter().x);
	menu->setPositionY(bg->getPositionY() - bg->getContentSize().height *.5 - 50);
	menu->alignItemsVertically();
	menu->setTag(menuTag);
	this->addChild(menu);
}

StartScene::~StartScene(void)
{
}
