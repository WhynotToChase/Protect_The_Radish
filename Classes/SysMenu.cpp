
#include "SysMenu.h"
#include <iostream>
#include <fstream>

using namespace cocos2d;

int SysMenu::saveNum = 0;

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
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("settings.plist");
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("tower.plist");
    ////////////////// 
    Size WinSize = Director::getInstance()->getWinSize();

    
    this->removeChildByName("temb");
    this->removeChildByName("Product");

    //添加背景 

    auto sp = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("sys_menu_17.png"));

    sp->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
    this->addChild(sp, -10, 1);

    //添加logo
    auto logo = Sprite::create("logo.png");
    logo->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
    logo->setPosition(1100, 800);
    this->addChild(logo, -9, 1);

    //添加tomb
    auto tomb = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("sys_menu_1.png"));

    tomb->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
    tomb->setPosition(200, 0);
    this->addChild(tomb, 5, 1);


    //添加 四个按钮
    //start
    Sprite* StartButtonNormal = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("sys_menu_2_1.png"));
    Sprite* StartTitleNormal = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("sys_menu_7_1.png"));
    StartTitleNormal->setPosition(120, 62);
    StartButtonNormal->addChild(StartTitleNormal);

    Sprite* StartButtonSelected = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("sys_menu_2_2.png"));
    Sprite* StartTitleSelected = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("sys_menu_7_2.png"));
    StartTitleSelected->setPosition(112, 56);
    StartButtonSelected->setPosition(4, -4);
    StartButtonSelected->addChild(StartTitleSelected);

    Sprite* OptionButtonNormal = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("sys_menu_3_1.png"));
    Sprite* OptionTitleNormal = (Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("sys_menu_12_1.png")));
    OptionTitleNormal->setPosition(120, 52);
    OptionButtonNormal->addChild(OptionTitleNormal);

    Sprite* OptionButtonSelected = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("sys_menu_3_2.png"));
    Sprite* OptionTitleSelected = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("sys_menu_12_2.png"));
    OptionTitleSelected->setPosition(117, 49);
    OptionButtonSelected->setPosition(-4, 0);
    OptionButtonSelected->addChild(OptionTitleSelected);

    Sprite* ProductButtonNormal = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("sys_menu_4_1.png"));
    Sprite* ProductTitleNormal = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("sys_menu_13_1.png"));
    ProductTitleNormal->setPosition(110, 48);
    ProductButtonNormal->addChild(ProductTitleNormal);

    Sprite* ProductButtonSelected = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("sys_menu_4_2.png"));
    Sprite* ProductTitleSelected = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("sys_menu_13_2.png"));
    ProductTitleSelected->setPosition(104, 41);
    ProductButtonSelected->addChild(ProductTitleSelected);

    Sprite* ExitButtonNormal = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("sys_menu_4_1.png"));
    Sprite* ExitTitleNormal = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("sys_menu_16_1.png"));
    ExitTitleNormal->setPosition(110, 45);
    ExitButtonNormal->addChild(ExitTitleNormal);

    Sprite* ExitButtonSelected = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("sys_menu_4_2.png"));
    Sprite* ExitTitleSelected = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("sys_menu_16_2.png"));
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



    music=SoundManager::getInstance();

    return true;
}

