#include "MultiBulletLayer.h"
#include "PlaneLayer.h"
#include "SimpleAudioEngine.h"

MultiBulletLayer::MultiBulletLayer() {
	bullet_batch = NULL;

	bullet_array = CCArray::create();
	bullet_array->retain();
}

MultiBulletLayer::~MultiBulletLayer() {
	bullet_array->release();
	bullet_array = NULL;
}

bool MultiBulletLayer::init() {
	bool result = false;

	do {
		CC_BREAK_IF(!CCLayer::init());
		CCTexture2D *texture = CCTextureCache::sharedTextureCache()->textureForKey("shoot.png");
		bullet_batch = CCSpriteBatchNode::createWithTexture(texture);
		this->addChild(bullet_batch);
		result = true;
	} while(0);

	return result;
}

void MultiBulletLayer::startShoot(float delay /* = 0 */) {
	this->schedule(schedule_selector(MultiBulletLayer::addBullet), 0.2f, 30, 0.0f);
}

void MultiBulletLayer::stopShoot() {
	this->unschedule(schedule_selector(MultiBulletLayer::addBullet));
}

void MultiBulletLayer::addBullet(float delta) {
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sound/bullet.mp3");
	CCSprite *bulletLeft = CCSprite::createWithSpriteFrameName("bullet2.png");
	CCSprite *bulletRight = CCSprite::createWithSpriteFrameName("bullet2.png");
	bullet_batch->addChild(bulletLeft);
	bullet_batch->addChild(bulletRight);
	bullet_array->addObject(bulletLeft);
	bullet_array->addObject(bulletRight);

	CCPoint planePosition = PlaneLayer::sharedPlane->getChildByTag(PLANE_TAG)->getPosition();
	CCPoint bulletLeftPosition = ccp(planePosition.x - 33, planePosition.y + 35);
	CCPoint bulletRightPosition = ccp(planePosition.x + 33, planePosition.y + 35);
	bulletLeft->setPosition(bulletLeftPosition);
	bulletRight->setPosition(bulletRightPosition);

	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	CCSize bulletSize = bulletLeft->getContentSize();

	float length = winSize.height + bulletSize.height / 2 - bulletLeftPosition.y;
	float velocity = 420 / 1;
	float realMoveDuration = length / velocity;


	CCFiniteTimeAction *action_left1 = CCMoveTo::create(realMoveDuration, ccp(bulletLeftPosition.x,
	                                   winSize.height + bulletSize.height / 2));
	CCFiniteTimeAction *action_left2 = CCCallFuncN::create(this,
	                                   callfuncN_selector(MultiBulletLayer::bulletMoveFinished));

	CCFiniteTimeAction *action_right1 = CCMoveTo::create(realMoveDuration, ccp(bulletRightPosition.x,
	                                    winSize.height + bulletSize.height / 2));
	CCFiniteTimeAction *action_right2 = CCCallFuncN::create(this,
	                                    callfuncN_selector(MultiBulletLayer::bulletMoveFinished));

	bulletLeft->runAction(CCSequence::create(action_left1, action_left2, NULL));
	bulletRight->runAction(CCSequence::create(action_right1, action_right2, NULL));
}

void MultiBulletLayer::bulletMoveFinished(CCNode *pSender) {
	CCSprite *bullet = (CCSprite *)pSender;
	bullet_array->removeObject(bullet);
	bullet_batch->removeChild(bullet, true);
}

void MultiBulletLayer::removeBullet(CCSprite *bullet) {
	if(bullet != NULL) {
		this->bullet_array->removeObject(bullet);
		this->bullet_batch->removeChild(bullet, true);
	}
}