#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"

class HelloWorld : public cocos2d::CCLayer
{
    public:
        virtual bool init();

        static cocos2d::CCScene *scene();

        void menuItemCallback(CCObject *sender);

        void initGame();

        int getPathOut();

        void randomStep();

        void setImageAtPos(int i, int j);

        void setImageCatAtPos(int i, int j, int state);

        bool posIllegal(int i, int j);

        void gameOver();

        int randomInt(int minx, int maxn);

        // implement the "static node()" method manually
        CREATE_FUNC(HelloWorld);

    private:
        cocos2d::CCSpriteFrameCache *cache;
        cocos2d::CCSprite *game_cat;
        cocos2d::CCMenuItemImage *game_object[9][9];
        bool game_object_x[9][9];
        int pos_cat_x, pos_cat_y;
        int queue[6];

        cocos2d::CCLayerColor *gameover_layer;
        cocos2d::CCSprite *gameover_win, *gameover_lose;
};

#endif // __HELLOWORLD_SCENE_H__
