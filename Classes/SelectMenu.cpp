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

    if (!Layer::init())
    {
        return false;
    }
    if(Resource::gameData[1]==0)
    Resource::gameData[1] = 4;
    ////////////////// 
    Size WinSize = Director::getInstance()->getWinSize();
    
    //先建立一个大背景
    auto sp = Sprite::create("../Resources/background.png");
    Size spritesize = sp->getContentSize();
    sp->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
    sp->setScale(WinSize.width/spritesize.width,WinSize.height / spritesize.height); // 设置初始缩放
    this->addChild(sp, -10, 1);

    Level = 1;//记录关数

    // 创建精灵并设置初始缩放
    auto middleSprite = Sprite::create("../Resources/level_01.png");

    Sprite* carret = Sprite::create(Resource::carret[Resource::gameData[1]]);
    carret->setPosition(middleSprite->getContentSize().width,0);
    middleSprite->addChild(carret);
    MenuItemSprite* The_middleSprite = MenuItemSprite::create(middleSprite, middleSprite,
        [this](Ref* pSender) {
            this_music->onEffect();
            if (Resource::gameData[Level] > 0) {
                auto p = ThisLevel::create(Level);
                Director::getInstance()->pushScene(p);
            }
        });

    The_middleSprite_menu = Menu::create(The_middleSprite, NULL);
    The_middleSprite_menu->alignItemsVertically();
    this->addChild(The_middleSprite_menu, -5, 2);
    The_middleSprite_menu->setPosition(960, 540);
    The_middleSprite_menu->setScale(0.1f); // 设置初始缩放

    // 创建缩放动作
    auto scaleToAction = ScaleTo::create(0.5f, 1.0f); // 缩放到原始大小，持续0.5秒

    // 运行动作
    The_middleSprite_menu->runAction(scaleToAction);


    //添加 2个按钮选择上一个或下一关
    Sprite* Selectleft0 = Sprite::create("../Resources/left0.png");
    Selectleft0->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    Sprite* Selectleft1 = Sprite::create("../Resources/left1.png");
    Selectleft0->setAnchorPoint(Vec2::ANCHOR_MIDDLE);

    Sprite* Selectright0 = Sprite::create("../Resources/right0.png");
    Selectright0->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    Sprite* Selectright1 = Sprite::create("../Resources/right1.png");
    Selectright0->setAnchorPoint(Vec2::ANCHOR_MIDDLE);


    MenuItemSprite* left = MenuItemSprite::create(Selectleft0, Selectleft1,
        [this](Ref* pSender) {
            this_music->onEffect();
            if (Level != 1) {
                IsChange = -1;
                moveSprites(pSender);
            }
        });

    MenuItemSprite* right = MenuItemSprite::create(Selectright0, Selectright1,
        [this](Ref* pSender) {
            this_music->onEffect();
            if (Level != 10) {
                IsChange = 1;
                moveSprites(pSender);
            }
        });

    Sprite* _set0 = Sprite::create("../Resources/touming-hd.pvr_28.PNG");
    _set0->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    Sprite* _set1 = Sprite::create("../Resources/touming-hd.pvr_26.PNG");
    _set1->setAnchorPoint(Vec2::ANCHOR_MIDDLE);

    MenuItemSprite* Menu_set = MenuItemSprite::create(_set0, _set1,
        [this](Ref* pSender) {
            this_music->onEffect();
            SelectMenu::ThisSet();
        });

    Menu* menu_set = Menu::create(Menu_set, NULL);
    menu_set->alignItemsVertically();
    this->addChild(menu_set, 99, 2);
    menu_set->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
    menu_set->setPosition(1600, 1000);
    menu_set->setScale(2.0f);

    //两个按钮left right
    // 最后一个参数要是NULL
    Menu* menu1 = Menu::create(left, NULL);
    menu1->alignItemsVertically();
    this->addChild(menu1, 10, 2);
    menu1->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
    menu1->setPosition(70, 540);
    menu1->setScale(2.0f);

    Menu* menu2 = Menu::create(right, NULL);
    menu2->alignItemsVertically();
    this->addChild(menu2, 10, 2);
    menu2->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
    menu2->setPosition(1850, 540);
    menu2->setScale(2.0f);

    auto back0 = Sprite::create("../Resources/close_normal.png");
    auto back1 = Sprite::create("../Resources/close_pressed.png");
    auto _back = MenuItemSprite::create(back0, back1, [this](Ref* pSender) {
        this_music->onEffect();
        Resource::saveGame();
        Director::getInstance()->popScene(); });
    auto back = Menu::create(_back, NULL);
    back->setAnchorPoint(Vec2(0, 0));
    back->setPosition(320, 1000);
    back->setScale(1.4f);
    this->addChild(back, 3);

    return true;
}

//选择文件名称
std::string SelectMenu::SelectLevel(const int&level) {
    switch (level) {
        case 1:return "../Resources/level_01.png";
        case 2:return "../Resources/level_02.png";
        case 3:return "../Resources/level_03.png";
        case 4:return "../Resources/level_04.png";
        case 5:return "../Resources/level_05.png";
        case 6:return "../Resources/level_06.png";
        case 7:return "../Resources/level_07.png";
        case 8:return "../Resources/level_08.png";
        case 9:return "../Resources/level_09.png";
        case 10:return "../Resources/level_010.png";
        default:
            break;
    }
    return "";
}

void SelectMenu::ThisSet() {
    auto p = SettingMenu::create(true);
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
        auto moveOutAction = MoveBy::create(1.0f, Vec2(-960 * 2, 0));
        The_middleSprite_menu->runAction(moveOutAction);

        // 创建新的按钮并设置初始位置在右边屏幕外
        auto newSprite = Sprite::create(SelectLevel(Level + IsChange));
        Sprite* carret = Sprite::create(Resource::carret[Resource::gameData[Level + IsChange]]);
        carret->setPosition(newSprite->getContentSize().width, 0);
        newSprite->addChild(carret);

        MenuItemSprite* The_middleSprite = MenuItemSprite::create(newSprite, newSprite,
            [this](Ref* pSender) {
                this_music->onEffect();
                if (Resource::gameData[Level] > 0) {
                    auto p = ThisLevel::create(Level);
                    Director::getInstance()->pushScene(p);
                } });

        Menu* The_new_middleSprite_menu = Menu::create(The_middleSprite, NULL);
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
        Sprite* carret = Sprite::create(Resource::carret[Resource::gameData[Level + IsChange]]);
        carret->setPosition(newSprite->getContentSize().width, 0);
        newSprite->addChild(carret);

        MenuItemSprite* The_middleSprite = MenuItemSprite::create(newSprite, newSprite,
            [this](Ref* pSender) {
                this_music->onEffect();
                //第n关
                if (Resource::gameData[Level] > 0) {
                    auto p = ThisLevel::create(Level);
                    Director::getInstance()->pushScene(p);
                }
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
        
    }
    
}


