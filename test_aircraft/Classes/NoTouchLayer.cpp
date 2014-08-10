#include "NoTouchLayer.h"

NoTouchLayer::NoTouchLayer() {}
NoTouchLayer::~NoTouchLayer() {}

bool NoTouchLayer::init() {
    bool result = false;

    do {
        CC_BREAK_IF(!CCLayer::init());
        setTouchEnabled(true);
        result = true;
    } while (0);

    return result;
}

void NoTouchLayer::registerWithTouchDispatcher() {
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, -127, true);
    CCLayer::registerWithTouchDispatcher();
}

bool NoTouchLayer::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent) {
    return true;
}

void NoTouchLayer::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent) {}
void NoTouchLayer::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent) {}