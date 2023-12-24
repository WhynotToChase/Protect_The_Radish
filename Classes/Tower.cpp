#include "Tower.h"

using namespace cocos2d;

#define SIZE 1.8f

float Tower::currentTime = 0.0f;
std::vector<Tower*> Tower::towers = std::vector<Tower*>();

void Tower::setAttackAction(const int ID, const int level, Sprite* tower, Sequence* action)
{
    Vector<SpriteFrame*> frames;
    auto data = Resource::getTowerDataById(ID);
    auto& x = data.action[level];
    if (ID == 1 || ID == 5) {
        for (auto& z : x)
            frames.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName(z));
        frames.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName(x[0]));
        Animation* p = Animation::createWithSpriteFrames(frames, 0.2f);
        Animate* q = Animate::create(p);
        if (action != nullptr) {
            auto se = Sequence::create(action, q, nullptr);
            tower->runAction(se);
        }
        tower->runAction(q);
    }
    else {
        auto circle = RotateBy::create(data.actionDelay, 360.0f);
        tower->runAction(circle);
    }
}

void Tower::clearup()
{
    currentTime = 0.0f;
    for (auto& p : towers) {
        delete p;
    }
}

// 获取当前时间戳的函数
void Tower::getCurrentTime()
{
    currentTime = std::chrono::duration_cast<std::chrono::milliseconds>(
        std::chrono::system_clock::now().time_since_epoch()
    ).count() / 1000.0f;
}

void Tower::upDate()
{
    wholeAttack();
    TowerMenu::upDate();
}

bool Tower::hasBuilt(const Vec2& position)
{
    for (auto& p : towers) {
        if (p->getPosition() == position)
            return true;
   }
    return false;
}

void Tower::wholeAttack()
{
    getCurrentTime();
    for (auto& tower : towers) {
        tower->attack();
   }
}

bool Tower::buildTower(const int ID ,const Vec2& position)
{
    if (!hasBuilt(position)) {
        Tower* p;
        switch (ID) {
            case 1:
                p = new BottleTower(position);
                break;
            case 3:
                p = new StarTower(position);
                break;
            case 4:
                p = new FanTower(position);
                break;
            case 5:
                p = new MagicTower(position);
                break;
            default:
                return false;
        }
        // ThisLevel::changeMoney(-getTowerDataById(ID).BLDC);
        towers.push_back(p);
        return true;
    }
    return false;
}

void Tower::deleteTower()
{
    auto sequence = Sequence::create(RemoveSelf::create(),nullptr);
    getWhole()->runAction(sequence);
    Effect::create(CARTTON,getPosition());

    auto iter = std::find(towers.begin(), towers.end(), this);
    if (iter != towers.end()) {
        towers.erase(iter);
        delete this;
    }
}

void Tower::attack()
{
    auto p = Resource::getTowerDataById(getID());
    if (currentTime -getLastTime() > p.AS[getLevel()]) {
        setLastTime(currentTime);
        auto place = getPosition();
        auto tower = getTowerBady();
        Vec2 enemy = Vec2(0, 0);//Monster::searchEnemy(place);
        if (enemy.distance(place) <= p.AR) {
            setAttackAction(getID(), getLevel(), tower);
            //Bullet::setupBullet(place, enemy, getID());
        }
    }
}

void Tower::levelUp()
{
    if (getLevel() < 3) {
        Effect::create(CARTTON,getPosition());
        getTowerBady()->setSpriteFrame(Resource::getTowerDataById(getID()).action[getLevel() + 1][0]);
        if (getID() == 3||getID()==4)
            getTowerLamp()->setSpriteFrame(Resource::getTowerDataById(getID()).lamp[getLevel() + 1]);
        addLevel();
    }
}


const int BottleTower::ID = 1;

