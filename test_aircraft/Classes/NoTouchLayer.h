#ifndef __NO_TOUCH_LAYER_H__
#define __NO_TOUCH_LAYER_H__

#include "cocos2d.h"

USING_NS_CC;

class NoTouchLayer: public CCLayer {
    public:
        NoTouchLayer();
        ~NoTouchLayer();
        CREATE_FUNC(NoTouchLayer);
        virtual bool init();

        virtual void registerWithTouchDispatcher();
        virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
        virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
        virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
};

#endif