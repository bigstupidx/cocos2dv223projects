#include "HelloWorldScene.h"

USING_NS_CC;

CCScene *HelloWorld::scene()
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

    CCSprite *bg = CCSprite::create("bg_0.png");
    bg->setPosition(ccp(160, 270));
    this->addChild(bg);

    cache = CCSpriteFrameCache::sharedSpriteFrameCache();
    cache->addSpriteFramesWithFile("ballz.plist");

    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

    CCArray *array = CCArray::createWithCapacity(81);

    for(int i = 0; i < 9; i++)
    {
        for(int j = 0; j < 9; j++)
        {
            game_object[i][j] = CCMenuItemImage::create(NULL, NULL,
                                this, menu_selector(HelloWorld::menuItemCallback));
            game_object[i][j]->setNormalSpriteFrame(cache->spriteFrameByName("ball.png"));

            if(j % 2 == 0)
            {
                game_object[i][j]->setPosition(10 + i * 31 + 15, j * 30 + 100);
            }
            else
            {
                game_object[i][j]->setPosition(10 + i * 31 + 30, j * 30 + 100);
            }

            array->addObject(game_object[i][j]);
        }
    }

    game_cat = CCSprite::createWithSpriteFrame(cache->spriteFrameByName("cat_00.png"));
    CCArray *frames = CCArray::create();

    for(int i = 0; i < 12; i++)
    {
        char str[100];
        sprintf(str, "cat_%02d.png", i);
        CCLog("%s", str);
        CCSpriteFrame *frame = cache->spriteFrameByName(str);
        frames->addObject(frame);
    }

    CCAnimation *animation = CCAnimation::createWithSpriteFrames(frames, 0.1f);
    game_cat->runAction(CCRepeatForever::create(CCSequence::create(CCAnimate::create(animation), CCDelayTime::create(0.3f), NULL)));

    CCMenu *pMenu =  CCMenu::createWithArray(array);
    pMenu->setPosition(CCPointZero);
    this->addChild(pMenu, 1);

    this->addChild(game_cat, 1);

    {
        //game over layer
        gameover_layer = CCLayerColor::create(ccc4(0, 0, 0, 130));

        CCSprite *gameover_bg = CCSprite::createWithSpriteFrame(cache->spriteFrameByName("bg_dialog.png"));
        gameover_bg->setPosition(ccp(160, 280));
        gameover_layer->addChild(gameover_bg);

        CCAnimation *animation_win = CCAnimation::create();
        animation_win->addSpriteFrame(cache->spriteFrameByName("cat_succ_0.png"));
        animation_win->addSpriteFrame(cache->spriteFrameByName("cat_succ_1.png"));
        animation_win->setDelayPerUnit(0.1f);

        gameover_win = CCSprite::createWithSpriteFrame(cache->spriteFrameByName("cat_succ_0.png"));
        gameover_win->runAction(CCRepeatForever::create(CCAnimate::create(animation_win)));
        gameover_win->setPosition(ccp(160, 310));

        CCAnimation *animation_lose = CCAnimation::create();
        animation_lose->addSpriteFrame(cache->spriteFrameByName("cat_lose_0.png"));
        animation_lose->addSpriteFrame(cache->spriteFrameByName("cat_lose_1.png"));
        animation_lose->setDelayPerUnit(0.1f);

        gameover_lose = CCSprite::createWithSpriteFrame(cache->spriteFrameByName("cat_lose_0.png"));
        gameover_lose->runAction(CCRepeatForever::create(CCAnimate::create(animation_lose)));
        gameover_lose->setPosition(ccp(160, 310));

        gameover_layer->addChild(gameover_win);
        gameover_layer->addChild(gameover_lose);
        //gameover_layer->addChild(gameover_menu);
        this->addChild(gameover_layer, 2);
    }

    initGame();

    return true;
}


void HelloWorld::initGame()
{
    memset(game_object_x, false, sizeof(game_object_x));

    for(int i = 0; i < 9; i++)
    {
        for(int j = 0; j < 9; j++)
        {
            setImageAtPos(i, j);
        }
    }

    pos_cat_x = 4;
    pos_cat_y = 4;
    setImageCatAtPos(pos_cat_x, pos_cat_y, 0);
}

static int dir[2][12] =
{
    {
        -1, 0, 1, 0, -1, -1, 0, -1, -1, 1, 0, 1,
    },//
    {
        -1, 0, 1, 0, 0, -1, 1, -1, 0, 1, 1, 1,
    },//
};

int HelloWorld::getPathOut()
{
    return 0;
}

void HelloWorld::randomStep()
{
    int index = 0, top = 0;

    if(pos_cat_y % 2 == 0)
    {
        index = 0;
    }
    else
    {
        index = 1;
    }

    for(int i = 0; i < 6; i++)
    {
        int ii = pos_cat_x + dir[index][2 * i];
        int jj = pos_cat_y + dir[index][2 * i + 1];

        if(posIllegal(ii, jj) && !game_object_x[ii][jj])
            queue[top++] = ii * 9 + jj;
    }

    if(top == 0)
    {
        gameOver();
        return;
    }

    int indexx = randomInt(0, top);
    pos_cat_x = queue[indexx] / 9;
    pos_cat_y = queue[indexx] % 9;
    setImageCatAtPos(pos_cat_x, pos_cat_y, 0);

    if(pos_cat_x == 0 || pos_cat_x == 8 || pos_cat_y == 0 || pos_cat_y == 8)
    {
        gameOver();
    }
}

void HelloWorld::gameOver()
{
    bool win = false;

    if(pos_cat_x == 0 || pos_cat_x == 8 || pos_cat_y == 0 || pos_cat_y == 8)win = false;
    else win = true;
}

int HelloWorld::randomInt(int minx, int maxn)
{
    if(minx != maxn)
    {
        return rand() % (maxn - minx) + minx;
    }

    return minx;
}


bool HelloWorld::posIllegal(int i, int j)
{
    if(i < 0 || j < 0 || i >= 9 || j >= 9)return false;

    return true;
}

void HelloWorld::setImageAtPos(int i, int j)
{
    CCLog("set image at pos: %d %d", i, j);

    if(game_object_x[i][j])
    {
        game_object[i][j]->setNormalSpriteFrame(cache->spriteFrameByName("ballx.png"));
    }
    else
    {
        game_object[i][j]->setNormalSpriteFrame(cache->spriteFrameByName("ball.png"));
    }
}

void HelloWorld::setImageCatAtPos(int i, int j, int state)
{
    if(j % 2 == 0)
    {
        game_cat->setPosition(ccp(10 + i * 31 + 20, j * 30 + 115));
    }
    else
    {
        game_cat->setPosition(ccp(10 + i * 31 + 35, j * 30 + 115));
    }
}

void HelloWorld::menuItemCallback(CCObject *pSender)
{
    CCLog("menu item call back");

    for(int i = 0; i < 9; i++)
    {
        for(int j = 0; j < 9; j++)
        {
            if(pSender == game_object[i][j])
            {
                CCLog("%d %d %d %d %d", i, j, game_object_x[i][j], pos_cat_x, pos_cat_y);

                if(!game_object_x[i][j] && (pos_cat_x != i || pos_cat_y != j))
                {
                    CCLog("%d %d", i, j);
                    game_object_x[i][j] = true;
                    setImageAtPos(i, j);
                    randomStep();
                }

                return;
            }
        }
    }
}
