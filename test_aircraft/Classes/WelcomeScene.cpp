#include "WelcomeScene.h"
#include "WelcomeLayer.h"
#include "SimpleAudioEngine.h"

WelcomeScene::WelcomeScene() {}
WelcomeScene::~WelcomeScene() {}

bool WelcomeScene::init() {
    bool result = false;

    do {
        CC_BREAK_IF(!CCScene::init());
        WelcomeLayer *layer = WelcomeLayer::create();
        CC_BREAK_IF(!layer);
        this->addChild(layer);
        preloadAudio();
        result = true;
    } while (0);

    return result;
}

void WelcomeScene::preloadAudio() {
    CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadBackgroundMusic("sound/game_music.mp3");
    CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic("sound/game_music.mp3");
}

