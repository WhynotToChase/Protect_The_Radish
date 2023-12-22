#ifndef __SETTINGMENU_CPP__
#define __SETTINGMENU_CPP__

#include "SettingMenu.h"

using namespace cocos2d;

bool SettingMenu::init()
{

    if (!Scene::init())
    {
        return false;
    }
    music = SoundManager::getInstance();

#ifdef MOUSE
    position = MousePosition::create();
    this->addChild(position,100);
#endif//MOUSE

    auto size = Director::getInstance()->getWinSize();
    auto bg = Sprite::create("../Resources/SettingBG.png");
    bg->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
    bg->setScale(size.width / bg->getContentSize().width, size.height / bg->getContentSize().height);
    this->addChild(bg);

    auto home0 = Sprite::create("../Resources/Btn_Return.png");
    auto home1 = Sprite::create("../Resources/Btn_ReturnLight.png");
    auto _home = MenuItemSprite::create(home0, home1, [this](Ref* pSender) {
        this->returnHome(pSender); });
    auto home = Menu::create(_home, NULL); 
    home->setAnchorPoint(Vec2(0,0));
    home->setPosition(600, 750);
    home->setScale(1.5f);
    this->addChild(home,3);

    auto titleSound = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("setting02-2.PNG"));
    auto titleEffect = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("setting02-0.PNG"));
    titleSound->setPosition(610,600);
    titleSound->setScale(2.0f);
    titleEffect->setPosition(1310, 600);
    titleEffect->setScale(2.0f);
    this->addChild(titleEffect,3);
    this->addChild(titleSound,3);

    auto switch1_0 = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("setting02-15.PNG"));
    auto switch1_1 = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("setting02-21.PNG"));
    auto switch2_0 = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("setting02-6.PNG"));
    auto switch2_1 = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("setting02-11.PNG"));

    // 创建开关1
    auto _switch1 = MenuItemToggle::createWithCallback([this](Ref* pSender) {
            music->onButtonEffect();
            music->controlSounds();
        }, MenuItemSprite::create(switch1_0, switch1_0), MenuItemSprite::create(switch1_1, switch1_1),nullptr );
    _switch1->setScale(2.0f);

    // 创建开关2
    auto _switch2 = MenuItemToggle::createWithCallback( [this](Ref* pSender) {
            music->onButtonEffect();
            music->controlEffects();
        }, MenuItemSprite::create(switch2_0, switch2_0), MenuItemSprite::create(switch2_1, switch2_1),nullptr );
    _switch2->setScale(2.0f);

    // 设置初始状态
    _switch1->setSelectedIndex(0);
    _switch2->setSelectedIndex(0);
    Menu* switchs = Menu::create(_switch1, _switch2, NULL);
    switchs->setAnchorPoint(Vec2::ANCHOR_MIDDLE_TOP);
    switchs->setPosition(size.width / 2, 400);
    switchs->alignItemsHorizontallyWithPadding(400);
    this->addChild(switchs,3);
    return true;
}

void SettingMenu::returnHome(Ref* pSender)
{
    music->onButtonEffect();
    Director::getInstance()->popScene();
}

#endif // !__SETTINGMENU_CPP__
