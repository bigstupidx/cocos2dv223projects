#include "GameLayer.h"

Level GameLayer::level = Level::EASY;

Level GameLayer::getLevel() {
    return level;
}

GameLayer::GameLayer() {
    background1 = NULL;
    background2 = NULL;
    bomb_count = 0;
}

GameLayer::~GameLayer() {
}

bool GameLayer::init() {
    bool result = false;

    do {
        CC_BREAK_IF(!CCLayer::init());
        CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("shoot_background.plist");
        background1 = CCSprite::createWithSpriteFrameName("background.png");
        background1->setAnchorPoint(ccp(0, 0));
        background1->setPosition(ccp(0, 0));
        this->addChild(background1);

        background2 = CCSprite::createWithSpriteFrameName("background.png");
        background2->setAnchorPoint(ccp(0, 0));
        background2->setPosition(ccp(0, background2->getContentSize().height - 2));
        this->addChild(background2);

        this->schedule(schedule_selector(GameLayer::backgroundMove));
        this->scheduleUpdate();

        this->planeLayer = PlaneLayer::create();
        this->addChild(planeLayer);

        this->bullet_layer = BulletLayer::create();
        this->addChild(bullet_layer);
        this->bullet_layer->startShoot();

        this->multi_bullet_layer = MultiBulletLayer::create();
        this->addChild(multi_bullet_layer);

        this->enemy_layer = EnemyLayer::create();
        this->addChild(enemy_layer);

        this->gift_layer = GiftLayer::create();
        this->addChild(gift_layer);

        this->control_layer = ControlLayer::create();
        this->addChild(control_layer);

        bomb_count = 0;
        score = 0;

        this->setTouchEnabled(true);

        result = true;
    } while(0);

    return result;
}

