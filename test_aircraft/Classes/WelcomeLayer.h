#ifndef __WELCOME_LAYER_H__
#define __WELCOME_LAYER_H__


#include "cocos2d.h"

USING_NS_CC;

class WelcomeLayer: public CCLayer {
    public:
        WelcomeLayer();
        ~WelcomeLayer();

        CREATE_FUNC(WelcomeLayer);
        virtual bool init();

        bool isHaveSaveLife();
        void getHighestHistoryScore();
        void loadingDone(CCNode *node);

        virtual void keyBackClicked();
};

#endif // !__WELCOME_LAYER_H__