void SysMenu::OnStart(Ref* pSender)
{
    music->onButtonEffect();
    using namespace std;
    this->removeChildByName("temb");
    this->removeChildByName("Product");
    MenuItemSprite* gameOne, * gameTwo, * gameThree;


    auto BG1Normal = Sprite::createWithSpriteFrameName("sys_menu_6_1.png");
    auto BG1Selected = Sprite::createWithSpriteFrameName("sys_menu_6_2.png");
    auto size = BG1Normal->getContentSize();





    fstream saveData("../saveData/gameOne.txt", std::ios::in | std::ios::out);
    if (saveData.is_open()) {
        auto Title1Normal = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("sys_menu_9_1.png"));
        auto Title1Selected = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("sys_menu_9_2.png"));
        Title1Normal->setPosition(size.width / 2-10, size.height / 2-4);
        Title1Selected->setPosition(size.width / 2 - 12, size.height / 2 - 10);
        Title1Normal->setScale(1.3f);
        Title1Selected->setScale(1.3f);
        BG1Normal->addChild(Title1Normal, 3);
        BG1Selected->addChild(Title1Selected, 3);
    }
    else {
        auto NewGame1Normal = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("sys_menu_8_1.png"));
        auto NewGame1Selected = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("sys_menu_8_2.png"));
        NewGame1Normal->setPosition(size.width / 2, size.height / 2);
        NewGame1Selected->setPosition(size.width / 2 - 5, size.height / 2 - 10);
        BG1Normal->addChild(NewGame1Normal, 3);
        BG1Selected->addChild(NewGame1Selected, 3);
    }
    gameOne = MenuItemSprite::create(BG1Normal, BG1Selected, [this](Ref* pSender) {
        this->StartGame(pSender, 1); });
    saveData.close();


    saveData.open("../saveData/gameTwo.txt", std::ios::in | std::ios::out);
    auto BG2Normal = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("sys_menu_6_1.png"));
    auto BG2Selected = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("sys_menu_6_2.png"));
    if (saveData.is_open()) {
        auto Title2Normal = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("sys_menu_10_1.png"));
        auto Title2Selected = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("sys_menu_10_2.png"));
        Title2Normal->setPosition(size.width / 2-4, size.height / 2-4);
        Title2Selected->setPosition(size.width / 2 - 8, size.height / 2 - 11);
        Title2Normal->setScale(1.3f);
        Title2Selected->setScale(1.3f);
        BG2Normal->addChild(Title2Normal, 3);
        BG2Selected->addChild(Title2Selected, 3);
    }
    else {
        auto NewGame2Normal = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("sys_menu_8_1.png"));
        auto NewGame2Selected = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("sys_menu_8_2.png"));
        NewGame2Normal->setPosition(size.width / 2, size.height / 2);
        NewGame2Selected->setPosition(size.width / 2 - 5, size.height / 2 - 10);
        BG2Normal->addChild(NewGame2Normal, 3);
        BG2Selected->addChild(NewGame2Selected, 3);
    }
    gameTwo = MenuItemSprite::create(BG2Normal, BG2Selected, [this](Ref* pSender) {
        this->StartGame(pSender, 2); });
    saveData.close();


    auto BG3Normal = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("sys_menu_6_1.png"));
    auto BG3Selected = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("sys_menu_6_2.png"));
    saveData.open("../saveData/gameThree.txt", std::ios::in | std::ios::out);
    if (saveData.is_open()) {
        auto Title3Normal = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("sys_menu_11_1.png"));
        auto Title3Selected = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("sys_menu_11_2.png"));
        Title3Normal->setPosition(size.width / 2-6, size.height / 2-2);
        Title3Selected->setPosition(size.width / 2 - 15, size.height / 2 - 7); 
        Title3Normal->setScale(1.3f);
        Title3Selected->setScale(1.3f);
        BG3Normal->addChild(Title3Normal, 3);
        BG3Selected->addChild(Title3Selected, 3);
    }
    else {
        auto NewGame3Normal = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("sys_menu_8_1.png"));
        auto NewGame3Selected = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("sys_menu_8_2.png"));
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
    saveData.close();


    Sprite* temb = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("sys_menu_5.png"));
    temb->addChild(miniMenu);
    temb->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
    temb->setPosition(320, 70);
    temb->setName("temb");
    this->addChild(temb,0);

    auto moveBy = MoveBy::create(0.5, Vec2(temb->getContentSize().width - 70, 0));
    temb->runAction(moveBy);
    monitor(temb);
}

void SysMenu::OnOption(Ref* pSender)
{
    music->onButtonEffect();

    this->removeChildByName("temb");
    this->removeChildByName("Product");

    auto settingMenu = SettingMenu::create(false);
    Director::getInstance()->pushScene(settingMenu);
}

