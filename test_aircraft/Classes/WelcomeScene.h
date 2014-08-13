#ifndef __WELCOME_SCENE_H__
#define __WELCOME_SCENE_H__

#include "cocos2d.h"
USING_NS_CC;

class WelcomeScene: public CCScene {
    public:
        WelcomeScene();
        ~WelcomeScene();

        virtual bool init();
        CREATE_FUNC(WelcomeScene);

        void preloadAudio();
};
#endif // !__WELCOME_SCENE_H__
