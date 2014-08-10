#ifndef __UFO_LAYER_H__
#define __UFO_LAYER_H__

#include "cocos2d.h"

USING_NS_CC;

const int GIFT_BOMB = 0;
const int GIFT_BULLET = 1;

class GiftLayer: public CCLayer {
    public:
        GiftLayer();
        virtual ~GiftLayer();
        virtual bool init();

        CREATE_FUNC(GiftLayer);

        void addGiftBullet(float dt);
        void addGiftBomb(float dt);
        void addGift(int type);

        void giftBulletMoveFinished(CCNode *pSender);
        void giftBombMoveFinished(CCNode *pSender);

        void removeGiftBullet(CCSprite *gift);
        void removeGiftBomb(CCSprite *gift);

    public:
        CCArray *gift_bullet_array;
        CCArray *gift_bomb_array;
};

#endif