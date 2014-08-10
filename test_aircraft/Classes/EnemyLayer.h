#ifndef __ENEMY_LAYER_H__
#define __ENEMY_LAYER_H__

#include "cocos2d.h"
#include "Enemy.h"

USING_NS_CC;

const int ENEMY1_MAXLIFE = 1;
const int ENEMY2_MAXLIFE = 2;
const int ENEMY3_MAXLIFE = 3;

enum Level {
    EASY, MIDDLE, HARD,
};

class EnemyLayer: public CCLayer {
    public:
        EnemyLayer();
        ~EnemyLayer();

        CREATE_FUNC(EnemyLayer);

        virtual bool init();

        void addEnemy1(float delta);
        void addEnemy2(float delta);
        void addEnemy3(float delta);

        void addEnemy(int type);

        void enemy1MoveFinished(CCNode *pTarget);
        void enemy2MoveFinished(CCNode *pTarget);
        void enemy3MoveFinished(CCNode *pTarget);

        void enemy1BlowUp(Enemy *enemy);
        void enemy2BlowUp(Enemy *enemy);
        void enemy3BlowUp(Enemy *enemy);

        void removeEnemy1(CCNode *pTarget, void *data);
        void removeEnemy2(CCNode *pTarget, void *data);
        void removeEnemy3(CCNode *pTarget, void *data);

        void removeAllEnemy1();
        void removeAllEnemy2();
        void removeAllEnemy3();

        void removeAllEnemy();

    public:
        CCArray *enemy1_array;
        CCArray *enemy2_array;
        CCArray *enemy3_array;

    private:
        CCSpriteFrame *enemy1SpriteFrame;
        CCSpriteFrame *enemy2SpriteFrame;
        CCSpriteFrame *enemy3SpriteFrame_1;
        CCSpriteFrame *enemy3SpriteFrame_2;
};

#endif