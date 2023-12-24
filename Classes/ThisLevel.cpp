#include "ThisLevel.h"

using namespace cocos2d;

bool ThisLevel::init(const int&level)
{
    money = 0;
    position_x = 0;
    position_y = 0;
    this_level = level;

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

    // ������ť�˵���

    buttonItem = MenuItemSprite::create(buttonNormal, buttonNormal,
        [this](Ref* pSender) {
           this_music->onButtonEffect();
           if (leftmenu || rightmenu || topmenu || bottommenu) {//����tower��ɾ��
               ToNull();
           }
           ThisLevel::createTower();
        });
    buttonItem->setScale(160 / buttonItem->getContentSize().width, 135 / buttonItem->getContentSize().height);
    // ������ť
    menu = Menu::create(buttonItem, nullptr);
    menu->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    menu->setPosition(Vec2(80,67));
    addChild(menu);
    
    // ע������¼�������
    auto mouseListener = cocos2d::EventListenerMouse::create();
    mouseListener->onMouseMove = CC_CALLBACK_1(ThisLevel::onMouseMove, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(mouseListener, this);
    
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

    //auto range=menu->getBoundingBox();
    auto mouseEvent = static_cast<cocos2d::EventMouse*>(event);
    if (mouseEvent) {
        mouseX = mouseEvent->getCursorX();
        mouseY = mouseEvent->getCursorY();
    }
    if ((int(mouseX / 160) == position_x && int(mouseY / 135) == position_y)|| 
        (int(mouseX / 160)+1 == position_x&& int(mouseY / 135) == position_y)|| 
        (int(mouseX / 160) - 1 == position_x && int(mouseY / 135) == position_y) ||
        (int(mouseX / 160) == position_x && int(mouseY / 135)+1 == position_y) ||
        (int(mouseX / 160) == position_x && int(mouseY / 135)-1 == position_y)||
        int(mouseY / 135) == 7) {
        if (!(leftmenu || rightmenu || topmenu || bottommenu)&& int(mouseY / 135) != 7) {
            menu->setPosition(Vec2(float(int(mouseX / 160) * 160) + 80, float(int(mouseY / 135) * 135) + 67));
            position_x = int(mouseX / 160);
            position_y = int(mouseY / 135);
        }
    }
    else {
        if (leftmenu|| rightmenu|| topmenu|| bottommenu) {//����tower��ɾ��
            ToNull();
        }
        
        menu->setPosition(Vec2(float(int(mouseX / 160) * 160)+80, float(int(mouseY / 135) * 135) + 67));
        position_x = int(mouseX / 160);
        position_y = int(mouseY / 135);
        
    }
    
}

void ThisLevel::createTower()
{
    // �ڵ�ǰ��ť����λ�ô����ĸ���ť
    money = 100;
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
        bottomSprite = Sprite::create("../Resources/CanClick5_1.PNG");
    }
    else {
        bottomSprite = Sprite::create("../Resources/CanClick5_0.PNG");
    }
    leftSprite->setScale(1.5f);
    rightSprite->setScale(1.5f);
    topSprite->setScale(1.5f);
    bottomSprite->setScale(1.5f);
    auto leftAction = MoveTo::create(0.2f, Vec2(float(position_x * 160) + 80 - buttonWidth, float((position_y) * 135) + 55));
    auto rightAction = MoveTo::create(0.2f, Vec2(float(position_x * 160) + 40 + buttonWidth, float((position_y) * 135) + 55));
    auto topAction = MoveTo::create(0.2f, Vec2(float(position_x * 160) + 60, float((position_y) * 135) + 55 + buttonHeight));
    auto bottomAction = MoveTo::create(0.2f, Vec2(float(position_x * 160) + 60, float((position_y) * 135) + 55 - buttonHeight));
    // ��߰�ť
    auto leftButton = MenuItemSprite::create(leftSprite, leftSprite,
        [this](Ref* pSender) {
            this_music->onButtonEffect();
            if (money >= 100) {
                money = money - 100;
                auto firsttower = Tower::buildTower(1, Vec2(float(position_x * 160) + 80, float((position_y) * 135) + 67));
            }
            ToNull();
        });
    leftmenu = Menu::create(leftButton, nullptr);
    leftmenu->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    leftmenu->setPosition(float(position_x * 160) + 80, float((position_y) * 135) + 67);
    leftmenu->runAction(leftAction);
    // �ұ߰�ť
    auto rightButton = MenuItemSprite::create(rightSprite, rightSprite,
        [this](Ref* pSender) {
            this_music->onButtonEffect();
            if (money >= 100) {
                auto firsttower = Tower::buildTower(1, Vec2(float(position_x * 160) + 80, float((position_y) * 135) + 67));
            }
            ToNull();
        });
    rightmenu = Menu::create(rightButton, nullptr);
    rightmenu->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    rightmenu->setPosition(float(position_x * 160) + 80, float((position_y) * 135) + 67);
    rightmenu->runAction(rightAction);
    // �ϱ߰�ť
    auto topButton = MenuItemSprite::create(topSprite, topSprite,
       [this](Ref* pSender) {
            this_music->onButtonEffect();
            if (money >= 100) {
                auto firsttower = Tower::buildTower(1, Vec2(float(position_x * 160) + 80, float((position_y) * 135) + 67));
            }
            ToNull();
        });
    topmenu = Menu::create(topButton, nullptr);
    topmenu->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    topmenu->setPosition(float(position_x * 160) + 80, float((position_y) * 135) + 67);
    topmenu->runAction(topAction);
    // �±߰�ť
    auto bottomButton = MenuItemSprite::create(bottomSprite, bottomSprite,
        [this](Ref* pSender) {
            this_music->onButtonEffect();
            if (money >= 100) {
                auto firsttower = Tower::buildTower(1, Vec2(float(position_x * 160) + 80, float((position_y) * 135) + 67));
            }
            ToNull();
        });
    bottommenu = Menu::create(bottomButton, nullptr);
    bottommenu->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    bottommenu->setPosition(float(position_x * 160) + 80, float((position_y) * 135) + 67);
    bottommenu->runAction(bottomAction);
    // ... ����������ť�Ĵ��� ...

    // ���°�ť��ӵ��������
    this->addChild(leftmenu,55);
    this->addChild(rightmenu,55);
    this->addChild(topmenu,55);
    this->addChild(bottommenu,55);
}

