#include "ThisLevel.h"

using namespace cocos2d;
int ThisLevel::money=0;
Sprite* ThisLevel::moneyNumber = nullptr;

bool ThisLevel::init(const int& level)
{
    cleanUp();

    moneyNumber = Sprite::create();
    moneyNumber->setPosition(350, 1030);
    moneyNumber->setScale(2.0f);
    changeMoney(0, true);
    addChild(moneyNumber,100);

    auto moneySquare = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("Coin.png"));
    addChild(moneySquare);
    moneySquare->setPosition(350, 1030);
    moneySquare->setScale(2.0f);

    position_x = 0;
    position_y = 0;
    this_level = level;

    this_music = SoundManager::getInstance();

    if (!Scene::init())
    {
        return false;
    }
    //��������
    this->initWithPhysics();


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
            this_music->onEffect();
            if (leftmenu || rightmenu || topmenu || bottommenu) {//����tower��ɾ��
                ToNull();
            }
            ThisLevel::createTower();
        });
    buttonItem->setScale(160 / buttonItem->getContentSize().width, 135 / buttonItem->getContentSize().height);
    // ������ť
    menu = Menu::create(buttonItem, nullptr);
    menu->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    menu->setPosition(Vec2(80, 67));
    addChild(menu, 40);

    // ע������¼�������
    auto mouseListener = cocos2d::EventListenerMouse::create();
    mouseListener->onMouseMove = CC_CALLBACK_1(ThisLevel::onMouseMove, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(mouseListener, this);

    this->schedule(CC_SCHEDULE_SELECTOR(ThisLevel::update), 0.1f);

    auto plate = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("clock.PNG"));
    auto num = Sprite::create();
    Vector<SpriteFrame*>frames;
    frames.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("lastthree.PNG"));
    frames.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("lasttwo.PNG"));
    frames.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("lastone.PNG"));
    auto animation = Animation::createWithSpriteFrames(frames, 1.0f);
    auto animate = Animate::create(animation);
    auto delay = DelayTime::create(1.0f);
    auto sequence = Sequence::create(animate, delay, RemoveSelf::create(), nullptr);
    auto _delay = DelayTime::create(3.0f);
    auto _se = Sequence::create(_delay, RemoveSelf::create(), nullptr);
    num->runAction(sequence);
    num->setPosition(plate->getContentSize() / 2);
    plate->runAction(_se);
    plate->setScale(2.0f);
    plate->setPosition(960, 540);
    plate->addChild(num);
    this->addChild(plate, 120);

    auto pause0 = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("pause0.png"));
    auto pause1 = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("pause1.png"));
    auto _pause = MenuItemSprite::create(pause0, pause1, [this](Ref* pSender) {
        Director::getInstance()->pause();
        pauseMenu(); });
    auto back = Menu::create(_pause, NULL);
    back->setAnchorPoint(Vec2(0, 0));
    back->setPosition(1800, 1020);
    back->setScale(1.6f);
    this->addChild(back, 5);


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
        case 7:return "../Resources/level007.png";
        case 8:return "../Resources/level008.png";
        case 9:return "../Resources/level009.png";
        case 10:return "../Resources/level0010.png";
        default:
            break;
    }
    return "";
}


//����ÿʱ�̵ı仯
void ThisLevel::update(float delta) {
    Tower::upDate(delta);
}

