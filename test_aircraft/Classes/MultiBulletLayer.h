#ifndef __MULTI_BULLET_LAYER_H__
#define __MULTI_BULLET_LAYER_H__

#include <cocos2d.h>

USING_NS_CC;

class MultiBulletLayer: public CCLayer {
public:
	MultiBulletLayer();
	~MultiBulletLayer();

	CREATE_FUNC(MultiBulletLayer);

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