#include "SysMenu.h"
#include "Resource.h"
#include <iostream>
#include <fstream>

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

    //��ӱ��� 

    auto sp = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(SysmenuBackground));

    sp->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
    this->addChild(sp, -10, 1);

    //���logo
    auto logo = Sprite::create("logo.png");
    logo->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
    logo->setPosition(1100, 800);
    this->addChild(logo, -9, 1);

    //���tomb
    auto tomb = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(SysmenuSelection));

    tomb->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
    tomb->setPosition(200, 0);
    this->addChild(tomb, -5, 1);


    //��� �߸���ť
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


    // ���һ������Ҫ��NULL
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
    Vec2::condition
    auto BGNormal = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(SysmenuButton4On));
    auto BGSelected = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(SysmenuButton4Down));
    Sprite* TitleNormal, * TitleSelected, * NewGameNormal, * NewGameSelected;
    fstream saveData1("/saveData/gameOne.txt", std::ios::in | std::ios::out  );
    if (saveData1.is_open()) {
        TitleNormal = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(SaveFile1ScriptOn));
        TitleSelected = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(SaveFile1ScriptDown));
        TitleNormal->setPosition((0, 0));
        TitleSelected->setPosition((0, 0));
    }
    else {
        NewGameNormal = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(NewGameScriptOn));
        NewGameSelected = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(NewGameScriptDown));
        NewGameNormal->setPosition((0, 0));
        NewGameSelected->setPosition()
    }
    fstream saveData2("/saveData/gameTwo.txt", std::ios::in | std::ios::out);
    if (saveData2.is_open()) {
        auto Title2Normal = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(SaveFile2ScriptOn));
        auto Title2selected = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(SaveFile2ScriptDown));
    }
    fstream saveData3("/saveData/gameThree.txt", std::ios::in | std::ios::out);
    if (saveData1.is_open()) {
        auto Title3Normal = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(SaveFile3ScriptOn));
        auto Title3selected = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(SaveFile3ScriptDown));
    }
}

void SysMenu::OnOption(Ref* pSender)
{
 /*   onButtonEffect();

    //ת��"SettingsLayer"
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

void SysMenu::StartGame(Ref* pSender,int num)
{
    /*Scene* scene = Scene::create();
    scene->addChild(GameLayer::create());

    Director::getInstance()->replaceScene(TransitionFade::create(1.2, scene));
    */
}