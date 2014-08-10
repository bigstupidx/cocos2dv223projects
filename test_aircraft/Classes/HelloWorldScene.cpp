#include "HelloWorldScene.h"

USING_NS_CC;

CCScene* HelloWorld::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    HelloWorld *layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }
    
	this->initData();

	
    CCSize wSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

	CCSprite* bgSprite = CCSprite::createWithSpriteFrameName("");
	bgSprite->setPosition(ccp(wSize.width/2, wSize.height/2));
	this->addChild(bgSprite);

	CCSprite* logoSprite = CCSprite::create("BurstAircraftLogo-hd.png");
	logoSprite->setPosition(ccp(wSize.width/2, wSize.height/2 + 100));
	this->addChild(logoSprite);

	CCMenuItemFont *startItem = CCMenuItemFont::create("PLAY", this, menu_selector(HelloWorld::startGame));
	startItem->setPosition(ccp(wSize.width/2, wSize.height/2-200));
	//startItem->setFontNameObj("Georgia-Bold");
	
	CCMenu *menu = CCMenu::create(startItem, NULL);
	menu->setPosition(CCPointZero);
	this->addChild(menu);
    
    return true;
}


void HelloWorld::initData(){
	//CCSpriteFrameCache *frameCache = CCSpriteFrameCache::sharedSpriteFrameCache();
	//frameCache->addSpriteFramesWithFile("gameArts.plist");
}

void HelloWorld::startGame(CCObject *pSender){

}