void GameLayer::update(float delta) {
    CCArray *bullet_to_delete = CCArray::create();
    bullet_to_delete->retain();

    CCArray *enemy_to_delete = CCArray::create();
    enemy_to_delete->retain();

    CCObject *bt, *et;
    //bullet enemy1
    CCARRAY_FOREACH(this->bullet_layer->bullet_array, bt) {
        CCSprite *bullet = (CCSprite *)bt;
        CCARRAY_FOREACH(this->enemy_layer->enemy1_array, et) {
            Enemy *enemy = (Enemy *)et;

            if(enemy->getBoundingBox().intersectsRect(bullet->boundingBox())) {
                int life = enemy->getLife();

                if(life > 1) {//alive
                    enemy->loseLife();
                    bullet_to_delete->addObject(bullet);
                } else if(life == 1) {//will die
                    enemy->loseLife();
                    bullet_to_delete->addObject(bullet);
                    enemy_to_delete->addObject(enemy);
                    score += SCORE_ENEMY1;
                    control_layer->updateScore(score);
                } else {//dying
                }
            }
        }
    }
    CCARRAY_FOREACH(enemy_to_delete, et) {
        Enemy *enemy = (Enemy *)et;
        this->enemy_layer->enemy1BlowUp(enemy);
    }
    CCARRAY_FOREACH(bullet_to_delete, bt) {
        CCSprite *bullet = (CCSprite *)bt;
        this->bullet_layer->removeBullet(bullet);
    }
    enemy_to_delete->removeAllObjects();
    bullet_to_delete->removeAllObjects();

    //bullet enemy2
    CCARRAY_FOREACH(this->bullet_layer->bullet_array, bt) {
        CCSprite *bullet = (CCSprite *)bt;
        CCARRAY_FOREACH(this->enemy_layer->enemy2_array, et) {
            Enemy *enemy = (Enemy *)et;

            if(enemy->getBoundingBox().intersectsRect(bullet->boundingBox())) {
                int life = enemy->getLife();

                if(life > 1) { //alive
                    enemy->loseLife();
                    bullet_to_delete->addObject(bullet);
                } else if(life == 1) {//will die
                    enemy->loseLife();
                    bullet_to_delete->addObject(bullet);
                    enemy_to_delete->addObject(enemy);
                    score += SCORE_ENEMY2;
                    control_layer->updateScore(score);
                } else {//dying. show dying animation.
                }
            }
        }
    }
    CCARRAY_FOREACH(enemy_to_delete, et) {
        Enemy *enemy = (Enemy *)et;
        this->enemy_layer->enemy2BlowUp(enemy);
    }
    CCARRAY_FOREACH(bullet_to_delete, bt) {
        CCSprite *bullet = (CCSprite *)bt;
        this->bullet_layer->removeBullet(bullet);
    }
    enemy_to_delete->removeAllObjects();
    bullet_to_delete->removeAllObjects();

    //bullet enemy3
    CCARRAY_FOREACH(this->bullet_layer->bullet_array, bt) {
        CCSprite *bullet = (CCSprite *)bt;
        CCARRAY_FOREACH(this->enemy_layer->enemy3_array, et) {
            Enemy *enemy = (Enemy *)et;

            if(enemy->getBoundingBox().intersectsRect(bullet->boundingBox())) {
                int life = enemy->getLife();

                if(life > 1) { //alive
                    enemy->loseLife();
                    bullet_to_delete->addObject(bullet);
                } else if(life == 1) {//will die
                    enemy->loseLife();
                    bullet_to_delete->addObject(bullet);
					enemy_to_delete->addObject(enemy);
					score += SCORE_ENEMY3;
					control_layer->updateScore(score);
                } else {//dying
                }
            }
        }
    }
    CCARRAY_FOREACH(enemy_to_delete, et) {
        Enemy *enemy = (Enemy *)et;
        this->enemy_layer->enemy3BlowUp(enemy);
    }
    CCARRAY_FOREACH(bullet_to_delete, bt) {
        CCSprite *bullet = (CCSprite *)bt;
        this->bullet_layer->removeBullet(bullet);
    }
    enemy_to_delete->removeAllObjects();
    bullet_to_delete->removeAllObjects();

    //multi bullet enemy1
    CCARRAY_FOREACH(this->multi_bullet_layer->bullet_array, bt) {
        CCSprite *bullet = (CCSprite *)bt;
        CCARRAY_FOREACH(this->enemy_layer->enemy1_array, et) {
            Enemy *enemy = (Enemy *)et;

            if(enemy->getBoundingBox().intersectsRect(bullet->boundingBox())) {
                int life = enemy->getLife();

                if(life > 1) {//alive
                    enemy->loseLife();
                    bullet_to_delete->addObject(bullet);
                } else if(life == 1) {//will die
                    enemy->loseLife();
                    bullet_to_delete->addObject(bullet);
					enemy_to_delete->addObject(enemy);
					score += SCORE_ENEMY1;
					control_layer->updateScore(score);
                } else {//dying
                }
            }
        }
    }
    CCARRAY_FOREACH(enemy_to_delete, et) {
        Enemy *enemy = (Enemy *)et;
        this->enemy_layer->enemy1BlowUp(enemy);
    }
    CCARRAY_FOREACH(bullet_to_delete, bt) {
        CCSprite *bullet = (CCSprite *)bt;
        this->multi_bullet_layer->removeBullet(bullet);
    }
    enemy_to_delete->removeAllObjects();
    bullet_to_delete->removeAllObjects();

    //multi bullet enemy2
    CCARRAY_FOREACH(this->multi_bullet_layer->bullet_array, bt) {
        CCSprite *bullet = (CCSprite *)bt;
        CCARRAY_FOREACH(this->enemy_layer->enemy2_array, et) {
            Enemy *enemy = (Enemy *)et;

            if(enemy->getBoundingBox().intersectsRect(bullet->boundingBox())) {
                int life = enemy->getLife();

                if(life > 1) { //alive
                    enemy->loseLife();
                    bullet_to_delete->addObject(bullet);
                } else if(life == 1) {//will die
                    enemy->loseLife();
                    bullet_to_delete->addObject(bullet);
					enemy_to_delete->addObject(enemy);
					score += SCORE_ENEMY2;
					control_layer->updateScore(score);
                } else {//dying. show dying animation.
                }
            }
        }
    }
    CCARRAY_FOREACH(enemy_to_delete, et) {
        Enemy *enemy = (Enemy *)et;
        this->enemy_layer->enemy2BlowUp(enemy);
    }
    CCARRAY_FOREACH(bullet_to_delete, bt) {
        CCSprite *bullet = (CCSprite *)bt;
        this->multi_bullet_layer->removeBullet(bullet);
    }
    enemy_to_delete->removeAllObjects();
    bullet_to_delete->removeAllObjects();

    //multi bullet enemy3
    CCARRAY_FOREACH(this->multi_bullet_layer->bullet_array, bt) {
        CCSprite *bullet = (CCSprite *)bt;
        CCARRAY_FOREACH(this->enemy_layer->enemy3_array, et) {
            Enemy *enemy = (Enemy *)et;

            if(enemy->getBoundingBox().intersectsRect(bullet->boundingBox())) {
                int life = enemy->getLife();

                if(life > 1) { //alive
                    enemy->loseLife();
                    bullet_to_delete->addObject(bullet);
                } else if(life == 1) {//will die
                    enemy->loseLife();
                    bullet_to_delete->addObject(bullet);
					enemy_to_delete->addObject(enemy);
					score += SCORE_ENEMY3;
					control_layer->updateScore(score);
                } else {//dying
                }
            }
        }
    }
    CCARRAY_FOREACH(enemy_to_delete, et) {
        Enemy *enemy = (Enemy *)et;
        this->enemy_layer->enemy3BlowUp(enemy);
    }
    CCARRAY_FOREACH(bullet_to_delete, bt) {
        CCSprite *bullet = (CCSprite *)bt;
        this->multi_bullet_layer->removeBullet(bullet);
    }
    enemy_to_delete->removeAllObjects();
    bullet_to_delete->removeAllObjects();

    enemy_to_delete->release();
    bullet_to_delete->release();

    //collecting gift bomb
    CCArray *gift_to_delete = CCArray::create();
    gift_to_delete->retain();

    CCSprite *plane = (CCSprite *)PlaneLayer::sharedPlane->getChildByTag(PLANE_TAG);
    CCObject *gt;
    CCARRAY_FOREACH(this->gift_layer->gift_bomb_array, gt) {
        CCSprite *gift = (CCSprite *)gt;

        if(gift->boundingBox().intersectsRect(plane->boundingBox())) {
            ++bomb_count;
            updateBigBoomItem(bomb_count);
            gift_to_delete->addObject(gift);
        }
    }
    CCARRAY_FOREACH(gift_to_delete, gt) {
        CCSprite *sprite = (CCSprite *)gt;
        this->gift_layer->removeGiftBomb(sprite);
    }
    gift_to_delete->removeAllObjects();

    //collect gift multi bullet
    CCARRAY_FOREACH(this->gift_layer->gift_bullet_array, gt) {
        CCSprite *gift = (CCSprite *)gt;

        if(gift->boundingBox().intersectsRect(plane->boundingBox())) {
            gift_to_delete->addObject(gift);
            this->bullet_layer->stopShoot();
            this->multi_bullet_layer->startShoot();
            this->bullet_layer->startShoot(6.0f);
        }
    }
    CCARRAY_FOREACH(gift_to_delete, gt) {
        CCSprite *sprite = (CCSprite *)gt;
        this->gift_layer->removeGiftBullet(sprite);
    }
    gift_to_delete->removeAllObjects();

    gift_to_delete->release();
}

