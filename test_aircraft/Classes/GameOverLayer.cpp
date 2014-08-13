#include "GameOverLayer.h"

int GameOverLayer::highest_record = 0;

GameOverLayer::GameOverLayer() {
    score = 0;
    highest_score_item = NULL;
}

GameOverLayer::~GameOverLayer() {}

GameOverLayer *GameOverLayer::create(int passScore) {
    GameOverLayer *result = new GameOverLayer();
    result->score = passScore;

    if(result && result->init()) {
        result->autorelease();
        return result;
    } else {
        delete result;
        result = NULL;
        return NULL;
    }
}

bool GameOverLayer::init() {
    bool result = false;

    do {
        CC_BREAK_IF(!CCLayer::init());
        CCSize winSize = CCDirector::sharedDirector()->getWinSize();

        CCSprite *background = CCSprite::createWithSpriteFrameName("gameover.png");
        background->setPosition(ccp(winSize.width / 2, winSize.height / 2));
        this->addChild(background);

        CCSprite *normalBackToGame = CCSprite::createWithSpriteFrameName("btn_finish.png");
        CCSprite *pressedBackToGame = CCSprite::createWithSpriteFrameName("btn_finish.png");

        CCSize image_size = normalBackToGame->getContentSize();

        CCMenuItemImage *button_back = CCMenuItemImage::create();
        button_back->initWithNormalSprite(normalBackToGame, pressedBackToGame, NULL, this, menu_selector(GameOverLayer::menuBackCallBack));
        button_back->setPosition(ccp(winSize.width - image_size.width / 2 - 10, image_size.height / 2 + 10));
        CCMenu *menu = CCMenu::create(button_back, NULL);
        menu->setPosition(CCPointZero);
        this->addChild(menu);

        CCString *strScore = CCString::createWithFormat("%d", score);
        CCLabelBMFont *finalScore = CCLabelBMFont::create(strScore->m_sString.c_str(), "font/font.fnt");
        finalScore->setColor(ccc3(143, 146, 147));
        finalScore->setPosition(ccp(winSize.width / 2, winSize.height / 2));
        this->addChild(finalScore);

        CCDelayTime *delay = CCDelayTime::create(1.0f);
        CCCallFunc *showAD = CCCallFunc::create(this, callfunc_selector(GameOverLayer::showAD));
        finalScore->runAction(CCSequence::create(delay, CCScaleTo::create(1.0f, 3.0f), CCScaleTo::create(0.3f, 2.0f), showAD, NULL));

        result = true;
    } while (0);

    return result;
}

void GameOverLayer::menuBackCallBack(CCObject *sender) {}
void GameOverLayer::keyBackClicked() {}

void GameOverLayer::showAD() {}