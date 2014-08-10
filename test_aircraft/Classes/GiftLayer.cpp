#include "GiftLayer.h"

GiftLayer::GiftLayer() {
    gift_bomb_array = CCArray::create();
    gift_bomb_array->retain();

    gift_bullet_array = CCArray::create();
    gift_bullet_array->retain();
}

GiftLayer::~GiftLayer() {
    gift_bullet_array->release();
    gift_bullet_array = NULL;

    gift_bomb_array->release();
    gift_bomb_array = NULL;
}

bool GiftLayer::init() {
    bool result = false;

    do {
        this->schedule(schedule_selector(GiftLayer::addGiftBomb), 0.5f);
        this->schedule(schedule_selector(GiftLayer::addGiftBullet), 1.0f);
        result = true;
    } while(0);

    return result;
}

void GiftLayer::addGiftBullet(float dt) {
    addGift(GIFT_BULLET);
}

void GiftLayer::addGiftBomb(float dt) {
    addGift(GIFT_BOMB);
}

void GiftLayer::addGift(int type) {
    CCSprite *gift = NULL;

    if(type == GIFT_BOMB) {
        gift = CCSprite::createWithSpriteFrame(
                   CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("ufo1.png"));
        this->gift_bomb_array->addObject(gift);
    } else {
        gift = CCSprite::createWithSpriteFrame(
                   CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("ufo2.png"));
        this->gift_bullet_array->addObject(gift);
    }

    CCSize win_size = CCDirector::sharedDirector()->getWinSize();
    CCSize gif_size = gift->getContentSize();

    int range_x = win_size.width - gif_size.width;

    gift->setPosition(ccp(rand() % range_x + gif_size.width / 2,
                          win_size.height + gif_size.height / 2));
    this->addChild(gift);

    CCMoveBy *action1 = CCMoveBy::create(0.5f, CCPointMake(0, -150));
    CCMoveBy *action2 = CCMoveBy::create(0.3f, CCPointMake(0, 100));
    CCMoveBy *action3 = CCMoveBy::create(1.0f, CCPointMake(0, -win_size.height - gif_size.height / 2));
    CCCallFuncN *action4 = NULL;

    if(type == GIFT_BULLET)
        action4 = CCCallFuncN::create(this, callfuncN_selector(GiftLayer::giftBulletMoveFinished));
    else
        action4 = CCCallFuncN::create(this, callfuncN_selector(GiftLayer::giftBombMoveFinished));

    gift->runAction(CCSequence::create(action1, action2, action3, action4, NULL));
}

void GiftLayer::giftBombMoveFinished(CCNode *pSender) {
    CCSprite *gift = (CCSprite *)pSender;
    this->removeChild(gift);
    this->gift_bomb_array->removeObject(gift);
}

void GiftLayer::giftBulletMoveFinished(CCNode *pSender) {
    CCSprite *gift = (CCSprite *)pSender;
    this->removeChild(gift);
    this->gift_bullet_array->removeObject(gift);
}

void GiftLayer::removeGiftBomb(CCSprite *gift) {
    this->removeChild(gift);
    this->gift_bomb_array->removeObject(gift);
}

void GiftLayer::removeGiftBullet(CCSprite *gift) {
    this->removeChild(gift);
    this->gift_bullet_array->removeObject(gift);
}