void GameLayer::updateBigBoomItem(int bigBoomCount) {
    CCSprite *normalBomb = CCSprite::createWithSpriteFrameName("bomb.png");
    CCSprite *pressedBomb = CCSprite::createWithSpriteFrameName("bomb.png");

    if(bigBoomCount < 0)return;

    if(bigBoomCount == 0) {
        if(this->getChildByTag(TAG_BIGBOOM_LABEL))this->removeChildByTag(TAG_BIGBOOM_LABEL);

        if(this->getChildByTag(TAG_BIGBOOM_MENUITEM))this->removeChildByTag(TAG_BIGBOOM_MENUITEM);

        return;
    }

    if(bigBoomCount == 1) {
        if(!this->getChildByTag(TAG_BIGBOOM_MENUITEM)) {
            CCMenuItemImage *bigBoomItem = CCMenuItemImage::create();
            bigBoomItem->initWithNormalSprite(normalBomb, pressedBomb, NULL, this,
                                              menu_selector(GameLayer::menuBoomCallBack));
            bigBoomItem->setPosition(ccp(normalBomb->getContentSize().width / 2 + 10,
                                         normalBomb->getContentSize().height / 2 + 10));
            menu_bomb = CCMenu::create(bigBoomItem, NULL);
            menu_bomb->setPosition(CCPointZero);
            this->addChild(menu_bomb, 0, TAG_BIGBOOM_MENUITEM);
        }

        if(this->getChildByTag(TAG_BIGBOOM_LABEL))
            this->removeChildByTag(TAG_BIGBOOM_LABEL, true);

        return;
    }

    if(!this->getChildByTag(TAG_BIGBOOM_MENUITEM)) {
        CCMenuItemImage *bigBoomItem = CCMenuItemImage::create();
        bigBoomItem->initWithNormalSprite(normalBomb, pressedBomb, NULL, this,
                                          menu_selector(GameLayer::menuBoomCallBack));
        bigBoomItem->setPosition(ccp(normalBomb->getContentSize().width / 2 + 10,
                                     normalBomb->getContentSize().height / 2 + 10));
        menu_bomb = CCMenu::create(bigBoomItem, NULL);
        menu_bomb->setPosition(CCPointZero);
        this->addChild(menu_bomb, 0, TAG_BIGBOOM_MENUITEM);
    }

    if(this->getChildByTag(TAG_BIGBOOM_LABEL))
        this->removeChildByTag(TAG_BIGBOOM_LABEL, true);

    if(bigBoomCount >= 0 && bigBoomCount <= MAX_BIGBOOM_COUNT) {
        CCString *strScore = CCString::createWithFormat("X%d", bigBoomCount);
        bomb_count_item = CCLabelBMFont::create(strScore->m_sString.c_str(), "font/font.fnt");
        bomb_count_item->setColor(ccc3(143, 146, 147));
        bomb_count_item->setAnchorPoint(ccp(0, 0.5f));
        bomb_count_item->setPosition(ccp(normalBomb->getContentSize().width + 15,
                                         normalBomb->getContentSize().height / 2 + 5));
        this->addChild(bomb_count_item, 0, TAG_BIGBOOM_LABEL);
    }
}

