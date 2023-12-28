
#include "SettingMenu.h"

using namespace cocos2d;

bool SettingMenu::inside = false;

bool SettingMenu::init()
{

    if (!Scene::init())
    {
        return false;
    }
    music = SoundManager::getInstance();
    res = Resource::getInstance();

    auto size = Director::getInstance()->getWinSize();
    auto bg = Sprite::create("../Resources/SettingBG.png");
    bg->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
    bg->setScale(size.width / bg->getContentSize().width, size.height / bg->getContentSize().height);
    this->addChild(bg);

    auto back0 = Sprite::create("../Resources/close_normal.png");
    auto back1 = Sprite::create("../Resources/close_pressed.png");
    auto _back = MenuItemSprite::create(back0, back1, [this](Ref* pSender) {
        this->lastPage(); });
    auto back = Menu::create(_back, NULL);
    back->setAnchorPoint(Vec2(0, 0));
    back->setPosition(1320,750);
    back->setScale(1.5f);
    this->addChild(back, 3);

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
            music->onEffect();
            music->controlSounds();
        }, MenuItemSprite::create(switch1_0, switch1_0), MenuItemSprite::create(switch1_1, switch1_1),nullptr );
    _switch1->setScale(2.0f);

    // 创建开关2
    auto _switch2 = MenuItemToggle::createWithCallback( [this](Ref* pSender) {
            music->onEffect();
            music->controlEffects();
        }, MenuItemSprite::create(switch2_0, switch2_0), MenuItemSprite::create(switch2_1, switch2_1),nullptr );
    _switch2->setScale(2.0f);

    // 设置初始状态
    _switch1->setSelectedIndex(!music->getSounds());
    _switch2->setSelectedIndex(!music->getEffects());
    Menu* switchs = Menu::create(_switch1, _switch2, NULL);
    switchs->setAnchorPoint(Vec2::ANCHOR_MIDDLE_TOP);
    switchs->setPosition(size.width / 2, 400);
    switchs->alignItemsHorizontallyWithPadding(400);
    this->addChild(switchs,3);

    if (inside) {
        auto home0 = Sprite::create("../Resources/Btn_Return.png");
        auto home1 = Sprite::create("../Resources/Btn_ReturnLight.png");
        auto _home = MenuItemSprite::create(home0, home1, [this](Ref* pSender) {
            this->returnHome(); });
        auto home = Menu::create(_home, NULL);
        home->setAnchorPoint(Vec2(0, 0));
        home->setPosition(600, 750);
        home->setScale(1.5f);
        this->addChild(home, 3);

        auto save0 = Sprite::create("../Resources/setting0256.png");
        auto save1 = Sprite::create("../Resources/setting0257.png");
        auto _save = MenuItemSprite::create(save0, save1, [this](Ref* pSender) {
            music->onEffect();
            res->saveGame(); });
        auto save = Menu::create(_save, NULL);
        save->setAnchorPoint(Vec2(0, 0));
        save->setPosition(670, 170);
        save->setScale(1.5f);
        this->addChild(save, 3);

        auto reset0 = Sprite::create("../Resources/setting0255.png");
        auto reset1 = Sprite::create("../Resources/setting0254.png");
        auto _reset = MenuItemSprite::create(reset0, reset1, [this](Ref* pSender) {
            music->onEffect();
            res->removeData(); });
        auto reset = Menu::create(_reset, NULL);
        reset->setAnchorPoint(Vec2(0, 0));
        reset->setPosition(1250, 170);
        reset->setScale(1.5f);
        this->addChild(reset, 3);
    }
    return true;
}

void SettingMenu::lastPage()
{
    music->onEffect();
    Director::getInstance()->popScene();
}

void SettingMenu::returnHome() 
{
    music->onEffect();
    Director::getInstance()->popToRootScene();
    res->readData(0);
}


