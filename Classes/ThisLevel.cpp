#include "ThisLevel.h"

using namespace cocos2d;

ThisLevel* ThisLevel::instance = nullptr;


ThisLevel* ThisLevel::getInstance()
{
    return instance;
}

bool ThisLevel::init(const int& level)
{  
    if (!Scene::init())
    {
        return false;
    }
    this_music = SoundManager::getInstance();
    res = Resource::getInstance();
    this_level = level;
    time = 0;
    lastTime = 0.0f;
    currentTime = 0.0f;
    currentWave = -1;
    maxWave = res->levelData[this_level].monsters.size();
    p = res->levelData[this_level].monsters;
    monsterCount = 0;

    moneyNumber = Sprite::create();
    moneyNumber->setPosition(350, 1030);
    moneyNumber->setScale(2.0f);
    changeMoney(0, true);
    addChild(moneyNumber,100);

    auto moneySquare = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("Coin.png"));
    addChild(moneySquare);
    moneySquare->setPosition(350, 1030);
    moneySquare->setScale(2.0f);



    //物理世界
    this->initWithPhysics();
    // 获取物理世界
    auto physicsWorld = this->getPhysicsWorld();
    // 设置全局重力向量为零
    physicsWorld->setGravity(Vec2(0.0f, 0.0f));
    physicsWorld->setAutoStep(false);

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

    // 创建按钮菜单项

    buttonItem = MenuItemSprite::create(buttonNormal, buttonNormal,
        [this](Ref* pSender) {
            this_music->onEffect();
            buttonItem->setEnabled(false);
            menuEnabled = false;
            if (towers.find(lastPosition)==towers.end())
                createTower();
            else
               createTowerMenu(towers[lastPosition].these);
        });
    buttonItem->setScale(160 / buttonItem->getContentSize().width, 135 / buttonItem->getContentSize().height);
    // 创建按钮
    menu = Menu::create(buttonItem, nullptr);
    menu->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    menu->setPosition(Vec2(80, 67));
    addChild(menu, 40);

    // 注册鼠标事件监听器
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
        this_music->onEffect();
        Director::getInstance()->pause();
        pauseMenu(); });
    auto back = Menu::create(_pause, NULL);
    back->setAnchorPoint(Vec2(0, 0));
    back->setPosition(1800, 1020);
    back->setScale(1.6f);
    this->addChild(back, 100);
    instance = this;
    //建立萝卜菜单
    radish = Radish::create();
    this->addChild(radish, 100);
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

//更新每时刻的变化
void ThisLevel::update(float delta)
{
    if (isEnd) {
        this->getPhysicsWorld()->step(delta);
        currentTime += delta;
        //出兵
        if (currentWave < maxWave) {
            if (monsterCount == 0 && currentWave < maxWave - 1 && currentTime - lastTime >= p[currentWave + 1].time) {
                currentWave++;
                monsterCount = p[currentWave].num;
                lastTime = currentTime;
            }
            else if (monsterCount != 0 && currentTime - lastTime >= p[currentWave].delay) {
                lastTime = currentTime;
                monsters.push_back(Monster::create(p[currentWave].ID, this_level));
                monsterCount--;
            }
        }

        radish->outoMusic(delta);

        for (auto& item : towers) {
            item.second.hasSearched = false;
        }
        Coor finalPoint = res->levelPath[0][this_level];
        Coor p;

        for (int i = 0; i < monsters.size();) {
            p = transform(monsters[i]->getPosition());
            if (p == finalPoint) {
                monsters[i]->removeFromParentAndCleanup(true);
                monsters.erase(monsters.begin() + i);
                if (radish->takeDamage(1)) {
                    this->stopAllActions();
                    isEnd = false;
                }
                continue;
            }
            for (auto& item : towers) {
                if (!item.second.hasSearched && p * item.first <= item.second.RG) {
                    item.second.these->attack(delta, monsters[i]->getPosition());
                    item.second.hasSearched = true;
                }
            }
            i++;
        }
        if (currentWave == maxWave - 1 && monsterCount == 0 && monsters.size() == 0 ) {
            this->stopAllActions();
            isEnd = false;
        }
    }
    else {
        time += delta;
        if(time>2.0f)
            settle(radish->blood);
    }
}

