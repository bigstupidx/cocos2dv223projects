#include "GameScene.h"

GameScene::GameScene() {
    game_layer = NULL;
}

GameScene::~GameScene() {

}

bool GameScene::init() {
    bool result = false;

    do {
        CC_BREAK_IF ( !CCScene::init() );
        CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile ( "shoot_background.plist" );
        CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile ( "shoot.plist" );

        game_layer = GameLayer::create();
        CC_BREAK_IF ( !game_layer );
        this->addChild ( game_layer );

        result = true;
    } while ( 0 );

    return result = true;
}