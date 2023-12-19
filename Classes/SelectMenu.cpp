#include "SelectMenu.h"
#include "Resource.h"
#include<string>

using namespace cocos2d;

Scene* SelectMenu::scene()
{
    // 'scene' is an autorelease object
    Scene* scene = Scene::create();

    // 'layer' is an autorelease object
    SelectMenu* layer = SelectMenu::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

bool SelectMenu::init()
{

    if (!Layer::init())
    {
        return false;
    }

    ////////////////// 
    Size WinSize = Director::getInstance()->getWinSize();

    //添加背景 0 ；1；

    auto sp = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("background.png"));

    sp->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
    this->addChild(sp, -10, 1);


    //添加tomb 2 ；1；
    auto tomb = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(SelectLevel(1)));

    tomb->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    tomb->setPosition(960, 540);
    this->addChild(tomb, -5, 1);


    //添加 2个按钮
    //start
    Sprite* Selectleft = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(SelectLevel(1)));
    tomb->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    Selectleft->setPosition(20,540);

    Sprite* Selectright = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(SelectLevel(1)));
    tomb->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    Selectright->setPosition(1900, 540);



    MenuItemSprite* left = MenuItemSprite::create(Selectleft, Selectleft,
        CC_CALLBACK_1(SelectMenu::OnStart, this));

    MenuItemSprite* right = MenuItemSprite::create(Selectright, Selectright,
        CC_CALLBACK_1(SelectMenu::OnOption, this));


    // 最后一个参数要是NULL
    Menu* menu1 = Menu::create(left, NULL);
    menu1->alignItemsVertically();
    this->addChild(menu1, 10, 2);
    menu1->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    menu1->setPosition(20, 540);

    Menu* menu2 = Menu::create(right, NULL);
    menu2->alignItemsVertically();
    this->addChild(menu2, 10, 2);
    menu2->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
    menu2->setPosition(1900, 540);


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

std::string SelectMenu::SelectLevel(const int&level) {
    switch (level) {
        case 1:return "first.png";
        case 2:return "second.png";
        case 3:return "third.png";
        case 4:return "fourth.png";
        case 5:return "fifth.png";
        case 6:return "sixth.png";
        case 7:return "seventh.png";
        case 8:return "eighth.png";
        case 9:return "ninth.png";
        case 10:return "tenth.png";
    }
}
void SelectMenu::OnStart(Ref* pSender)
{
    /* AudioEngine::stopAll();
     Scene* scene = Scene::create();
     scene->addChild(GameLayer::create());

     Director::getInstance()->replaceScene(TransitionFade::create(1.2, scene));
     */
}

void SelectMenu::OnOption(Ref* pSender)
{
    /*   onButtonEffect();

       //转到"SettingsLayer"
       Scene* scene = SettingsLayer::scene();
       Director::getInstance()->replaceScene(TransitionFade::create(1.2, scene));
       */
}