void ThisLevel::pauseMenu()
{
    for (auto& child : this->getChildren()) {
        // 判断节点是否为按钮（这里假设按钮是 Button 类型）
        auto button = dynamic_cast<Menu*>(child);
        if (button) {
            // 禁用按钮的触摸
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
        this_music->onEffect();
        pausemenu->pause();
        auto se = Sequence::create(FadeOut::create(0.5f), RemoveSelf::create(), nullptr);
        pausemenu->runAction(se->clone());
        pauseMenuButtons->runAction(se);
        Director::getInstance()->resume();
        for (auto& child : this->getChildren()) {
            // 判断节点是否为按钮
            auto button = dynamic_cast<Menu*>(child);
            if (button) {
                // 启用按钮的触摸
                button->setEnabled(true);
            }
        }});
    auto button2 = MenuItemSprite::create(button20, button21, [this](Ref* pSender) { 
        this_music->onEffect();
        this->unscheduleAllCallbacks();
        this->stopAllActions();
        instance = nullptr;
        auto scene = ThisLevel::create(this_level);
        Director::getInstance()->resume();
        Director::getInstance()->replaceScene(scene);
        });
    auto button3 = MenuItemSprite::create(button30, button31, [this](Ref* pSender) {
        this_music->onEffect();
        this->unscheduleAllCallbacks();
        this->stopAllActions();
        instance = nullptr;
        Director::getInstance()->resume();
        auto p = SelectMenu::scene(); 
        Director::getInstance()->replaceScene(p); });
    pauseMenuButtons = Menu::create(button1, button2, button3, nullptr);
    pauseMenuButtons->alignItemsVerticallyWithPadding(25.0f);
    pauseMenuButtons->setPosition(205.999f, 173.99f);
    pausemenu->addChild(pauseMenuButtons);
    pausemenu->setPosition(960,540);
    pausemenu->setScale(1.5f);
    this->addChild(pausemenu, 150);
}

void ThisLevel::onMouseMove(cocos2d::Event* event)
{
    //判断选择框是否存在
    auto mouseEvent = static_cast<cocos2d::EventMouse*>(event);
    if (mouseEvent) {
        mouseP = transform( Vec2(mouseEvent->getCursorX(), mouseEvent->getCursorY()));
    }
    if (menuEnabled) {
        if (!(lastPosition == mouseP)&& res->find(mouseP,this_level)) {
            menu->setPosition(transform(mouseP));
            lastPosition = mouseP;
        }
    }
} 


void ThisLevel::createTower()
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
        bottomSprite = Sprite::create("../Resources/CanClick5_1.PNG");
    }
    else {
        bottomSprite = Sprite::create("../Resources/CanClick5_0.PNG");
    }
    leftSprite->setScale(1.5f);
    rightSprite->setScale(1.5f);
    topSprite->setScale(1.5f);
    bottomSprite->setScale(1.5f);
    auto leftAction = MoveTo::create(0.2f, Vec2(float(lastPosition.x * 160) + 80 - buttonWidth, float((lastPosition.y) * 135) + 55));
    auto rightAction = MoveTo::create(0.2f, Vec2(float(lastPosition.x * 160) + 40 + buttonWidth, float((lastPosition.y) * 135) + 55));
    auto topAction = MoveTo::create(0.2f, Vec2(float(lastPosition.x * 160) + 60, float((lastPosition.y) * 135) + 55 + buttonHeight));
    auto bottomAction = MoveTo::create(0.2f, Vec2(float(lastPosition.x * 160) + 60, float((lastPosition.y) * 135) + 55 - buttonHeight));
    // 左边按钮
    auto here = transform(lastPosition);
    auto leftButton = MenuItemSprite::create(leftSprite, leftSprite,
        [this](Ref* pSender) {
            if (changeMoney(-100)) {
                towers.emplace(lastPosition, towerNature{ false,BottleTower::create(1,transform(lastPosition)),2 });
                ToNull();
            }
        });
    // 右边按钮
    auto rightButton = MenuItemSprite::create(rightSprite, rightSprite,
        [this](Ref* pSender) {
            if (changeMoney(-160)) {
                towers.emplace(lastPosition, towerNature{ false,StarTower::create(3,transform(lastPosition)),3 });
                ToNull();
            }
        });
    // 上边按钮
    auto topButton = MenuItemSprite::create(topSprite, topSprite,
        [this](Ref* pSender) {
            if (changeMoney(-160)) {
                towers.emplace(lastPosition, towerNature{ false,FanTower::create(4,transform(lastPosition)),3 });
                ToNull();
            }
        });
    // 下边按钮
    auto bottomButton = MenuItemSprite::create(bottomSprite, bottomSprite,
        [this](Ref* pSender) {
            if (changeMoney(-160)) {
                towers.emplace(lastPosition, towerNature{ false,MagicTower::create(5,transform(lastPosition)),2 });
                ToNull();
            }
        });
    leftButton->setPosition(here);
    leftButton->runAction(leftAction);
    rightButton->setPosition(here);
    rightButton->runAction(rightAction);
    topButton->setPosition(here);
    topButton->runAction(topAction);
    bottomButton->setPosition(here);
    bottomButton->runAction(bottomAction);

    selectMenu = Menu::create(leftButton, rightButton, topButton, bottomButton,nullptr);
    selectMenu->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
    selectMenu->setPosition(0, 0);
    // ... 其他创建按钮的代码 ...

    auto bg = MenuItem::create([this](Ref* pSender) {
        buttonItem->setEnabled(true);
        ToNull(); });
    bg->setContentSize(Size(1920, 1080));
    bg->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
    bg->setPosition(0, 0);
    bg->setLocalZOrder(10);
    selectMenu->addChild(bg);

    // 将新按钮添加到场景或层
    this->addChild(selectMenu, 100);
}