void ThisLevel::pauseMenu()
{
    for (auto& child : this->getChildren()) {
        // �жϽڵ��Ƿ�Ϊ��ť��������谴ť�� Button ���ͣ�
        auto button = dynamic_cast<Menu*>(child);
        if (button) {
            // ���ð�ť�Ĵ���
            button->setEnabled(false);
        }
    }
    pausemenu = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("gamemenu.png"));
    auto button10 = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("continue1.png"));
    auto button11 = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("continue0.png"));
    auto button20 = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("restart0.png"));
    auto button21 = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("restart1.png"));
    auto button30 = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("select0.png"));
    auto button31 = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("select1.png"));
    auto button1 = MenuItemSprite::create(button10, button11, [this](Ref* pSender) {
        pausemenu->pause();
        auto se = Sequence::create(FadeOut::create(0.5f), RemoveSelf::create(), nullptr);
        pausemenu->runAction(se->clone());
        buttons->runAction(se);
        Director::getInstance()->resume();
        for (auto& child : this->getChildren()) {
            // �жϽڵ��Ƿ�Ϊ��ť
            auto button = dynamic_cast<Menu*>(child);
            if (button) {
                // ���ð�ť�Ĵ���
                button->setEnabled(true);
            }
        }});
    auto button2 = MenuItemSprite::create(button20, button21, [this](Ref* pSender) {
        cleanUp();
        auto scene = ThisLevel::create(this_level);
        Director::getInstance()->resume();
        Director::getInstance()->replaceScene(scene);
        });
    auto button3 = MenuItemSprite::create(button30, button31, [this](Ref* pSender) {
        Director::getInstance()->resume();
        Director::getInstance()->popScene();
        cleanUp(); });
    buttons = Menu::create(button1, button2, button3, nullptr);
    buttons->alignItemsVerticallyWithPadding(25.0f);
    buttons->setPosition(205.999893, 173.999954);
    pausemenu->addChild(buttons);
    pausemenu->setPosition(960,540);
    pausemenu->setScale(1.5f);
    this->addChild(pausemenu, 150);
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
        !Resource::find(mouseX,mouseY,this_level)) {
        if (!(leftmenu || rightmenu || topmenu || bottommenu)&& Resource::find(mouseX, mouseY, this_level)) {
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
                auto firsttower = Tower::buildTower(1, Vec2(float(position_x * 160) + 80, float((position_y) * 135) + 67));
                ToNull();
        });
    leftmenu = Menu::create(leftButton, nullptr);
    leftmenu->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    leftmenu->setPosition(float(position_x * 160) + 80, float((position_y) * 135) + 67);
    leftmenu->runAction(leftAction);
    // �ұ߰�ť
    auto rightButton = MenuItemSprite::create(rightSprite, rightSprite,
        [this](Ref* pSender) {
            auto firsttower = Tower::buildTower(3, Vec2(float(position_x * 160) + 80, float((position_y) * 135) + 67));
            ToNull();
        });
    rightmenu = Menu::create(rightButton, nullptr);
    rightmenu->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    rightmenu->setPosition(float(position_x * 160) + 80, float((position_y) * 135) + 67);
    rightmenu->runAction(rightAction);
    // �ϱ߰�ť
    auto topButton = MenuItemSprite::create(topSprite, topSprite,
        [this](Ref* pSender) {
            auto firsttower = Tower::buildTower(4, Vec2(float(position_x * 160) + 80, float((position_y) * 135) + 67));
            ToNull();
        });
    topmenu = Menu::create(topButton, nullptr);
    topmenu->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    topmenu->setPosition(float(position_x * 160) + 80, float((position_y) * 135) + 67);
    topmenu->runAction(topAction);
    // �±߰�ť
    auto bottomButton = MenuItemSprite::create(bottomSprite, bottomSprite,
        [this](Ref* pSender) {
            auto firsttower = Tower::buildTower(5, Vec2(float(position_x * 160) + 80, float((position_y) * 135) + 67));
            ToNull();
        });
    bottommenu = Menu::create(bottomButton, nullptr);
    bottommenu->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    bottommenu->setPosition(float(position_x * 160) + 80, float((position_y) * 135) + 67);
    bottommenu->runAction(bottomAction);
    // ... ����������ť�Ĵ��� ...

    // ���°�ť��ӵ��������
    this->addChild(leftmenu,100);
    this->addChild(rightmenu,100);
    this->addChild(topmenu,100);
    this->addChild(bottommenu,100);
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

bool ThisLevel::changeMoney(const int num, const bool i)
{
    if (moneyNumber == nullptr)
        return false;
    int count=0;
    if (i) {
        count=money= 600;
    }
    else {
        count = money + num;
        if (count < 0)
            return false;
        money = count;
    }
    moneyNumber->removeAllChildren();
    int position = 0;
    do {
        int i = count % 10;
        count /= 10;
        auto p=cocos2d::StringUtils::format("num%d.png", i);
        auto thisNum = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(p));
        thisNum->setPosition(position, 0);
        position -= 21;
        moneyNumber->addChild(thisNum);
    } while (count > 0);
    return true;
}

void ThisLevel::cleanUp()
{
    Tower::clearup();
    moneyNumber = nullptr;
    money = 0;
}