//���ĸ�ѡ������
void ThisLevel::ToNull() {
    leftmenu->removeFromParentAndCleanup(true);
    leftmenu = nullptr;
    rightmenu->removeFromParentAndCleanup(true);
    rightmenu = nullptr;
    topmenu->removeFromParentAndCleanup(true);
    topmenu = nullptr;
    bottommenu->removeFromParentAndCleanup(true);
    bottommenu = nullptr;
}

//���Ƿ��������
bool ThisLevel::find() {//
    int level_1[12][8] = {//��һ��
        //0                 1                2                  3
        {0,0,1,1,1,1,1,0},{0,0,0,0,0,0,0,0},{0,1,0,1,1,1,1,0},{0,1,0,1,1,1,1,0},
        //4                 5                6                  7
        {1,1,0,0,1,1,1,0},{1,1,1,0,1,1,1,0},{1,1,1,0,1,1,1,0},{1,1,0,0,1,1,1,0},
        //8                 9                10                 11
        {0,1,0,1,1,1,1,0},{0,1,0,1,1,1,1,0} ,{0,0,0,0,0,0,0,0},{0,0,1,1,1,1,1,0}
    };
    int level_2[12][8] = {//�ڶ���
        //0                 1                2                  3
        {0,0,1,1,1,1,1,0},{0,0,1,1,1,1,1,0},{0,0,0,0,1,1,1,0},{0,0,1,0,1,1,1,0},
        //4                 5                6                  7
        {1,0,1,0,1,0,1,0},{1,0,1,0,1,0,1,0},{1,0,1,0,1,0,1,0},{1,0,1,0,1,0,1,0},
        //8                 9                10                 11
        {0,0,1,0,1,0,1,0} ,{0,1,1,0,0,0,1,0} ,{0,0,1,1,1,1,1,0},{0,0,1,1,1,1,1,0}
    };
    int level_3[12][8] = {//������
        //0                 1                2                  3
        {0,1,1,1,1,1,1,0},{0,0,0,0,0,1,1,0},{0,0,1,1,1,1,1,0},{0,0,1,1,1,1,1,0},
        //4                 5                6                  7
        {1,0,1,1,1,1,1,0},{1,0,0,0,1,1,1,0},{1,1,1,0,1,1,1,0},{1,1,1,0,0,0,1,0},
        //8                 9                10                 11
        {1,1,1,1,0,0,1,0},{0,1,1,1,0,1,1,0} ,{0,1,1,1,0,1,1,0},{0,0,1,1,1,1,1,0}
    };
    int level_4[12][8] = {//���Ĺ�
        //0                 1                2                  3
        {0,0,1,1,0,1,1,0},{0,0,1,1,0,1,1,0},{0,0,0,0,0,1,1,0},{0,0,1,1,1,1,1,0},
        //4                 5                6                  7
        {1,0,0,0,1,1,1,0},{1,1,1,0,1,1,1,0},{1,1,1,0,1,1,1,0},{1,0,0,0,1,1,1,0},
        //8                 9                10                 11
        {0,0,1,1,1,1,1,0},{0,0,1,1,1,1,1,0} ,{0,0,0,0,0,0,1,0},{0,0,1,1,1,1,1,0}
    };
    int level_5[12][8] = {//�����
        //0                 1                2                  3
        {0,0,1,1,1,1,1,0},{0,1,0,0,1,1,1,0},{0,0,0,0,1,1,1,0},{0,1,1,0,1,1,1,0},
        //4                 5                6                  7
        {0,1,1,0,0,1,1,0},{0,1,1,1,0,1,1,0},{0,1,1,1,0,1,1,0},{0,0,0,1,0,0,1,0},
        //8                 9                10                 11
        {0,1,1,1,1,0,1,0},{0,1,1,1,1,0,1,0} ,{0,0,0,0,0,0,1,0},{0,0,1,1,1,1,1,0}
    };
    int level_6[12][8] = {//������
        //0                 1                2                  3
        {0,0,1,1,1,0,1,0},{0,0,1,1,1,0,1,0},{0,1,1,1,1,0,1,0},{0,1,1,1,1,0,1,0},
        //4                 5                6                  7
        {1,1,1,1,1,0,1,0},{1,0,0,0,0,0,1,0},{1,0,1,1,1,1,1,0},{1,0,1,1,1,1,1,0},
        //8                 9                10                 11
        {0,0,1,1,1,1,1,0},{0,0,1,1,1,1,1,0} ,{0,0,1,1,1,1,1,0},{0,0,1,1,1,1,1,0}
    };
    int level_7[12][8] = {//���߹�
        //0                 1                2                  3
        {0,0,1,1,1,1,1,0},{0,0,0,0,0,0,0,0},{0,1,0,1,1,1,1,0},{0,1,0,1,1,1,1,0},
        //4                 5                6                  7
        {1,1,0,0,1,1,1,0},{1,1,1,0,1,1,1,0},{1,1,1,0,1,1,1,0},{1,1,0,0,1,1,1,0},
        //8                 9                10                 11
        {0,1,0,1,1,1,1,0},{0,1,0,1,1,1,1,0} ,{0,0,0,0,0,0,0,0},{0,0,1,1,1,1,1,0}
    };
    int level_8[12][8] = {//�ڰ˹�
        //0                 1                2                  3
        {0,0,1,1,1,1,1,0},{0,0,0,0,0,0,0,0},{0,1,0,1,1,1,1,0},{0,1,0,1,1,1,1,0},
        //4                 5                6                  7
        {1,1,0,0,1,1,1,0},{1,1,1,0,1,1,1,0},{1,1,1,0,1,1,1,0},{1,1,0,0,1,1,1,0},
        //8                 9                10                 11
        {0,1,0,1,1,1,1,0},{0,1,0,1,1,1,1,0} ,{0,0,0,0,0,0,0,0},{0,0,1,1,1,1,1,0}
    };
    int level_9[12][8] = {//�ھŹ�
        //0                 1                2                  3
        {0,0,1,1,1,1,1,0},{0,0,0,0,0,0,0,0},{0,1,0,1,1,1,1,0},{0,1,0,1,1,1,1,0},
        //4                 5                6                  7
        {1,1,0,0,1,1,1,0},{1,1,1,0,1,1,1,0},{1,1,1,0,1,1,1,0},{1,1,0,0,1,1,1,0},
        //8                 9                10                 11
        {0,1,0,1,1,1,1,0},{0,1,0,1,1,1,1,0} ,{0,0,0,0,0,0,0,0},{0,0,1,1,1,1,1,0}
    };
    int level_10[12][8] = {//��ʮ��
        //0                 1                2                  3
        {0,0,1,1,1,1,1,0},{0,0,0,0,0,0,0,0},{0,1,0,1,1,1,1,0},{0,1,0,1,1,1,1,0},
        //4                 5                6                  7
        {1,1,0,0,1,1,1,0},{1,1,1,0,1,1,1,0},{1,1,1,0,1,1,1,0},{1,1,0,0,1,1,1,0},
        //8                 9                10                 11
        {0,1,0,1,1,1,1,0},{0,1,0,1,1,1,1,0} ,{0,0,0,0,0,0,0,0},{0,0,1,1,1,1,1,0}
    };
    return 0;

}
