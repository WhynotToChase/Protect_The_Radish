#include "SelectMenu.h"
#include "Resource.h"
#include"SettingMenu.h"
#include"SoundManager.h"
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
    this_music = SoundManager::getInstance();

    if (!Layer::init())
    {
        return false;
    }

    ////////////////// 
    Size WinSize = Director::getInstance()->getWinSize();

    //添加背景 0 ；1；
    //先建立一个大背景
    auto sp = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("background.png"));

    sp->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
    this->addChild(sp, -10, 1);

    Level = 1;//记录关数

    int Last_Next = 0;//判断前或后

    // 创建精灵并设置初始缩放
    middleSprite = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(SelectLevel(1)));
    middleSprite->setPosition(Vec2(240, 160));
    middleSprite->setScale(0.1); // 设置初始缩放

    // 创建缩放动作
    auto scaleToAction = ScaleTo::create(0.5f, 0.5f); // 缩放到原始大小0.5倍，持续0.5秒

    // 运行动作
    middleSprite->runAction(scaleToAction);

    // 将精灵添加到场景
    this->addChild(middleSprite,-5,2);

    //添加tomb 2 ；1；
    /*auto tomb = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(SelectLevel(1)));

    tomb->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    tomb->setPosition(960, 540);
    this->addChild(tomb, -5, 1);*/


    //添加 2个按钮
    //start
    Sprite* Selectleft = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("../Resources/Pictures/NormalMordel/left"));
    Selectleft->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    Selectleft->setPosition(20,540);

    Sprite* Selectright = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("../Resources/Pictures/NormalMordel/right"));
    Selectright->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    Selectright->setPosition(1900, 540);



    MenuItemSprite* left = MenuItemSprite::create(Selectleft, Selectleft,
        [this](Ref* pSender) {
            this_music->onButtonEffect();
            IsChange = -1;
            SelectMenu::moveSprites;
        });

    MenuItemSprite* right = MenuItemSprite::create(Selectright, Selectright,
        [this](Ref* pSender) {
            this_music->onButtonEffect();
            IsChange = 1;
            SelectMenu::moveSprites;
        });

    Sprite* _set = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("../Resources/Pictures/NormalMordel/touming-hd.pvr_28.PNG"));
    _set->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    _set->setPosition(1900, 20);
    this->addChild(_set);

    MenuItemSprite* Menu_set = MenuItemSprite::create(_set, _set,
        [this](Ref* pSender) {
            this_music->onButtonEffect();
            SelectMenu::ThisSet();
        });

    //两个按钮left right
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


    return true;
}

std::string SelectMenu::SelectLevel(const int&level) {
    switch (level) {
        case 1:return ".. / Resources / Pictures / level/first.png";
        case 2:return ".. / Resources / Pictures / level/second.png";
        case 3:return ".. / Resources / Pictures / level/third.png";
        case 4:return ".. / Resources / Pictures / level/fourth.png";
        case 5:return ".. / Resources / Pictures / level/fifth.png";
        case 6:return ".. / Resources / Pictures / level/sixth.png";
        case 7:return ".. / Resources / Pictures / level/seventh.png";
        case 8:return ".. / Resources / Pictures / level/eighth.png";
        case 9:return ".. / Resources / Pictures / level/ninth.png";
        case 10:return ".. / Resources / Pictures / level/tenth.png";
    }
}

void SelectMenu::ThisSet() {
    auto p = SettingMenu::create();
    p->inside = true;
    Director::getInstance()->replaceScene(p);
}
void SelectMenu::moveSprites(Ref* pSender)
{
    if (IsChange == 0) {
        return;
    }
    else if (IsChange == -1) {
        // 移动中间精灵到左边屏幕外
        auto moveOutAction = MoveBy::create(1.0f, Vec2(-960, 0));
        middleSprite->runAction(moveOutAction);

        // 创建新的精灵并设置初始位置在右边屏幕外
        auto newSprite = Sprite::create(SelectLevel(Level + IsChange));
        newSprite->setPosition(Vec2(2880, 540));
        newSprite->setScale(0.5); // 设置初始缩放
        addChild(newSprite);

        // 移动新的精灵到中间
        auto moveInAction = MoveTo::create(1.0f, Vec2(960, 540));

        // 同时执行移动和创建精灵的动作
        auto spawnAction = Spawn::create(moveInAction, nullptr);
        newSprite->runAction(spawnAction);

        middleSprite = newSprite;
    }
    else if (IsChange == 1) {
        // 移动中间精灵到右边屏幕外
        auto moveOutAction = MoveBy::create(1.0f, Vec2(2880, 0));
        middleSprite->runAction(moveOutAction);

        // 创建新的精灵并设置初始位置在左边屏幕外
        auto newSprite = Sprite::create(SelectLevel(Level + IsChange));
        newSprite->setPosition(Vec2(-960, 540));
        newSprite->setScale(0.5); // 设置初始缩放
        addChild(newSprite);

        // 移动新的精灵到中间
        auto moveInAction = MoveTo::create(1.0f, Vec2(960, 540));

        // 同时执行移动和创建精灵的动作
        auto spawnAction = Spawn::create(moveInAction, nullptr);
        newSprite->runAction(spawnAction);

        middleSprite = newSprite;
    }
}