//将选择菜单删除
void ThisLevel::ToNull() {
    selectMenu->removeFromParentAndCleanup(true);
    selectMenu = nullptr;
    menuEnabled = true;
    buttonItem->setEnabled(true);
}

void ThisLevel::createTowerMenu(Tower* it)
{
    cost = it->data->UPGC[it->level];
    price = it->data->PR[it->level];
    float range = it->data->AR;
    ThisLevel::it = it;
    Sprite* up = Sprite::createWithSpriteFrameName(res->getIcon(cost,cost < money));
    Sprite* destory = Sprite::createWithSpriteFrameName(res->getSellPrice(price));
    auto levelUp = MenuItemSprite::create(up, up, [this](Ref* pSender) {
        if (ThisLevel::changeMoney(-cost)) {
            ToNull();
            ThisLevel::it->levelUp();
        }});
    levelUp->setScale(1.5f);
    auto remove = MenuItemSprite::create(destory, destory, [this](Ref* pSender) {
            ThisLevel::changeMoney(price);
            towers.erase(transform(ThisLevel::it->position));
            ThisLevel::it->destoryTower();
            ToNull();
          });
    remove->setScale(1.5f);
    levelUp->setPosition(Vec2(float(lastPosition.x * 160) + 80.0f, float(lastPosition.y * 135) + 202.0f));
    remove->setPosition(Vec2(float(lastPosition.x * 160) + 80.0f, float(lastPosition.y * 135) - 67.5f));


    selectMenu = Menu::create(levelUp, remove, NULL);
    selectMenu->setPosition(0, 0);
    selectMenu->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
    auto fadeIn = FadeIn::create(0.2f);
    selectMenu->runAction(fadeIn);
    auto bg = MenuItem::create([this](Ref* pSender) {
        buttonItem->setEnabled(true);
        ToNull(); });
    bg->setContentSize(Size(1920, 1080));
    bg->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
    bg->setPosition(0, 0);
    bg->setLocalZOrder(10);
    selectMenu->addChild(bg);
    auto theRange = Sprite::create("../Resources/AttackRange.PNG");
    theRange->setScaleX(2 * range / theRange->getContentSize().width);
    theRange->setScaleY(2 * range/ theRange->getContentSize().height);
    theRange->setOpacity(100);
    auto _theRange = MenuItem::create();
    _theRange->addChild(theRange);
    _theRange->setPosition(transform(lastPosition));
    selectMenu->addChild(_theRange, -10);
    this->addChild(selectMenu,100);
}

bool ThisLevel::changeMoney(const int num, const bool i)
{
    if (moneyNumber == nullptr)
        return false;
    int count=0;
    if (i) {
        count = money = res->levelData[this_level].moneyNum;
    }
    else {
        count = money + num;
        if (count < 0)
            return false;
        money = count;
    }
    if (num > 0)
        this_music->onEffect(15);
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

void ThisLevel::settle(const int hp)
{
    instance = nullptr;
    int a = 0;

    if (hp == 0) {
        a = 4;
    }
    else if (hp == 10) {
        a = 3;
        if (this_level < 10 && res->gameData[this_level + 1] < 1)
            res->gameData[this_level + 1] = 4;
        res->gameData[this_level] = 3;
    }
    else if (hp >= 5) {
        a = 2;
        if (this_level < 10 && res->gameData[this_level + 1] < 1)
            res->gameData[this_level + 1] = 4;
        if (res->gameData[this_level] < 2)
            res->gameData[this_level] = 2;

    }
    else {
        a = 1;
        if (this_level < 10 && res->gameData[this_level + 1] < 1)
            res->gameData[this_level + 1] = 4;
        if (res->gameData[this_level] == 4)
            res->gameData[this_level] = 1;

    }
    VictoryScene* p = VictoryScene::create(this_level, a);
    Director::getInstance()->replaceScene(p);
}
