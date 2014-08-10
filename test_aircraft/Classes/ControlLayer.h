#ifndef __CONTROL_LAYER_H__
#define __CONTROL_LAYER_H__

#include "cocos2d.h"
#include "NoTouchLayer.h"

const int MAX_SCORE = 2000000000;

USING_NS_CC;

class ControlLayer: public CCLayer {
    public:
        ControlLayer();
        ~ControlLayer();

        CREATE_FUNC(ControlLayer);

        virtual bool init();

        void menuPauseCallback(CCObject *sender);

        void updateScore(int score);

    public:
        CCLabelBMFont *score_item;
        CCMenuItemImage *button_pause;
        NoTouchLayer *no_touch_layer;
};

#endif
