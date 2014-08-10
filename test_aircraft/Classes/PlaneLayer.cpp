#include "PlaneLayer.h"

PlaneLayer::PlaneLayer() {}
PlaneLayer::~PlaneLayer() {}

PlaneLayer *PlaneLayer::sharedPlane = NULL;

PlaneLayer *PlaneLayer::create() {
	PlaneLayer *result = new PlaneLayer();

	if(result && result->init()) {
		result->autorelease();
		sharedPlane = result;
		return result;
	} else {
		CC_SAFE_DELETE(result);
		return NULL;
	}
}

void PlaneLayer::moveTo(CCPoint location) {
	if(is_alive && !CCDirector::sharedDirector()->isPaused()) {
		CCSize winSize = CCDirector::sharedDirector()->getWinSize();
		CCSize flySize = this->getChildByTag(PLANE_TAG)->getContentSize();

		if(location.x < flySize.width / 2)
			location.x = flySize.width / 2;

		if(location.y < flySize.height / 2)
			location.y = flySize.height / 2;

		if(location.x > winSize.width - flySize.width / 2)
			location.x = winSize.width - flySize.width / 2;

		if(location.y > winSize.height - flySize.height / 2)
			location.y = winSize.height - flySize.height / 2;

		this->getChildByTag(PLANE_TAG)->setPosition(location);
	}
}

void PlaneLayer::blowUp(int passScore) {

}

void PlaneLayer::removePlane() {

}

bool PlaneLayer::init() {
	bool result = false;

	do {
		CC_BREAK_IF(!CCLayer::init());

		CCSize winSize = CCDirector::sharedDirector()->getWinSize();

		CCSprite *plane = CCSprite::createWithSpriteFrame(
		                      CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("hero1.png"));
		plane->setPosition(ccp(winSize.width / 2, plane->getContentSize().height / 2));
		this->addChild(plane, 0, PLANE_TAG);

		CCBlink *blink = CCBlink::create(1, 3);

		CCAnimation *animation = CCAnimation::create();
		animation->setDelayPerUnit(0.1f);
		animation->addSpriteFrame(
		    CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("hero1.png"));
		animation->addSpriteFrame(
		    CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("hero2.png"));

		plane->runAction(blink);
		plane->runAction(CCRepeatForever::create(CCAnimate::create(animation)));

		result = true;
	} while(0);

	return result;
}