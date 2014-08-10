#ifndef __GAME_LAYER_H__
#define __GAME_LAYER_H__

#include "cocos2d.h"
#include "BulletLayer.h"
#include "PlaneLayer.h"
#include "EnemyLayer.h"
#include "GiftLayer.h"
#include "MultiBulletLayer.h"
#include "ControlLayer.h"

USING_NS_CC;

#define TAG_BIGBOOM_MENUITEM 1000
#define TAG_BIGBOOM_LABEL 1001
#define MAX_BIGBOOM_COUNT 5

const int SCORE_ENEMY1 = 100;
const int SCORE_ENEMY2 = 400;
const int SCORE_ENEMY3 = 1000;

class GameLayer: public CCLayer {
    public:
        GameLayer();
        ~GameLayer();
        CREATE_FUNC(GameLayer);

        virtual bool init();

        void registerWithTouchDispatcher();

        virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
        virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
        virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
        virtual void ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent);

        void backgroundMove(float dt);
        void updateBigBoomItem(int bigBoomCount);
        void menuBoomCallBack(CCObject *sender);

        void update(float delta);

        static Level getLevel();

    private:
        CCSprite *background1, *background2;
        PlaneLayer *planeLayer;
        BulletLayer *bullet_layer;
        MultiBulletLayer *multi_bullet_layer;
        EnemyLayer *enemy_layer;
        GiftLayer *gift_layer;
		ControlLayer *control_layer;

        CCMenu *menu_bomb;
        CCLabelBMFont *bomb_count_item;

        int bomb_count;
        int score;

        static Level level;
};


#endif