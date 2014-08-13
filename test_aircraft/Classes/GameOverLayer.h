#ifndef __GAMEOVER_LAYER_H__
#define __GAMEOVER_LAYER_H__

#include "cocos2d.h"

USING_NS_CC;

class GameOverLayer: public CCLayer {
    public:
        GameOverLayer();
        ~GameOverLayer();

        virtual bool init();

        static GameOverLayer *create(int passScore);

        void menuBackCallBack(CCObject *sender);

        virtual void keyBackClicked();

        void beginChangeHighestScore(CCNode *node);

        void showAD();

    public:
        static int highest_record;

        int score;

        CCLabelBMFont *highest_score_item;
};
#endif // !__GAMEOVER_LAYER_H__
