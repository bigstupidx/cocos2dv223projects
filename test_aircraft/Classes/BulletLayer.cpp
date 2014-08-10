#include "BulletLayer.h"
#include "PlaneLayer.h"

BulletLayer::BulletLayer() {
	bullet_array = CCArray::create();
	bullet_array->retain();
}

BulletLayer::~BulletLayer() {
	bullet_array->release();
	bullet_array = NULL;
}

bool BulletLayer::init() {
	bool result = false;

	do {
		CC_BREAK_IF(!CCLayer::init());
		CCTexture2D *bullet_texture = CCTextureCache::sharedTextureCache()->textureForKey("shoot.png");
		bullet_batch = CCSpriteBatchNode::createWithTexture(bullet_texture);
		this->addChild(bullet_batch);
		result = true;
	} while(0);

	return result;
}

void BulletLayer::addBullet(float delta) {
	CCSprite *bullet = CCSprite::createWithSpriteFrameName("bullet1.png");

	bullet_batch->addChild(bullet);
	bullet_array->addObject(bullet);

	CCPoint planePosition = PlaneLayer::sharedPlane->getChildByTag(PLANE_TAG)->getPosition();
	CCPoint bulletPosition = ccp(planePosition.x,
	                             planePosition.y
	                             + PlaneLayer::sharedPlane->getChildByTag(PLANE_TAG)->getContentSize().height / 2);
	bullet->setPosition(bulletPosition);

	float length = CCDirector::sharedDirector()->getWinSize().height + bullet->getContentSize().height /
	               2 - bulletPosition.y;
	float velocity = 320 / 1;

	float realMoveDuration = length / velocity;

	CCFiniteTimeAction *action1 = CCMoveTo::create(realMoveDuration,
	                              ccp(bulletPosition.x, CCDirector::sharedDirector()->getWinSize().height +
	                                  bullet->getContentSize().height / 2));
	CCFiniteTimeAction *action2 = CCCallFuncN::create(this,
	                              callfuncN_selector(BulletLayer::bulletMoveFinished));

	CCSequence *sequence = CCSequence::create(action1, action2, NULL);
	bullet->runAction(sequence);
}

void BulletLayer::bulletMoveFinished(CCNode *pSender) {
	CCSprite *bullet = (CCSprite *) pSender;
	this->bullet_array->removeObject(bullet);
	this->bullet_batch->removeChild(bullet, true);
}

void BulletLayer::startShoot(float delay) {
	this->schedule(schedule_selector(BulletLayer::addBullet), 0.1f, kCCRepeatForever, delay);
}

void BulletLayer::stopShoot() {
	this->unschedule(schedule_selector(BulletLayer::addBullet));
}

void BulletLayer::removeBullet(CCSprite *bullet) {
	if(bullet == NULL) return;

	this->bullet_array->removeObject(bullet);
	this->bullet_batch->removeChild(bullet , true);
}