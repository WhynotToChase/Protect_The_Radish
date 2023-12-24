#include "ThisLevel.h"

using namespace cocos2d;

bool ThisLevel::init(const int&level)
{
    money = 0;

    this_music = SoundManager::getInstance();

    this_mouse = MousePosition::create();
    addChild(this_mouse);

    if (!Scene::init())
    {
        return false;
    }


    Size WinSize = Director::getInstance()->getWinSize();

    //先建立一个大背景第level关的背景
    auto sp = Sprite::create(ThisLevel::SelectLevel(level));
    Size spritesize = sp->getContentSize();
    sp->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
    sp->setScale(WinSize.width / spritesize.width, WinSize.height / spritesize.height); // 设置初始缩放
    this->addChild(sp, -10, 1);

    // 初始化按钮精灵
    auto buttonNormal = Sprite::create("../Resources/Grid.png");
    auto buttonPressed = Sprite::create("../Resources/left0.png");
    auto size = buttonNormal->getContentSize();
    buttonNormal->setScale(160 / size.width, 135 / size.height);
    size = buttonPressed->getContentSize();
    buttonPressed->setScale(160 / size.width, 135 / size.height);

    // 创建按钮菜单项

    buttonItem = MenuItemSprite::create(buttonNormal, buttonPressed,
        [this](Ref* pSender) {
            this_music->onButtonEffect();
            ThisLevel::createTower(buttonItem->getPosition());
        });

    // 创建按钮
    auto menu = Menu::create(buttonItem, nullptr);
    menu->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
    menu->setPosition(Vec2(500,500));

    addChild(menu);

    // 注册鼠标事件监听器
    auto mouseListener = cocos2d::EventListenerMouse::create();
    mouseListener->onMouseMove = CC_CALLBACK_1(ThisLevel::onMouseMove, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(mouseListener, Director::getInstance()->getRunningScene());

    this->schedule(CC_SCHEDULE_SELECTOR(ThisLevel::update), 0.1f);

    return true;
}

std::string ThisLevel::SelectLevel(const int&level) {
    switch (level) {
        case 1:return "../Resources/level1.png";
        case 2:return "../Resources/level2.png";
        case 3:return "../Resources/level3.png";
        case 4:return "../Resources/level4.png";
        case 5:return "../Resources/level5.png";
        case 6:return "../Resources/level6.png";
        case 7:return "../Resources/level7.png";
        case 8:return "../Resources/level8.png";
        case 9:return "../Resources/level9.png";
        case 10:return "../Resources/level10.png";
        default:
            break;
    }
    return "";
}


//更新每时刻的变化
void ThisLevel::update(float delta) {

}

void ThisLevel::onMouseMove(cocos2d::Event* event)
{
    //判断选择框是否存在
   // 。。。。。。

    auto range=p->getBoundingBox();
    auto mouseEvent = static_cast<cocos2d::EventMouse*>(event);

    // 获取鼠标当前位置
    Vec2 position = mouseEvent->getLocation();
     //是否在原来框的范围内，移动
    //.......当前位置是否可用，不可用就禁用
    
}

void ThisLevel::createTower(const Vec2& centerPosition)
{
    // 在当前按钮中心位置创建四个按钮

    float buttonWidth = 160.0f;
    float buttonHeight = 135.0f;
    Sprite* leftSprite;
    Sprite* rightSprite;
    Sprite* topSprite;
    Sprite* bottomSprite;
    if (money >= 100) {//瓶子
        leftSprite = Sprite::create("../Resources/CanClick1_1.PNG");
    }
    else {
        leftSprite = Sprite::create("../Resources/CanClick1_0.PNG");
    }
    if (money >= 160) {//星星
        rightSprite = Sprite::create("../Resources/CanClick3_1.PNG");
    }
    else {
        rightSprite = Sprite::create("../Resources/CanClick3_0.PNG");
    }
    if (money >= 160) {//风扇
        topSprite = Sprite::create("../Resources/CanClick4_1.PNG");
    }
    else {
        topSprite = Sprite::create("../Resources/CanClick4_0.PNG");
    }
    if (money >= 160) {//激光
        auto bottomSprite = Sprite::create("../Resources/CanClick5_1.PNG");
    }
    else {
        auto bottomSprite = Sprite::create("../Resources/CanClick5_0.PNG");
    }

    // 左边按钮
    auto leftButton = MenuItemSprite::create(leftSprite, leftSprite,
        [this](Ref* pSender) {
            this_music->onButtonEffect();
            
        });
    leftButton->setPosition(centerPosition.x - buttonWidth / 2, centerPosition.y);

    // 右边按钮
    auto rightButton = MenuItemSprite::create(rightSprite, leftSprite,
        [this](Ref* pSender) {
            this_music->onButtonEffect();
            
        });
    rightButton->setPosition(centerPosition.x + buttonWidth / 2, centerPosition.y);

    // 上边按钮
    auto topButton = MenuItemSprite::create(topSprite, topSprite,
       [this](Ref* pSender) {
            this_music->onButtonEffect();
            
        });
    topButton->setPosition(centerPosition.x, centerPosition.y + buttonHeight / 2);

    // 下边按钮
    auto bottomButton = MenuItemSprite::create(bottomSprite, bottomSprite,
        [this](Ref* pSender) {
            this_music->onButtonEffect();

        });
    bottomButton->setPosition(centerPosition.x, centerPosition.y - buttonHeight / 2);

    // ... 其他创建按钮的代码 ...

    // 将新按钮添加到场景或层
    this->addChild(leftButton);
    this->addChild(rightButton);
    this->addChild(topButton);
    this->addChild(bottomButton);
}
/*
void ThisLevel::onEnter() {
    Scene::onEnter();
}

void ThisLevel::onExit() {
    Scene::onExit();
}

bool ThisLevel::onTouchBegan(Touch* touch, Event* event) {
    // 在触摸开始时调用
    Vec2 touchPoint = touch->getLocation();

    if (pointInsideButton(touchPoint)) {
        setButtonHover();
        return true;
    }

    return false;
}

void ThisLevel::onTouchMoved(Touch* touch,Event* event) {
    // 在触摸移动时调用
    Vec2 touchPoint = touch->getLocation();

    if (pointInsideButton(touchPoint)) {
        setButtonHover();
    }
    else {
        setButtonNormal();
    }
}

void ThisLevel::onTouchEnded(Touch* touch, Event* event) {
    // 在触摸结束时调用
    Vec2 touchPoint = touch->getLocation();

    if (pointInsideButton(touchPoint)) {
        setButtonClicked();
    }
    else {
        setButtonNormal();
    }
}

void ThisLevel::setButtonNormal() {
    buttonItem->unselected(); // 恢复为正常状态
}

void ThisLevel::setButtonHover() {
    buttonItem->selected(); // 切换到悬停状态
}

void ThisLevel::setButtonClicked() {
    // 处理按钮点击事件
    // 可以在这里执行按钮点击后的逻辑
    setButtonNormal();
}

bool ThisLevel::pointInsideButton(const Vec2& point) {
    // 判断触摸点是否在按钮内
    Rect buttonRect = buttonItem->getBoundingBox();
    return buttonRect.containsPoint(point);
}*/
