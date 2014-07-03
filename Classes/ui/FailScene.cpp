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

	LabelTTF* scoreTxt = LabelTTF::create("Score:", "Arial", 45);
	scoreTxt->setAnchorPoint(Point(0, .5));
	scoreTxt->setPosition(Point(draw2->getPositionX() + 10, 
								draw2->getPositionY() + 110));
	this->addChild(scoreTxt);

	LabelTTF* bestScoreTxt = LabelTTF::create("Best:", "Arial", 45);
	bestScoreTxt->setAnchorPoint(Point(0, .5));
	bestScoreTxt->setPosition(Point(scoreTxt->getPositionX(), 
									draw2->getPositionY() + 50));
	this->addChild(bestScoreTxt);

	LabelTTF* scoreValTxt = LabelTTF::create("0", "Arial", 45);
	scoreValTxt->setPositionX(scoreTxt->getPositionX() + scoreTxt->getContentSize().width + 25);
	scoreValTxt->setPositionY(scoreTxt->getPositionY());
	scoreValTxt->setTag(scoreValTxtTag);
	this->addChild(scoreValTxt);

	LabelTTF* bestScoreValTxt = LabelTTF::create("0", "Arial", 45);
	bestScoreValTxt->setPositionX(scoreValTxt->getPositionX());
	bestScoreValTxt->setPositionY(bestScoreTxt->getPositionY());
	bestScoreValTxt->setTag(bestScoreValTxtTag);
	this->addChild(bestScoreValTxt);

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

void FailScene::setScore( int score, int bestScore)
{
	String* str = String::createWithFormat("%d", score);
	LabelTTF* scoreValTxt = (LabelTTF* )this->getChildByTag(scoreValTxtTag);
	scoreValTxt->setString(str->_string);

	str = String::createWithFormat("%d", bestScore);
	LabelTTF* bestScoreValTxt = (LabelTTF* )this->getChildByTag(bestScoreValTxtTag);
	bestScoreValTxt->setString(str->_string);
}
