#ifndef __BULLET_LAYER_H__
#define __BULLET_LAYER_H__

#include "cocos2d.h"

USING_NS_CC;

class BulletLayer: public CCLayer {
public:
	BulletLayer();
	~BulletLayer();

	CREATE_FUNC(BulletLayer);

	virtual bool init();

	void addBullet(float delta);
	void bulletMoveFinished(CCNode *pSender);

	void startShoot(float delay = 0);
	void stopShoot();
	void removeBullet(CCSprite *bullet);

public:
	CCArray *bullet_array;
private:
	CCSpriteBatchNode *bullet_batch;
};

#endif