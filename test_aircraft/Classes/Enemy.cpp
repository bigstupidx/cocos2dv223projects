#include "Enemy.h"
Enemy::Enemy() {
	sprite = NULL;
	life = 0;
}

Enemy::~Enemy() {}

Enemy *Enemy::create() {
	Enemy *result = new Enemy;
	result->autorelease();
	return result;
}

void Enemy::bindSprite(CCSprite *sprite, int life) {
	this->sprite = sprite;
	this->life = life;
	this->addChild(sprite);
}

CCSprite *Enemy::getSprite() {
	return sprite;
}
int Enemy::getLife() {
	return life;
}
void Enemy::loseLife() {
	--life;
}
CCRect Enemy::getBoundingBox() {
	CCRect rect = sprite->boundingBox();
	CCPoint pos = this->convertToWorldSpace(rect.origin);
	CCRect enemyRect(pos.x, pos.y, rect.size.width, rect.size.height);
	return enemyRect;
}