#include "SysMenu.h"
#include "resource.h"

using namespace cocos2d;

Scene* SysMenu::scene()
{
    // 'scene' is an autorelease object
    Scene* scene = Scene::create();

    // 'layer' is an autorelease object
    SysMenu* layer = SysMenu::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

bool SysMenu::init()
{

    if (!Layer::init())
    {
        return false;
    }
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile(s_textureTransparentPack_plist);
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile(s_textureTextureOpaquePack_plist);


    //////////////////

    winSize = Director::getInstance()->getWinSize();
    //添加背景 0 ；1；

    Sprite* sp = Sprite::create(s_loading_png);

    sp->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
    sp->setScale(MW_SCALE);
    this->addChild(sp, 0, 1);


    //添加logo 10 ；1；
    auto logo = Sprite::create(s_logo_png);

    logo->setAnchorPoint(Vec2::ANCHOR_MIDDLE_TOP);
    logo->setPosition(Point(winSize.width / 2, winSize.height - 75));//我手工对齐了      
    logo->setScale(MW_SCALE);
    this->addChild(logo, 10, 1);

    //添加logoBack
    auto logoBack = Sprite::create(slogoBack_png);
    logoBack->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
    logoBack->setPosition(Point(60, 410));//我手工对齐了
    logoBack->setScale(MW_SCALE);
    this->addChild(logoBack, 9);

    //不写配置了，手动
    int singalHeight = 36;
    int singalWidth = 123;
    //添加 三个按钮
    Sprite* newGameNormal = Sprite::create("menu.png", Rect(0, 0, singalWidth, singalHeight));
    Sprite* newGameSelected = Sprite::create("menu.png", Rect(0, singalHeight, singalWidth, singalHeight));
    Sprite* newGameDisabled = Sprite::create("menu.png", Rect(0, singalHeight * 2, singalWidth, singalHeight));

    Sprite* gameSettingsNormal = Sprite::create("menu.png", Rect(singalWidth, 0, singalWidth, singalHeight));
    Sprite* gameSettingsSelected = Sprite::create("menu.png", Rect(singalWidth, singalHeight, singalWidth, singalHeight));
    Sprite* gameSettingsDisabled = Sprite::create("menu.png", Rect(singalWidth, singalHeight * 2, singalWidth, singalHeight));

    Sprite* aboutNormal = Sprite::create("menu.png", Rect(singalWidth * 2, 0, singalWidth, singalHeight));
    Sprite* aboutSelected = Sprite::create("menu.png", Rect(singalWidth * 2, singalHeight, singalWidth, singalHeight));
    Sprite* aboutDesabled = Sprite::create("menu.png", Rect(singalWidth * 2, singalHeight * 2, singalWidth, singalHeight));

    auto flare = Sprite::create(s_flare_jpg);
    this->addChild(flare, 15, 10);
    flare->setVisible(false);

    MenuItemSprite* newGame = MenuItemSprite::create(newGameNormal, newGameSelected, newGameDisabled,
        CC_CALLBACK_1(SysMenu::flareEffect, this));

    MenuItemSprite* gameSetting = MenuItemSprite::create(gameSettingsNormal, gameSettingsSelected, gameSettingsDisabled,
        CC_CALLBACK_1(SysMenu::onSettings, this));
    //“设置”按钮tag为20
    gameSetting->setTag(20);

    MenuItemSprite* about = MenuItemSprite::create(aboutNormal, aboutSelected, aboutDesabled,
        CC_CALLBACK_1(SysMenu::onAbout, this));//StartMenu::menuCallback
    //“关于”按钮tag为21
    about->setTag(21);

    newGame->setScale(MW_SCALE);
    gameSetting->setScale(MW_SCALE);
    about->setScale(MW_SCALE);


    // 最后一个参数要是NULL
    Menu* menu = Menu::create(newGame, gameSetting, about, NULL);
    menu->alignItemsVerticallyWithPadding(15);
    this->addChild(menu, 1, 2);
    menu->setPosition(Point(winSize.width / 2, winSize.height / 2 - 140));


    auto label = Label::createWithSystemFont("Power by Cocos2dx4.0 Ithe", "Arial", 21);
    label->setColor(Color3B(31, 45, 150));
    this->addChild(label, 1);
    label->setPosition(winSize.width / 2, 80);

    //添加update回调函数
    this->schedule(CC_SCHEDULE_SELECTOR(SysMenu::update), 0.1);

    // 添加ships
   // Texture2D *textCache = Director::getInstance()->getTextureCache()->addImage(s_ship03);
    _ship = Sprite::createWithSpriteFrameName("ship03.png");
    this->addChild(_ship, 0, 4);
    //设置飞船位置 移动
    Point position = Point(CCRANDOM_0_1() * winSize.width, 0);
    _ship->setPosition(position);
    _ship->runAction(MoveBy::create(2, Point(CCRANDOM_0_1() * winSize.width, position.y + winSize.height + 100)));


    if (GlobalResManager::getInstance()->getSoundFlag())
    {

        int mainMusicAudio = AudioEngine::play2d(s_mainMainMusic);
        AudioEngine::setVolume(mainMusicAudio, 0.7);

    }

    return true;
}