void SysMenu::OnProduct(Ref* pSender)
{
    music->onButtonEffect();

    this->removeChildByName("temb");
    this->removeChildByName("Product");
    auto size = Director::getInstance()->getWinSize();

    auto frame = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("sys_menu_14.png"));
    auto frameSize = frame->getContentSize(); 
    frame->setName("Product");
    frame->setAnchorPoint(Vec2::ANCHOR_MIDDLE);


    auto title = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("creator.png"));
    auto name = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("name.png"));
    title->setAnchorPoint(Vec2::ANCHOR_MIDDLE_BOTTOM);
    title->setPosition(frameSize.width / 2, frameSize.height / 2);
    name->setAnchorPoint(Vec2::ANCHOR_MIDDLE_TOP);
    name->setPosition(frameSize.width / 2, frameSize.height / 2);
    frame->addChild(title);
    frame->addChild(name);

    auto back0 = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("back_0.png"));
    auto back1 = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("back_1.png"));
    MenuItem* _back = MenuItemSprite::create(back1, back0, [this](Ref* pSender) {
        this->FrameReturn(pSender, "Product"); });
    Menu* back = Menu::create(_back, NULL);
    back->setAnchorPoint(Vec2::ANCHOR_TOP_LEFT);
    back->setPosition(30, frameSize.height-30);
    frame->addChild(back);

    
    this->addChild(frame);
    frame->setPosition(size.width / 2, size.height + frameSize.width / 2);
    auto moveBy = MoveBy::create(0.7f, Vec2(0,-size.height / 2 - frameSize.width / 2));
    frame->runAction(moveBy);
    monitor(frame);
}

void SysMenu::OnExit(Ref* pSender)
{
    music->onButtonEffect();

    this->removeChildByName("temb");
    this->removeChildByName("Product");
    ExitProcess(1);
}

void SysMenu::StartGame( Ref* pSender,int num)
{
    music->onButtonEffect();
    changeSaveNum(num);
    auto p = SelectMenu::scene();
    Director::getInstance()->pushScene(p);
}

bool SysMenu::onTouchBegan(Touch* touch, Event* event, Sprite* menu)
{
    Vec2 touchPoint = this->convertToNodeSpace(touch->getLocation()); 
    Rect menuBoundingBox = menu->getBoundingBox(); if (!menuBoundingBox.containsPoint(touchPoint)) {
        music->onButtonEffect();
        MoveBy* moveby;
        if (menu->getName() == "temb")
            moveby = MoveBy::create(0.5, Vec2(-menu->getContentSize().width + 70, 0));
        else if (menu->getName() == "Product")
            moveby = MoveBy::create(0.8f, Vec2(0, 1000));
        auto dead = CallFunc::create([=]() {
            // 回调函数中执行销毁精灵的操作
            menu->removeFromParentAndCleanup(true);
            });
        auto sequence = Sequence::create(moveby, dead, NULL);
        removeTouchListener();
        menu->runAction(sequence);
    }
    return true;
}

void SysMenu::monitor(Sprite* menu)
{
    auto touchListener = EventListenerTouchOneByOne::create(); 
    touchListener->onTouchBegan = CC_CALLBACK_2(SysMenu::onTouchBegan, this, menu); 
    _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, menu);
}

void SysMenu::removeTouchListener() {
    _eventDispatcher->removeEventListenersForTarget(this);
};

void SysMenu::FrameReturn(Ref* pSender, std::string frame)
{
    music->onButtonEffect();
    auto p = this->getChildByName(frame);
    removeTouchListener();
    auto moveUp = MoveBy::create(0.8f, Vec2(0, 1000));
    auto dead = CallFunc::create([=]() {
        // 回调函数中执行销毁精灵的操作
        p->removeFromParentAndCleanup(true);
        });
    auto sequence = Sequence::create(moveUp, dead,NULL); 
    p->runAction(sequence);
}