void GameLayer::menuBoomCallBack(CCObject *sender) {
    if(bomb_count > 0 && !CCDirector::sharedDirector()->isPaused()) {
        --bomb_count;
        this->enemy_layer->removeAllEnemy();
        updateBigBoomItem(bomb_count);
    }
}

void GameLayer::registerWithTouchDispatcher() {
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0, true);
}

bool GameLayer::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent) {
    return true;
}

void GameLayer::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent) {
    if(this->planeLayer->is_alive) {
        CCPoint beginPoint = pTouch->getLocation();
        CCRect planeRect = this->planeLayer->getChildByTag(PLANE_TAG)->boundingBox();
        planeRect.origin.x -= 15;
        planeRect.origin.y -= 15;
        planeRect.size.width += 30;
        planeRect.size.height += 30;

        if(planeRect.containsPoint(beginPoint)) {
            CCPoint endPoint = pTouch->getPreviousLocation();
            CCPoint offset = ccpSub(beginPoint, endPoint);
            CCPoint toPoint = ccpAdd(offset, this->planeLayer->getChildByTag(PLANE_TAG)->getPosition());
            this->planeLayer->moveTo(toPoint);
        }
    }
}
void GameLayer::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent) {}
void GameLayer::ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent) {}

void GameLayer::backgroundMove(float dt) {
    background1->setPositionY(background1->getPositionY() - 2);
    background2->setPositionY(background1->getPositionY() + background1->getContentSize().height - 2);

    if(background2->getPositionY() == 0) {
        background1->setPositionY(0);
    }
}

