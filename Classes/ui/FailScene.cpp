#include "FailScene.h"
#include "utils/ScreenUtil.h"
#include "utils/ColorUtil.h"

FailScene::FailScene(void)
{
	Vec2 points[] = {	Vec2(0, 0), 
						Vec2(0, 140),
						Vec2(400, 140),
						Vec2(400, 0) };
	DrawNode* draw = DrawNode::create();
	//±³¾°
	draw->drawPolygon(points, 4, ColorUtil::getColor4F(0x00 , 0xAD , 0xFF, 0xFF),
								0, ColorUtil::getColor4F(0x00, 0xDA, 0xFF, 0xFF));

	this->addChild(draw);
	draw->setAnchorPoint(Point(.5, .5));
	draw->setPositionX(ScreenUtil::getCenter().x - 200);
	draw->setPositionY(ScreenUtil::getCenter().y - 140);

	Vec2 points2[] = {	Vec2(0, 0), 
						Vec2(0, 150),
						Vec2(230, 150),
						Vec2(230, 0) };
	DrawNode* draw2 = DrawNode::create();
	//±³¾°
	draw2->drawPolygon(points2, 4, ColorUtil::getColor4F(0x00 , 0xAD , 0xFF, 0xFF),
								0, ColorUtil::getColor4F(0x00, 0xDA, 0xFF, 0xFF));

	this->addChild(draw2);
	draw2->setAnchorPoint(Point(.5, .5));
	draw2->setPositionX(ScreenUtil::getCenter().x - 115);
	draw2->setPositionY(ScreenUtil::getCenter().y + 40);

	LabelTTF* scoreTxt = LabelTTF::create("Score:", "Arial", 30);
	scoreTxt->setPosition(Point(draw2->getPositionX() + scoreTxt->getContentSize().width *.5 + 10, 
								draw2->getPositionY() + 120));
	this->addChild(scoreTxt);

	LabelTTF* scoreValTxt = LabelTTF::create("0", "Arial", 90);
	scoreValTxt->setPositionX(draw2->getPositionX() + 115);
	scoreValTxt->setPositionY(draw2->getPositionY() + 60);
	scoreValTxt->setTag(scoreValTxtTag);
	this->addChild(scoreValTxt);

	LabelTTF* replayTxt = LabelTTF::create("Replay", "Arial", 45);
	MenuItemLabel* replayBtn = MenuItemLabel::create(replayTxt);
	replayBtn->setTag(replayBtnTag);

	LabelTTF* shareTxt = LabelTTF::create("Share", "Arial", 45);
	MenuItemLabel* shareBtn = MenuItemLabel::create(shareTxt);

	Menu* menu = Menu::create(replayBtn, shareBtn,  NULL);
	menu->setPositionX(ScreenUtil::getCenter().x);
	menu->setPositionY(ScreenUtil::getCenter().y - 70);
	menu->alignItemsHorizontallyWithPadding(50);
	menu->setTag(menuTag);
	this->addChild(menu);
}


FailScene::~FailScene(void)
{
}

void FailScene::setScore( int score )
{
	String* str = String::createWithFormat("%d", score);
	LabelTTF* scoreValTxt = (LabelTTF* )this->getChildByTag(scoreValTxtTag);
	scoreValTxt->setString(str->_string);
}
