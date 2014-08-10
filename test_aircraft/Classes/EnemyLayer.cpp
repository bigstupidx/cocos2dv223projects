#include "EnemyLayer.h"
#include "GameLayer.h"

EnemyLayer::EnemyLayer() {
	enemy1_array = CCArray::create();
	enemy1_array->retain();

	enemy2_array = CCArray::create();
	enemy2_array->retain();

	enemy3_array = CCArray::create();
	enemy3_array->retain();

	enemy1SpriteFrame = NULL;
	enemy2SpriteFrame = NULL;
	enemy3SpriteFrame_1 = NULL;
	enemy3SpriteFrame_2 = NULL;
}

EnemyLayer::~EnemyLayer() {
	enemy1_array->release();
	enemy1_array = NULL;

	enemy2_array->release();
	enemy2_array = NULL;

	enemy3_array->release();
	enemy3_array = NULL;
}

bool EnemyLayer::init() {
	bool result = false;

	do {
		CC_BREAK_IF(!CCLayer::init());

		CCSpriteFrameCache *cache = CCSpriteFrameCache::sharedSpriteFrameCache();

		enemy1SpriteFrame = cache->spriteFrameByName("enemy1.png");
		enemy2SpriteFrame = cache->spriteFrameByName("enemy2.png");
		enemy3SpriteFrame_1 = cache->spriteFrameByName("enemy3_n1.png");
		enemy3SpriteFrame_2 = cache->spriteFrameByName("enemy3_n2.png");

		CCAnimation *animation1 = CCAnimation::create();
		animation1->setDelayPerUnit(0.1f);
		animation1->addSpriteFrame(cache->spriteFrameByName("enemy1_down1.png"));
		animation1->addSpriteFrame(cache->spriteFrameByName("enemy1_down2.png"));
		animation1->addSpriteFrame(cache->spriteFrameByName("enemy1_down3.png"));
		animation1->addSpriteFrame(cache->spriteFrameByName("enemy1_down4.png"));

		CCAnimation *animation2 = CCAnimation::create();
		animation2->setDelayPerUnit(0.1f);
		animation2->addSpriteFrame(cache->spriteFrameByName("enemy2_down1.png"));
		animation2->addSpriteFrame(cache->spriteFrameByName("enemy2_down2.png"));
		animation2->addSpriteFrame(cache->spriteFrameByName("enemy2_down3.png"));
		animation2->addSpriteFrame(cache->spriteFrameByName("enemy2_down4.png"));

		CCAnimation *animation3 = CCAnimation::create();
		animation3->setDelayPerUnit(0.1f);
		animation3->addSpriteFrame(cache->spriteFrameByName("enemy3_down1.png"));
		animation3->addSpriteFrame(cache->spriteFrameByName("enemy3_down2.png"));
		animation3->addSpriteFrame(cache->spriteFrameByName("enemy3_down3.png"));
		animation3->addSpriteFrame(cache->spriteFrameByName("enemy3_down4.png"));
		animation3->addSpriteFrame(cache->spriteFrameByName("enemy3_down5.png"));
		animation3->addSpriteFrame(cache->spriteFrameByName("enemy3_down6.png"));

		CCAnimationCache::sharedAnimationCache()->addAnimation(animation1, "enemy1blowup");
		CCAnimationCache::sharedAnimationCache()->addAnimation(animation2, "enemy2blowup");
		CCAnimationCache::sharedAnimationCache()->addAnimation(animation3, "enemy3blowup");

		this->schedule(schedule_selector(EnemyLayer::addEnemy1), 0.5f);
		this->schedule(schedule_selector(EnemyLayer::addEnemy2), 3.0f);
		this->schedule(schedule_selector(EnemyLayer::addEnemy3), 6.0f);

		result = true;
	} while(0);

	return result;
}

void EnemyLayer::addEnemy1(float delta) {
	addEnemy(ENEMY1_MAXLIFE);
}

void EnemyLayer::addEnemy2(float delta) {
	addEnemy(ENEMY2_MAXLIFE);
}

void EnemyLayer::addEnemy3(float delta) {
	addEnemy(ENEMY3_MAXLIFE);
}

