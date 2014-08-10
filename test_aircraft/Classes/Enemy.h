#ifndef __ENEMY_H__
#define __ENEMY_H__

#include "cocos2d.h"

USING_NS_CC;

class Enemy: public CCNode {
public:
	Enemy();
	~Enemy();

	static Enemy *create();
	void bindSprite(CCSprite *sprite, int life);
	CCSprite *getSprite();

	int getLife();
	void loseLife();
	CCRect getBoundingBox();

private:
	CCSprite *sprite;
	int life;
};

#endif