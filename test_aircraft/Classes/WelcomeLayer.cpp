#include "WelcomeLayer.h"
#include "GameScene.h"
#include "GameOverLayer.h"

WelcomeLayer::WelcomeLayer() {}
WelcomeLayer::~WelcomeLayer() {}

bool WelcomeLayer::init() {
    bool result = false;

    do {
        CC_BREAK_IF(!CCLayer::init());
        CCSpriteFrameCache *cache = CCSpriteFrameCache::sharedSpriteFrameCache();
        cache->addSpriteFramesWithFile("shoot.plist");
        cache->addSpriteFramesWithFile("shoot_background.plist");

        CCSize winSize = CCDirector::sharedDirector()->getWinSize();

        CCSprite *background = CCSprite::createWithSpriteFrameName("background.png");
        background->setPosition(ccp(winSize.width / 2, winSize.height / 2));
        this->addChild(background);

        CCSprite *copyright = CCSprite::createWithSpriteFrameName("shoot_copyright.png");
        copyright->setAnchorPoint(ccp(0.5, 0));
        copyright->setPosition(ccp(winSize.width / 2, winSize.height / 2));
        this->addChild(copyright);

        CCSprite *loading = CCSprite::createWithSpriteFrameName("game_loading1.png");
        loading->setPosition(ccp(winSize.width / 2, winSize.height / 2 - 40));
        this->addChild(loading);

        CCAnimation *animation = CCAnimation::create();
        animation->setDelayPerUnit(0.2f);
        animation->addSpriteFrame(cache->spriteFrameByName("game_loading1.png"));
        animation->addSpriteFrame(cache->spriteFrameByName("game_loading2.png"));
        animation->addSpriteFrame(cache->spriteFrameByName("game_loading3.png"));
        animation->addSpriteFrame(cache->spriteFrameByName("game_loading4.png"));
        loading->runAction(CCSequence::create(CCAnimate::create(animation), CCCallFuncN::create(this, callfuncN_selector(WelcomeLayer::loadingDone)), NULL));

        getHighestHistoryScore();

        this->setKeypadEnabled(true);

        result = true;
    } while (0);

    return result;
}

void WelcomeLayer::loadingDone(CCNode *node) {
    CCScene *nextScene = GameScene::create();
    CCTransitionMoveInB *animateScene = CCTransitionMoveInB::create(0.5f, nextScene);
    CCDirector::sharedDirector()->replaceScene(animateScene);
}

void WelcomeLayer::keyBackClicked() {
    CCDirector::sharedDirector()->end();
}

bool WelcomeLayer::isHaveSaveLife() {
    if(!CCUserDefault::sharedUserDefault()->getBoolForKey("saved_xml")) {
        CCUserDefault::sharedUserDefault()->setBoolForKey("saved_xml", true);
        CCUserDefault::sharedUserDefault()->setIntegerForKey("highest", 0);
        CCUserDefault::sharedUserDefault()->flush();
        return false;
    }

    return true;
}

void WelcomeLayer::getHighestHistoryScore() {
    if(isHaveSaveLife()) {
        GameOverLayer::highest_record = CCUserDefault::sharedUserDefault()->getIntegerForKey("highest", 0);
    }
}