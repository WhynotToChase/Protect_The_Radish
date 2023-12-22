#include "SelectMenu.h"

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

    this_mouse = MousePosition::create();
    addChild(this_mouse);

    if (!Layer::init())
    {
        return false;
    }


    ////////////////// 
    Size WinSize = Director::getInstance()->getWinSize();
    
    //添加背景 0 ；1；
    //先建立一个大背景
    auto sp = Sprite::create("../Resources/background.png");
    Size spritesize = sp->getContentSize();
    sp->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
    sp->setScale(WinSize.width/spritesize.width,WinSize.height / spritesize.height); // 设置初始缩放
    this->addChild(sp, -10, 1);

    Level = 1;//记录关数

    // 创建精灵并设置初始缩放
    auto middleSprite = Sprite::create("../Resources/first.png");
    
    MenuItemSprite* The_middleSprite = MenuItemSprite::create(middleSprite, middleSprite,
        [this](Ref* pSender) {
            this_music->onButtonEffect();
            //第一关
        });

    The_middleSprite_menu = Menu::create(The_middleSprite, NULL);
    The_middleSprite_menu->alignItemsVertically();
    this->addChild(The_middleSprite_menu, -5, 2);
    The_middleSprite_menu->setPosition(960, 540);
    The_middleSprite_menu->setScale(0.1); // 设置初始缩放

    // 创建缩放动作
    auto scaleToAction = ScaleTo::create(0.5f, 1.0f); // 缩放到原始大小，持续0.5秒

    // 运行动作
    The_middleSprite_menu->runAction(scaleToAction);


    //添加 2个按钮选择上一个或下一关
    Sprite* Selectleft = Sprite::create("../Resources/left.png");
    Selectleft->setAnchorPoint(Vec2::ANCHOR_MIDDLE);

    Sprite* Selectright = Sprite::create("../Resources/right.png");
    Selectright->setAnchorPoint(Vec2::ANCHOR_MIDDLE);



    MenuItemSprite* left = MenuItemSprite::create(Selectleft, Selectleft,
        [this](Ref* pSender) {
            this_music->onButtonEffect();
            if (Level != 1) {
                IsChange = -1;
                moveSprites(pSender);
            }
        });

    MenuItemSprite* right = MenuItemSprite::create(Selectright, Selectright,
        [this](Ref* pSender) {
            this_music->onButtonEffect();
            if (Level != 10) {
                IsChange = 1;
                moveSprites(pSender);
            }
        });

    Sprite* _set = Sprite::create("../Resources/touming-hd.pvr_28.PNG");
    _set->setAnchorPoint(Vec2::ANCHOR_MIDDLE);

    MenuItemSprite* Menu_set = MenuItemSprite::create(_set, _set,
        [this](Ref* pSender) {
            this_music->onButtonEffect();
            SelectMenu::ThisSet();
        });

    Menu* menu_set = Menu::create(Menu_set, NULL);
    menu_set->alignItemsVertically();
    this->addChild(menu_set, 99, 2);
    menu_set->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
    menu_set->setPosition(1600, 70);
    menu_set->setScale(1.5f);

    //两个按钮left right
    // 最后一个参数要是NULL
    Menu* menu1 = Menu::create(left, NULL);
    menu1->alignItemsVertically();
    this->addChild(menu1, 10, 2);
    menu1->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
    menu1->setPosition(70, 540);
    menu1->setScale(1.5f);

    Menu* menu2 = Menu::create(right, NULL);
    menu2->alignItemsVertically();
    this->addChild(menu2, 10, 2);
    menu2->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
    menu2->setPosition(1850, 540);
    menu2->setScale(1.5f);


    auto label = Label::createWithSystemFont("Power by Cocos2dx4.0 hkf lzh", "Arial", 40);
    label->setColor(Color3B(31, 45, 150));
    this->addChild(label, 100);
    label->setAnchorPoint(Vec2::ANCHOR_MIDDLE_BOTTOM);
    label->setPosition(WinSize.width / 2 + 70, 0);


    return true;
}

std::string SelectMenu::SelectLevel(const int&level) {
    switch (level) {
        case 1:return "../Resources/first.png";
        case 2:return "../Resources/second.png";
        case 3:return "../Resources/third.png";
        case 4:return "../Resources/fourth.png";
        case 5:return "../Resources/fifth.png";
        case 6:return "../Resources/sixth.png";
        case 7:return "../Resources/seventh.png";
        case 8:return "../Resources/eighth.png";
        case 9:return "../Resources/ninth.png";
        case 10:return "../Resources/tenth.png";
    }
}