void EnemyLayer::addEnemy(int type) {
	Enemy *enemy = Enemy::create();
	CCSpriteFrameCache *cache  = CCSpriteFrameCache::sharedSpriteFrameCache();

	if(type == ENEMY1_MAXLIFE) {
		enemy->bindSprite(CCSprite::createWithSpriteFrame(enemy1SpriteFrame), ENEMY1_MAXLIFE);
		this->enemy1_array->addObject(enemy);

	} else if(type == ENEMY2_MAXLIFE) {
		enemy->bindSprite(CCSprite::createWithSpriteFrame(enemy2SpriteFrame), ENEMY2_MAXLIFE);
		this->enemy2_array->addObject(enemy);

	} else if(type == ENEMY3_MAXLIFE) {
		CCSprite *enemy3 = CCSprite::createWithSpriteFrame(cache->spriteFrameByName("enemy3_n1.png"));

		CCAnimation *animation = CCAnimation::create();
		animation->setDelayPerUnit(0.2f);
		animation->addSpriteFrame(cache->spriteFrameByName("enemy3_n1.png"));
		animation->addSpriteFrame(cache->spriteFrameByName("enemy3_n2.png"));
		enemy3->runAction(CCRepeatForever::create(CCAnimate::create(animation)));

		enemy->bindSprite(enemy3, ENEMY3_MAXLIFE);
		this->enemy3_array->addObject(enemy);
	}

	CCSize enemySize = enemy->getSprite()->getContentSize();
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	int rangeX = winSize.width - enemySize.width;
	int x = (rand() % rangeX) + enemySize.width / 2;
	enemy->setPosition(x, winSize.height + enemySize.height / 2);
	this->addChild(enemy);

	float minDuration, maxDuration;

	switch(GameLayer::getLevel()) {
	case EASY:
		if(type == ENEMY1_MAXLIFE) {
			minDuration = 2.0;
			maxDuration = 4.0;
		} else if(type == ENEMY2_MAXLIFE) {
			minDuration = 3.0;
			maxDuration = 6.0;
		} else {
			minDuration = 4.0;
			maxDuration = 8.0;
		}

		break;

	case MIDDLE:
		if(type == ENEMY1_MAXLIFE) {
			minDuration = 1.8f;
			maxDuration = 3.6f;
		} else if(type == ENEMY2_MAXLIFE) {
			minDuration = 2.7f;
			maxDuration = 5.4f;
		} else {
			minDuration = 3.6f;
			maxDuration = 7.2f;
		}

		break;

	case HARD:
		if(type == ENEMY1_MAXLIFE) {
			minDuration = 1.6f;
			maxDuration = 3.2f;
		} else if(type == ENEMY2_MAXLIFE) {
			minDuration = 2.5f;
			maxDuration = 5.0f;
		} else {
			minDuration = 3.2f;
			maxDuration = 6.4f;
		}


		break;

	default:
		if(type == ENEMY1_MAXLIFE) {
			minDuration = 2.0;
			maxDuration = 4.0;
		} else if(type == ENEMY2_MAXLIFE) {
			minDuration = 3.0;
			maxDuration = 6.0;
		} else {
			minDuration = 4.0;
			maxDuration = 8.0;
		}

		break;
	}

	int range_duration = maxDuration - minDuration;
	int duration = rand() % range_duration + minDuration;

	CCFiniteTimeAction *action1 = CCMoveTo::create(duration, ccp(x,  - enemySize.height / 2));
	CCFiniteTimeAction *action2 = NULL;

	if(type == ENEMY1_MAXLIFE)
		action2 = CCCallFuncN::create(this, callfuncN_selector(EnemyLayer::enemy1MoveFinished));
	else if(type == ENEMY2_MAXLIFE)
		action2 = CCCallFuncN::create(this, callfuncN_selector(EnemyLayer::enemy2MoveFinished));
	else
		action2 = CCCallFuncN::create(this, callfuncN_selector(EnemyLayer::enemy3MoveFinished));

	CCSequence *sequence = CCSequence::create(action1, action2, NULL);
	enemy->runAction(sequence);
}