BottleTower::BottleTower(const cocos2d::Vec2& p)
{
    level = 1;
    lastTime = 0.0f;  
    position = p;
   
    body= Sprite::createWithSpriteFrameName(Resource::getTowerDataById(ID).action[level][0]);
    auto lamp = Sprite::createWithSpriteFrameName(Resource::getTowerDataById(ID).lamp[level]);
    body->setScale(SIZE);
    lamp->setScale(SIZE);


    auto bg = Sprite::create("../Resources/1.png");
    bg->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    bg->setOpacity(0);
    auto _bg = MenuItemSprite::create(bg,bg, [this](Ref* pSender) {
        SoundManager::getInstance()->onButtonEffect();
            TowerMenu::create(this);  });
    auto BG = Menu::create(_bg, NULL);
    BG->setPosition(0, 0);

    whole = Sprite::create();
    whole->addChild(lamp);
    whole->addChild(body);
    whole->addChild(BG);
    whole->setPosition(p);
    Director::getInstance()->getRunningScene()->addChild(whole, 50);
    Effect::create(CARTTON, getPosition());
    
}

void BottleTower::attack()
{
    auto p = Resource::getTowerDataById(ID);
    if (currentTime - lastTime > p.AS[level]) {
        lastTime = currentTime;
        Vec2 enemy = Vec2(0, 0);// Monster::searchEnemy(bottle->getPosition());
        if (enemy.distance(position) <= p.AR) {
            Vec2 direction = enemy - position;
            Vec2 normalizedDirection = direction.getNormalized();
            // 计算旋转角度（弧度）
            float angle = CC_RADIANS_TO_DEGREES(atan2(normalizedDirection.y, normalizedDirection.x)) - body->getRotation();
            // 创建旋转动画
            auto rotateBy = RotateBy::create(angle / 360.0f, angle);
            auto action = Sequence::create(rotateBy, nullptr);
            setAttackAction(ID, level, body,action);
           // Bullet::setupBullet(position, enemy, ID);
        }
    }
}

const int StarTower::ID = 3;

StarTower::StarTower(const cocos2d::Vec2& p)
{
    level = 1;
    lastTime = 0.0f;
    position = p;

    body = Sprite::createWithSpriteFrameName(Resource::getTowerDataById(ID).action[level][0]);
    lamp = Sprite::createWithSpriteFrameName(Resource::getTowerDataById(ID).lamp[level]);
    body->setScale(SIZE);
    lamp->setScale(SIZE);


    auto bg = Sprite::create("../Resources/1.png");
    bg->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    bg->setOpacity(0);
    auto _bg = MenuItemSprite::create(bg, bg, [this](Ref* pSender) {
        SoundManager::getInstance()->onButtonEffect();
        TowerMenu::create(this);  });
    auto BG = Menu::create(_bg, NULL);
    BG->setPosition(0, 0);

    whole = Sprite::create();
    whole->addChild(lamp);
    whole->addChild(body);
    whole->addChild(BG);
    whole->setPosition(p);
    Director::getInstance()->getRunningScene()->addChild(whole, 50);
    Effect::create(CARTTON, getPosition());
}

const int FanTower::ID = 4;

FanTower::FanTower(const cocos2d::Vec2& p)
{
    level = 1;
    lastTime = 0.0f;
    position = p;

    body = Sprite::createWithSpriteFrameName(Resource::getTowerDataById(ID).action[level][0]);
    lamp = Sprite::createWithSpriteFrameName(Resource::getTowerDataById(ID).lamp[level]);
    body->setScale(SIZE);
    lamp->setScale(SIZE);


    auto bg = Sprite::create("../Resources/1.png");
    bg->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    bg->setOpacity(0);
    auto _bg = MenuItemSprite::create(bg, bg, [this](Ref* pSender) {
        SoundManager::getInstance()->onButtonEffect();
        TowerMenu::create(this);  });
    auto BG = Menu::create(_bg, NULL);
    BG->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    BG->setPosition(0, 0);

    whole = Sprite::create();
    whole->addChild(lamp);
    whole->addChild(body);
    whole->addChild(BG);
    whole->setPosition(p);
    Director::getInstance()->getRunningScene()->addChild(whole, 50);
    Effect::create(CARTTON, getPosition());
}

const int MagicTower::ID = 5;