void SelectMenu::ThisSet() {
    auto p = SettingMenu::create();
    p->inside = true;
    Director::getInstance()->pushScene(p);
}


void SelectMenu::moveSprites(Ref* pSender)
{
    auto dead = CallFunc::create([=]() {
        // 回调函数中执行销毁精灵的操作
        The_middleSprite_menu->removeFromParentAndCleanup(true);
        });
    if (IsChange == 0) {
        return;
    }
    else if (IsChange == 1) {
        // 移动中间精灵到左边屏幕外
        auto moveOutAction = MoveBy::create(1.0f, Vec2(-960*2, 0));
        The_middleSprite_menu->runAction(moveOutAction);

        // 创建新的按钮并设置初始位置在右边屏幕外
        auto newSprite = Sprite::create(SelectLevel(Level + IsChange));

        MenuItemSprite* The_middleSprite = MenuItemSprite::create(newSprite, newSprite,
            [this](Ref* pSender) {
                this_music->onButtonEffect();
                //第n关
            });

        Menu*The_new_middleSprite_menu = Menu::create(The_middleSprite, NULL);
        The_new_middleSprite_menu->alignItemsVertically();
        this->addChild(The_new_middleSprite_menu, -5, 2);
        The_new_middleSprite_menu->setPosition(Vec2(2880, 540));
        The_new_middleSprite_menu->setScale(1); // 设置初始缩放

        // 移动新的精灵到中间
        auto moveInAction = MoveTo::create(1.0f, Vec2(960, 540));

        // 同时执行移动和创建精灵的动作
        auto spawnAction = Spawn::create(moveInAction, nullptr);
        The_new_middleSprite_menu->runAction(spawnAction);

        Level += IsChange;

        auto sequence = Sequence::create(moveOutAction, moveInAction, dead, NULL);

        The_middleSprite_menu = The_new_middleSprite_menu;

    }
    else if (IsChange == -1) {
        // 移动中间精灵到左边屏幕外
        auto moveOutAction = MoveBy::create(1.0f, Vec2(2880, 0));
        The_middleSprite_menu->runAction(moveOutAction);

        // 创建新的按钮并设置初始位置在右边屏幕外
        auto newSprite = Sprite::create(SelectLevel(Level + IsChange));

        MenuItemSprite* The_middleSprite = MenuItemSprite::create(newSprite, newSprite,
            [this](Ref* pSender) {
                this_music->onButtonEffect();
                //第n关
            });

        Menu* The_new_middleSprite_menu = Menu::create(The_middleSprite, NULL);
        The_new_middleSprite_menu->alignItemsVertically();
        this->addChild(The_new_middleSprite_menu, -5, 2);
        The_new_middleSprite_menu->setPosition(Vec2(-960, 540));
        The_new_middleSprite_menu->setScale(1); // 设置初始缩放

        // 移动新的精灵到中间
        auto moveInAction = MoveTo::create(1.0f, Vec2(960, 540));

        // 同时执行移动和创建精灵的动作
        auto spawnAction = Spawn::create(moveInAction, nullptr);
        The_new_middleSprite_menu->runAction(spawnAction);

        Level += IsChange;

        auto sequence = Sequence::create(moveOutAction, moveInAction, dead, NULL);

        The_middleSprite_menu = The_new_middleSprite_menu;
        
        /*// 移动中间精灵到右边屏幕外
        auto moveOutAction = MoveBy::create(1.0f, Vec2(2880, 0));
        The_middleSprite_menu->runAction(moveOutAction);

        // 创建新的精灵并设置初始位置在左边屏幕外
        auto newSprite = Sprite::create(SelectLevel(Level + IsChange));
        newSprite->setPosition(Vec2(-960, 540));
        newSprite->setScale(1); // 设置初始缩放
        addChild(newSprite);

        // 移动新的精灵到中间
        auto moveInAction = MoveTo::create(1.0f, Vec2(960, 540));

        // 同时执行移动和创建精灵的动作
        auto spawnAction = Spawn::create(moveInAction, nullptr);
        newSprite->runAction(spawnAction);

        Level += IsChange;

        auto sequence = Sequence::create(moveOutAction, moveInAction, dead, NULL);

        middleSprite = newSprite;*/
    }
    
}


