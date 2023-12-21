#include "SysMenu.h"
#include <iostream>
#include <fstream>

using namespace cocos2d;
bool isMenu = false;
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

    
    this->removeChildByName("temb");

    //添加背景 

    auto sp = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(SysmenuBackground));

    sp->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
    this->addChild(sp, -10, 1);

    //添加logo
    auto logo = Sprite::create("logo.png");
    logo->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
    logo->setPosition(1100, 800);
    this->addChild(logo, -9, 1);

    //添加tomb
    auto tomb = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(SysmenuSelection));

    tomb->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
    tomb->setPosition(200, 0);
    this->addChild(tomb, 5, 1);


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
    using namespace std;
    MenuItemSprite* gameOne, * gameTwo, * gameThree;


    auto BG1Normal = Sprite::createWithSpriteFrameName(SysmenuButton4On);
    auto BG1Selected = Sprite::createWithSpriteFrameName(SysmenuButton4Down);
    auto size = BG1Normal->getContentSize();





    fstream saveData1("/saveData/gameOne.txt", std::ios::in | std::ios::out);
    if (saveData1.is_open()) {
        auto Title1Normal = Sprite::createWithSpriteFrameName(SaveFile1ScriptOn);
        auto Title1Selected = Sprite::createWithSpriteFrameName(SaveFile1ScriptDown);
        Title1Normal->setPosition(size.width / 2, size.height / 2);
        Title1Selected->setPosition(size.width / 2 - 5, size.height / 2 - 10);
        BG1Normal->addChild(Title1Normal, 3);
        BG1Selected->addChild(Title1Selected, 3);
    }
    else {
        auto NewGame1Normal = Sprite::createWithSpriteFrameName(NewGameScriptOn);
        auto NewGame1Selected = Sprite::createWithSpriteFrameName(NewGameScriptDown);
        NewGame1Normal->setPosition(size.width / 2, size.height / 2);
        NewGame1Selected->setPosition(size.width / 2 - 5, size.height / 2 - 10);
        BG1Normal->addChild(NewGame1Normal, 3);
        BG1Selected->addChild(NewGame1Selected, 3);
    }
    gameOne = MenuItemSprite::create(BG1Normal, BG1Selected, [this](Ref* pSender) {
        this->StartGame(pSender, 1); });



    fstream saveData2("/saveData/gameTwo.txt", std::ios::in | std::ios::out);
    auto BG2Normal = Sprite::createWithSpriteFrameName(SysmenuButton4On);
    auto BG2Selected = Sprite::createWithSpriteFrameName(SysmenuButton4Down);
    if (saveData2.is_open()) {
        auto Title2Normal = Sprite::createWithSpriteFrameName(SaveFile2ScriptOn);
        auto Title2Selected = Sprite::createWithSpriteFrameName(SaveFile2ScriptDown);
        Title2Normal->setPosition(size.width / 2, size.height / 2);
        Title2Selected->setPosition(size.width / 2 - 5, size.height / 2 - 10);
        BG2Normal->addChild(Title2Normal, 3);
        BG2Selected->addChild(Title2Selected, 3);
    }
    else {
        auto NewGame2Normal = Sprite::createWithSpriteFrameName(NewGameScriptOn);
        auto NewGame2Selected = Sprite::createWithSpriteFrameName(NewGameScriptDown);
        NewGame2Normal->setPosition(size.width / 2, size.height / 2);
        NewGame2Selected->setPosition(size.width / 2 - 5, size.height / 2 - 10);
        BG2Normal->addChild(NewGame2Normal, 3);
        BG2Selected->addChild(NewGame2Selected, 3);
    }
    gameTwo = MenuItemSprite::create(BG2Normal, BG2Selected, [this](Ref* pSender) {
        this->StartGame(pSender, 2); });



    auto BG3Normal = Sprite::createWithSpriteFrameName(SysmenuButton4On);
    auto BG3Selected = Sprite::createWithSpriteFrameName(SysmenuButton4Down);
    fstream saveData3("/saveData/gameThree.txt", std::ios::in | std::ios::out);
    if (saveData3.is_open()) {
        auto Title3Normal = Sprite::createWithSpriteFrameName(SaveFile3ScriptOn);
        auto Title3Selected = Sprite::createWithSpriteFrameName(SaveFile3ScriptDown);
        Title3Normal->setPosition(size.width / 2, size.height / 2);
        Title3Selected->setPosition(size.width / 2 - 5, size.height / 2 - 10);
        BG3Normal->addChild(Title3Normal, 3);
        BG3Selected->addChild(Title3Selected, 3);
    }
    else {
        auto NewGame3Normal = Sprite::createWithSpriteFrameName(NewGameScriptOn);
        auto NewGame3Selected = Sprite::createWithSpriteFrameName(NewGameScriptDown);
        NewGame3Normal->setPosition(size.width / 2, size.height / 2);
        NewGame3Selected->setPosition(size.width / 2 - 5, size.height / 2 - 10);
        BG3Normal->addChild(NewGame3Normal, 3);
        BG3Selected->addChild(NewGame3Selected, 3);
    }
    gameThree = MenuItemSprite::create(BG3Normal, BG3Selected, [this](Ref* pSender) {
        this->StartGame(pSender, 3); });
    Menu* miniMenu = Menu::create(gameOne, gameTwo, gameThree, NULL);
    miniMenu->alignItemsVerticallyWithPadding(-20);
    miniMenu->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
    miniMenu->setPosition(170, 200);



    Sprite* temb = Sprite::createWithSpriteFrameName(SysmenuSecondSelection);
    temb->addChild(miniMenu);
    temb->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
    temb->setPosition(320, 70);
    temb->setName("temb");
    this->addChild(temb,0);
    size = temb->getContentSize();
    auto moveBy = MoveBy::create(0.5, Vec2(size.width - 70, 0));
    temb->runAction(moveBy);
    monitor(temb);
}

void SysMenu::OnOption(Ref* pSender)
{
  /*  onButtonEffect();
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
    ExitProcess(1);
}

void SysMenu::StartGame( Ref* pSender,int num)
{
    /*Scene* scene = Scene::create();
    scene->addChild(GameLayer::create());

    Director::getInstance()->replaceScene(TransitionFade::create(1.2, scene));
    */
}

MONITOR_CPP(SysMenu);



