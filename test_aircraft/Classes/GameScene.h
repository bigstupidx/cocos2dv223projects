#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__


#include "cocos2d.h"
#include "GameLayer.h"
#include "PlaneLayer.h"
#include "BulletLayer.h"

USING_NS_CC;

class GameScene: public CCScene {
    public:
        GameScene();
        ~GameScene();

        virtual bool init();

        CREATE_FUNC ( GameScene );

    private:
        GameLayer *game_layer;
};

#endif