MagicTower::MagicTower(const cocos2d::Vec2& p)
{
    level = 1;
    lastTime = 0.0f;
    position = p;

    body = Sprite::createWithSpriteFrameName(Resource::getTowerDataById(ID).action[level][0]);
    body->setScale(SIZE);


    auto bg = Sprite::create("../Resources/1.png");
    bg->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    bg->setOpacity(0);
    auto _bg = MenuItemSprite::create(bg, bg, [this](Ref* pSender) {
        SoundManager::getInstance()->onButtonEffect();
        TowerMenu::create(this);  });
    auto BG = Menu::create(_bg, NULL);
    BG->setPosition(0, 0);

    whole = Sprite::create();
    whole->addChild(body);
    whole->addChild(BG);
    whole->setPosition(p);
    Director::getInstance()->getRunningScene()->addChild(whole, 50);
    Effect::create(CARTTON, getPosition());
}


bool TowerMenu::canUp=false;
Tower* TowerMenu::_tower=nullptr;
int TowerMenu::level=1;
cocos2d::Menu* TowerMenu::menu = nullptr;
cocos2d::Sprite* TowerMenu::up = nullptr;
Rect TowerMenu::range=Rect(0,0,0,0);

bool TowerMenu::init(Tower* tower) 
{
    if (!Menu::init()) {
        return false;
    }

    if (menu != nullptr)
        return false;
    _tower = tower;
    auto& data = Resource::getTowerDataById(_tower->getID());
    level=_tower->getLevel();

    auto& pos = tower->getPosition();
    range = Rect(pos.x - 80.0f, pos.y - 67.5f, 160.0f, 135.0f);

    canUp = true;//data.UPGC[level] < ThisLevel::getMoney();
    Sprite* up = Sprite::createWithSpriteFrameName(Resource::getIcon(data.UPGC[level], canUp));
    TowerMenu::up = up;
    Sprite* destory = Sprite::createWithSpriteFrameName(Resource::getSellPrice(data.PR[level]));
    auto levelUp = MenuItemSprite::create(up, up, [this](Ref* pSender) {
        SoundManager::getInstance()->onButtonEffect();
        if (canUp) {
            menu->removeFromParentAndCleanup(true);
            menu = nullptr;
            _tower->levelUp();
            /* ThisLevel::changeMoney(-data->UPGC[level]);*/
        }});
    auto remove = MenuItemSprite::create(destory, destory, [this](Ref* pSender) {
        SoundManager::getInstance()->onButtonEffect();
        _tower->deleteTower();
        menu->removeFromParentAndCleanup(true);
        menu = nullptr;
        /*ThisLevel::changeMoney(data->PR[level]);*/ });
    
    menu = Menu::create( levelUp,remove, NULL);
    menu->alignItemsVerticallyWithPadding(150);
    menu->setPosition(pos);
    auto fadeIn = FadeIn::create(0.2f);
    menu->setOpacity(0);
    menu->runAction(fadeIn);
    Director::getInstance()->getRunningScene()->addChild(menu,100);
    // 注册鼠标移动事件监听器
    auto mouseListener = EventListenerMouse::create();
    mouseListener->onMouseUp = CC_CALLBACK_1(TowerMenu::onMouseUp, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(mouseListener, menu);

    return true;
}

void TowerMenu::upDate()
{
    if (!menu)
        return;
    if (canUp != false) {//(data->UPGC[level]<ThisLevel::getMenoy))
        up->setSpriteFrame(Resource::getIcon(Resource::getTowerDataById(_tower->getID()).UPGC[level], canUp));
    }
}

void TowerMenu::onMouseUp(Event* event)
{
    EventMouse* e = dynamic_cast<EventMouse*>(event); // 将事件对象转换为鼠标事件对象
    if (e)
    {
        Vec2 mousePosition = Vec2(e->getCursorX(), e->getCursorY());
        if (!range.containsPoint(mousePosition)) {
            menu->removeFromParentAndCleanup(true);
            menu = nullptr;
        }
    }
}

