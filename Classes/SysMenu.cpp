#include "SysMenu.h"
#include "Resource.h"

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
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("sys_menu.plist");

    ////////////////// 
    Size WinSize = Director::getInstance()->getWinSize();

    //添加背景 0 ；1；

    auto sp = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(SysmenuBackground));

    sp->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
    this->addChild(sp, -10, 1);


    //添加tomb 2 ；1；
    auto tomb = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(SysmenuSelection));

    tomb->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
    tomb->setPosition(200, 0);
    this->addChild(tomb, -5, 1);


    //添加 七个按钮
    //start
    Sprite* StartButtonNormal = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(SysmenuButton1On));
    Sprite* StartTitleNormal = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(StartScriptOn));
    StartTitleNormal->setPosition(120, 62);
    StartButtonNormal->addChild(StartTitleNormal);

    Sprite* StartButtonSelected = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(SysmenuButton1Down));
    Sprite* StartTitleSelected = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(StartScriptDown));
    StartTitleSelected->setPosition(112, 56);
    StartButtonSelected->setPosition(4, -4);
    StartButtonSelected->addChild(StartTitleSelected);

    Sprite* OptionButtonNormal = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(SysmenuButton2On));
    Sprite* OptionTitleNormal = (Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(OptionScriptOn)));
    OptionTitleNormal->setPosition(120, 52);
    OptionButtonNormal->addChild(OptionTitleNormal);

    Sprite* OptionButtonSelected = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(SysmenuButton2Down));
    Sprite* OptionTitleSelected = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(OptionScriptDown));
    OptionTitleSelected->setPosition(117, 49);
    OptionButtonSelected->setPosition(-4, 0);
    OptionButtonSelected->addChild(OptionTitleSelected);

    Sprite* ProductButtonNormal = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(SysmenuButton3On));
    Sprite* ProductTitleNormal = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(ProductScriptOn));
    ProductTitleNormal->setPosition(110, 48);
    ProductButtonNormal->addChild(ProductTitleNormal);

    Sprite* ProductButtonSelected = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(SysmenuButton3Down));
    Sprite* ProductTitleSelected = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(ProductScriptDown));
    ProductTitleSelected->setPosition(104, 41);
    ProductButtonSelected->addChild(ProductTitleSelected);

    Sprite* ExitButtonNormal = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(SysmenuButton3On));
    Sprite* ExitTitleNormal = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(ExitScriptOn));
    ExitTitleNormal->setPosition(110, 45);
    ExitButtonNormal->addChild(ExitTitleNormal);

    Sprite* ExitButtonSelected = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(SysmenuButton3Down));
    Sprite* ExitTitleSelected = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(ExitScriptDown));
    ExitTitleSelected->setPosition(104, 41);
    ExitButtonSelected->addChild(ExitTitleSelected);





    /*   auto flare = Sprite::create(s_flare_jpg);
       this->addChild(flare, 15, 10);
       flare->setVisible(false);
       */
    MenuItemSprite* Start = MenuItemSprite::create(StartButtonNormal, StartButtonSelected,
        CC_CALLBACK_1(SysMenu::OnStart, this));

    MenuItemSprite* Option = MenuItemSprite::create(OptionButtonNormal, OptionButtonSelected,
        CC_CALLBACK_1(SysMenu::OnOption, this));


    MenuItemSprite* Product = MenuItemSprite::create(ProductButtonNormal, ProductButtonSelected,
        CC_CALLBACK_1(SysMenu::OnProduct, this));

    MenuItemSprite* Exit = MenuItemSprite::create(ExitButtonNormal, ExitButtonSelected,
        CC_CALLBACK_1(SysMenu::OnExit, this));


    // 最后一个参数要是NULL
    Menu* menu1 = Menu::create(Start, NULL);
    menu1->alignItemsVertically();
    this->addChild(menu1, 10, 2);
    menu1->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
    menu1->setPosition(450, 360);

    Menu* menu2 = Menu::create(Option, NULL);
    menu2->alignItemsVertically();
    this->addChild(menu2, 10, 2);
    menu2->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
    menu2->setPosition(455, 255);

    Menu* menu3 = Menu::create(Product, NULL);
    menu3->alignItemsVertically();
    this->addChild(menu3, 10, 2);
    menu3->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
    menu3->setPosition(470, 170);

    Menu* menu4 = Menu::create(Exit, NULL);
    menu4->alignItemsVertically();
    this->addChild(menu4, 10, 2);
    menu4->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
    menu4->setPosition(480, 100);

    auto label = Label::createWithSystemFont("Power by Cocos2dx4.0 hkf lzh", "Arial", 40);
    label->setColor(Color3B(31, 45, 150));
    this->addChild(label, 100);
    label->setAnchorPoint(Vec2::ANCHOR_MIDDLE_BOTTOM);
    label->setPosition(WinSize.width / 2 + 70, 0);




    /* if (GlobalResManager::getInstance()->getSoundFlag())
     {

         int mainMusicAudio = AudioEngine::play2d(s_mainMainMusic);
         AudioEngine::setVolume(mainMusicAudio, 0.7);

     }*/

    return true;
}

void SysMenu::OnStart(Ref* pSender)
{
   /* AudioEngine::stopAll();
    Scene* scene = Scene::create();
    scene->addChild(GameLayer::create());

    Director::getInstance()->replaceScene(TransitionFade::create(1.2, scene));
    */
}

void SysMenu::OnOption(Ref* pSender)
{
 /*   onButtonEffect();

    //转到"SettingsLayer"
    Scene* scene = SettingsLayer::scene();
    Director::getInstance()->replaceScene(TransitionFade::create(1.2, scene));
    */
}

void SysMenu::OnProduct(Ref* pSender)
{
   /* onButtonEffect();


    Scene* scene = AboutLayer::scene();
    Director::getInstance()->replaceScene(TransitionFade::create(1.2, scene));
    */
}

void SysMenu::OnExit(Ref* pSender)
{
    ExitProcess;
}