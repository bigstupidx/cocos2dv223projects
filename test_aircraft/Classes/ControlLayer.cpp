#include "ControlLayer.h"

ControlLayer::ControlLayer() {}

ControlLayer::~ControlLayer() {}

bool ControlLayer::init() {
    bool result = false;

    do {
        CC_BREAK_IF(!CCLayer::init());
        CCSize winSize = CCDirector::sharedDirector()->getWinSize();

        CCSprite *normalPause = CCSprite::createWithSpriteFrameName("game_pause_nor.png");
        CCSprite *pressedPause = CCSprite::createWithSpriteFrameName("game_pause_pressed.png");
        CCSize image_size = normalPause->getContentSize();
        button_pause = CCMenuItemImage::create();
        button_pause->initWithNormalSprite(normalPause, pressedPause, NULL, this, menu_selector(ControlLayer::menuPauseCallback));
        button_pause->setPosition(ccp(image_size.width / 2 + 10, winSize.height - image_size.height / 2 - 10));
        CCMenu *menuPause = CCMenu::create(button_pause, NULL);
        menuPause->setPosition(CCPointZero);
        this->addChild(menuPause);

        score_item = CCLabelBMFont::create("0", "font/font.fnt");
        score_item->setColor(ccc3(143, 146, 147));
        score_item->setAnchorPoint(ccp(0, 0.5f));
        score_item->setPosition(ccp(button_pause->getPositionX() + image_size.width / 2 + 5, button_pause->getPositionY()));
        this->addChild(score_item);

        result = true;
    } while (0);

    return result;
}

void ControlLayer::menuPauseCallback(CCObject *sender) {
    if(!CCDirector::sharedDirector()->isPaused()) {
        CCDirector::sharedDirector()->pause();
        button_pause->setNormalSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("game_resume_nor.png"));
        button_pause->setSelectedSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("game_resume_pressed.png"));
        no_touch_layer = NoTouchLayer::create();
        this->addChild(no_touch_layer);
    } else {
        CCDirector::sharedDirector()->resume();
        button_pause->setNormalSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("game_pause_nor.png"));
        button_pause->setSelectedSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("game_pause_pressed.png"));
        this->removeChild(no_touch_layer, true);
    }
}

void ControlLayer::updateScore(int score) {
    if(score >= 0 && score < MAX_SCORE) {
        CCString *strScore = CCString::createWithFormat("%d", score);
        score_item->setString(strScore->m_sString.c_str());
    }
}