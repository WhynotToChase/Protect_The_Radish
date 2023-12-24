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

    //�Ƚ���һ���󱳾���level�صı���
    auto sp = Sprite::create(ThisLevel::SelectLevel(level));
    Size spritesize = sp->getContentSize();
    sp->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
    sp->setScale(WinSize.width / spritesize.width, WinSize.height / spritesize.height); // ���ó�ʼ����
    this->addChild(sp, -10, 1);

    // ��ʼ����ť����
    auto buttonNormal = Sprite::create("../Resources/Grid.png");
    auto buttonPressed = Sprite::create("../Resources/left0.png");
    auto size = buttonNormal->getContentSize();
    buttonNormal->setScale(160 / size.width, 135 / size.height);
    size = buttonPressed->getContentSize();
    buttonPressed->setScale(160 / size.width, 135 / size.height);

    // ������ť�˵���

    buttonItem = MenuItemSprite::create(buttonNormal, buttonPressed,
        [this](Ref* pSender) {
            this_music->onButtonEffect();
            ThisLevel::createTower(buttonItem->getPosition());
        });

    // ������ť
    auto menu = Menu::create(buttonItem, nullptr);
    menu->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
    menu->setPosition(Vec2(500,500));

    addChild(menu);

    // ע������¼�������
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


//����ÿʱ�̵ı仯
void ThisLevel::update(float delta) {

}

void ThisLevel::onMouseMove(cocos2d::Event* event)
{
    //�ж�ѡ����Ƿ����
   // ������������

    auto range=p->getBoundingBox();
    auto mouseEvent = static_cast<cocos2d::EventMouse*>(event);

    // ��ȡ��굱ǰλ��
    Vec2 position = mouseEvent->getLocation();
     //�Ƿ���ԭ����ķ�Χ�ڣ��ƶ�
    //.......��ǰλ���Ƿ���ã������þͽ���
    
}

void ThisLevel::createTower(const Vec2& centerPosition)
{
    // �ڵ�ǰ��ť����λ�ô����ĸ���ť

    float buttonWidth = 160.0f;
    float buttonHeight = 135.0f;
    Sprite* leftSprite;
    Sprite* rightSprite;
    Sprite* topSprite;
    Sprite* bottomSprite;
    if (money >= 100) {//ƿ��
        leftSprite = Sprite::create("../Resources/CanClick1_1.PNG");
    }
    else {
        leftSprite = Sprite::create("../Resources/CanClick1_0.PNG");
    }
    if (money >= 160) {//����
        rightSprite = Sprite::create("../Resources/CanClick3_1.PNG");
    }
    else {
        rightSprite = Sprite::create("../Resources/CanClick3_0.PNG");
    }
    if (money >= 160) {//����
        topSprite = Sprite::create("../Resources/CanClick4_1.PNG");
    }
    else {
        topSprite = Sprite::create("../Resources/CanClick4_0.PNG");
    }
    if (money >= 160) {//����
        auto bottomSprite = Sprite::create("../Resources/CanClick5_1.PNG");
    }
    else {
        auto bottomSprite = Sprite::create("../Resources/CanClick5_0.PNG");
    }

    // ��߰�ť
    auto leftButton = MenuItemSprite::create(leftSprite, leftSprite,
        [this](Ref* pSender) {
            this_music->onButtonEffect();
            
        });
    leftButton->setPosition(centerPosition.x - buttonWidth / 2, centerPosition.y);

    // �ұ߰�ť
    auto rightButton = MenuItemSprite::create(rightSprite, leftSprite,
        [this](Ref* pSender) {
            this_music->onButtonEffect();
            
        });
    rightButton->setPosition(centerPosition.x + buttonWidth / 2, centerPosition.y);

    // �ϱ߰�ť
    auto topButton = MenuItemSprite::create(topSprite, topSprite,
       [this](Ref* pSender) {
            this_music->onButtonEffect();
            
        });
    topButton->setPosition(centerPosition.x, centerPosition.y + buttonHeight / 2);

    // �±߰�ť
    auto bottomButton = MenuItemSprite::create(bottomSprite, bottomSprite,
        [this](Ref* pSender) {
            this_music->onButtonEffect();

        });
    bottomButton->setPosition(centerPosition.x, centerPosition.y - buttonHeight / 2);

    // ... ����������ť�Ĵ��� ...

    // ���°�ť��ӵ��������
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
    // �ڴ�����ʼʱ����
    Vec2 touchPoint = touch->getLocation();

    if (pointInsideButton(touchPoint)) {
        setButtonHover();
        return true;
    }

    return false;
}

void ThisLevel::onTouchMoved(Touch* touch,Event* event) {
    // �ڴ����ƶ�ʱ����
    Vec2 touchPoint = touch->getLocation();

    if (pointInsideButton(touchPoint)) {
        setButtonHover();
    }
    else {
        setButtonNormal();
    }
}

void ThisLevel::onTouchEnded(Touch* touch, Event* event) {
    // �ڴ�������ʱ����
    Vec2 touchPoint = touch->getLocation();

    if (pointInsideButton(touchPoint)) {
        setButtonClicked();
    }
    else {
        setButtonNormal();
    }
}

void ThisLevel::setButtonNormal() {
    buttonItem->unselected(); // �ָ�Ϊ����״̬
}

void ThisLevel::setButtonHover() {
    buttonItem->selected(); // �л�����ͣ״̬
}

void ThisLevel::setButtonClicked() {
    // ����ť����¼�
    // ����������ִ�а�ť�������߼�
    setButtonNormal();
}

bool ThisLevel::pointInsideButton(const Vec2& point) {
    // �жϴ������Ƿ��ڰ�ť��
    Rect buttonRect = buttonItem->getBoundingBox();
    return buttonRect.containsPoint(point);
}*/