void EnemyLayer::enemy1MoveFinished(CCNode *pTarget) {
	Enemy *enemy = (Enemy *)pTarget;

	if(enemy) {
		this->enemy1_array->removeObject(enemy);
		this->removeChild(enemy);
	}
}

void EnemyLayer::enemy2MoveFinished(CCNode *pTarget) {
	Enemy *enemy = (Enemy *)pTarget;

	if(enemy) {
		this->enemy2_array->removeObject(enemy);
		this->removeChild(enemy);
	}
}

void EnemyLayer::enemy3MoveFinished(CCNode *pTarget) {
	Enemy *enemy = (Enemy *)pTarget;

	if(enemy) {
		this->enemy3_array->removeObject(enemy);
		this->removeChild(enemy);
	}
}

void EnemyLayer::enemy1BlowUp(Enemy *enemy) {
	CCAnimation *animation = CCAnimationCache::sharedAnimationCache()->animationByName("enemy1blowup");
	enemy->getSprite()->runAction(CCSequence::create(
	                                  CCAnimate::create(animation),
	                                  CCCallFuncND::create(this,
	                                          callfuncND_selector(EnemyLayer::removeEnemy1), (void *)enemy),
	                                  NULL));
}
void EnemyLayer::enemy2BlowUp(Enemy *enemy) {
	CCAnimation *animation = CCAnimationCache::sharedAnimationCache()->animationByName("enemy2blowup");
	enemy->getSprite()->runAction(CCSequence::create(
	                                  CCAnimate::create(animation),
	                                  CCCallFuncND::create(this,
	                                          callfuncND_selector(EnemyLayer::removeEnemy2), (void *)enemy),
	                                  NULL));
}
void EnemyLayer::enemy3BlowUp(Enemy *enemy) {
	CCAnimation *animation = CCAnimationCache::sharedAnimationCache()->animationByName("enemy3blowup");
	enemy->getSprite()->runAction(CCSequence::create(
	                                  CCAnimate::create(animation),
	                                  CCCallFuncND::create(this,
	                                          callfuncND_selector(EnemyLayer::removeEnemy3), (void *)enemy),
	                                  NULL));
}

void EnemyLayer::removeEnemy1(CCNode *pTarget, void *data) {
	Enemy *enemy = (Enemy *)data;

	if(enemy != NULL) {
		enemy1_array->removeObject(enemy);
		this->removeChild(enemy);
	}
}

void EnemyLayer::removeEnemy2(CCNode *pTarget, void *data) {
	Enemy *enemy = (Enemy *)data;

	if(enemy != NULL) {
		enemy2_array->removeObject(enemy);
		this->removeChild(enemy);
	}
}

void EnemyLayer::removeEnemy3(CCNode *pTarget, void *data) {
	Enemy *enemy = (Enemy *)data;

	if(enemy != NULL) {
		enemy3_array->removeObject(enemy);
		this->removeChild(enemy);
	}
}

void EnemyLayer::removeAllEnemy1() {
	CCObject *object;
	CCARRAY_FOREACH(enemy1_array, object) {
		Enemy *enemy = (Enemy *)object;

		if(!enemy)break;

		if(enemy->getLife() > 0) {
			enemy1BlowUp(enemy);
		}
	}
}

void EnemyLayer::removeAllEnemy2() {
	CCObject *object = NULL;
	CCARRAY_FOREACH(enemy2_array, object) {
		Enemy *enemy = (Enemy *)object;

		if(!enemy)break;

		if(enemy->getLife() > 0) {
			enemy2BlowUp(enemy);
		}
	}
}

void EnemyLayer::removeAllEnemy3() {
	CCObject *object = NULL;
	CCARRAY_FOREACH(enemy3_array, object) {
		Enemy *enemy = (Enemy *)object;

		if(!enemy)break;

		if(enemy->getLife() > 0) {
			enemy3BlowUp(enemy);
		}
	}
}

void EnemyLayer::removeAllEnemy() {
	removeAllEnemy1();
	removeAllEnemy2();
	removeAllEnemy3();
}