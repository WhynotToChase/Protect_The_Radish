#include "Tower.h"
#include <cmath>

using namespace cocos2d;

#define SIZE 1.8f

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
    for (auto& p : towers) {
        delete p;
    }
    towers.clear();
}

void Tower::upDate(const float delat)
{
    for (auto& tower : towers) {
        tower->attack(delat);
   }
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

bool Tower::buildTower(const int ID ,const Vec2& position)
{
    if (!hasBuilt(position)&&ThisLevel::changeMoney(-Resource::getTowerDataById(ID).BLDC)) {
        SoundManager::getInstance()->onEffect(2);
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
        towers.push_back(p);
        return true;
    }
    return false;
}

void Tower::deleteTower()
{
    SoundManager::getInstance()->onEffect(6);
    auto sequence = Sequence::create(RemoveSelf::create(),nullptr);
    getWhole()->runAction(sequence);
    Effect::create(CARTTON,getPosition());

    auto iter = std::find(towers.begin(), towers.end(), this);
    if (iter != towers.end()) {
        towers.erase(iter);
        delete this;
    }
}

void Tower::attack(const float& delat)
{
    auto& p = Resource::getTowerDataById(getID());
    if ((getLastTime() += delat) > p.AS[getLevel()]) {
        setLastTime();
        auto& place = getPosition();
        auto tower = getTowerBady();
        Vec2 enemy = Vec2(1000,500);//Monster::searchEnemy(place);
        if (place.distance(enemy)<= p.AR) {
            setAttackAction(getID(), getLevel(), tower);
            if (getID() != 3)
                Bullet::setupBullet(place, enemy, getID(), getLevel(), p.AR);
            else
                Bullet::setupBullet(place, enemy, 3, 1, p.AR);
        }
    }
}

void Tower::levelUp()
{
    if (getLevel() < 3) {
        SoundManager::getInstance()->onEffect(7);
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
    lastTime = -1.0f;  
    position = p;
   
    body= Sprite::createWithSpriteFrameName(Resource::getTowerDataById(ID).action[level][0]);
    auto lamp = Sprite::createWithSpriteFrameName(Resource::getTowerDataById(ID).lamp[level]);
    body->setScale(SIZE);
    lamp->setScale(SIZE);

    auto bg = Sprite::create("../Resources/1.png");
    bg->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    bg->setOpacity(0);
    auto _bg = MenuItemSprite::create(bg,bg, [this](Ref* pSender) {
        SoundManager::getInstance()->onEffect();
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

void BottleTower::attack(const float& delat)
{
    auto& p = Resource::getTowerDataById(ID);
    if ((lastTime+=delat) > p.AS[level]) {
        lastTime = 0.0f;
        Vec2 enemy = Vec2(1000, 500);// Monster::searchEnemy(bottle->getPosition());
        if (enemy.distance(position) <= p.AR) {
            Vec2 normalizedDirection = (enemy-position).getNormalized();
            // 计算旋转角度（弧度）
            float angle = CC_RADIANS_TO_DEGREES(atan2(normalizedDirection.y, normalizedDirection.x));
            // 创建旋转动画
            auto rotateTo = RotateTo::create(fabs(angle / 360.0f), -angle);
            auto action = Sequence::create(rotateTo, nullptr);
            setAttackAction(ID, level, body,action);
            Bullet::setupBullet(position, enemy, ID,level,p.AR);
        }
    }
}

const int StarTower::ID = 3;

StarTower::StarTower(const cocos2d::Vec2& p)
{
    level = 1;
    lastTime = -1.0f;
    position = p;

    body = Sprite::createWithSpriteFrameName(Resource::getTowerDataById(ID).action[level][0]);
    lamp = Sprite::createWithSpriteFrameName(Resource::getTowerDataById(ID).lamp[level]);
    body->setScale(SIZE);
    lamp->setScale(SIZE);

    auto bg = Sprite::create("../Resources/1.png");
    bg->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    bg->setOpacity(0);
    auto _bg = MenuItemSprite::create(bg, bg, [this](Ref* pSender) {
        SoundManager::getInstance()->onEffect();
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
    lastTime = -1.0f;
    position = p;

    body = Sprite::createWithSpriteFrameName(Resource::getTowerDataById(ID).action[level][0]);
    lamp = Sprite::createWithSpriteFrameName(Resource::getTowerDataById(ID).lamp[level]);
    body->setScale(SIZE);
    lamp->setScale(SIZE);

    auto bg = Sprite::create("../Resources/1.png");
    bg->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    bg->setOpacity(0);
    auto _bg = MenuItemSprite::create(bg, bg, [this](Ref* pSender) {
        SoundManager::getInstance()->onEffect();
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
    lastTime = -1.0f;
    position = p;

    body = Sprite::createWithSpriteFrameName(Resource::getTowerDataById(ID).action[level][0]);
    body->setScale(SIZE);


    auto bg = Sprite::create("../Resources/1.png");
    bg->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    bg->setOpacity(0);
    auto _bg = MenuItemSprite::create(bg, bg, [this](Ref* pSender) {
        SoundManager::getInstance()->onEffect();
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
Menu* TowerMenu::menu = nullptr;
Sprite* TowerMenu::up = nullptr;
MenuItem* TowerMenu::levelup = nullptr;
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

    canUp = data.UPGC[level] < ThisLevel::money;
    Sprite* up = Sprite::createWithSpriteFrameName(Resource::getIcon(data.UPGC[level], canUp));
    TowerMenu::up = up;
    Sprite* destory = Sprite::createWithSpriteFrameName(Resource::getSellPrice(data.PR[level]));
    auto levelUp = MenuItemSprite::create(up, up, [this](Ref* pSender) {
        if (canUp&&ThisLevel::changeMoney(-Resource::getTowerDataById(_tower->getID()).UPGC[level])) {
            menu->removeFromParentAndCleanup(true);
            menu = nullptr;
            _tower->levelUp();
        }});
    levelUp->setScale(1.5f);
    levelup = levelUp;
    auto remove = MenuItemSprite::create(destory, destory, [this](Ref* pSender) {   
        ThisLevel::changeMoney(Resource::getTowerDataById(_tower->getID()).PR[level]);
        _tower->deleteTower();
        menu->removeFromParentAndCleanup(true);
        menu = nullptr;
        });
    remove->setScale(1.5f);
    
    menu = Menu::create( levelUp,remove, NULL);
    menu->alignItemsVerticallyWithPadding(150);
    menu->setPosition(pos);
    auto fadeIn = FadeIn::create(0.2f);
    menu->setOpacity(0);
    menu->runAction(fadeIn);

    // 注册鼠标移动事件监听器
    auto mouseListener = EventListenerMouse::create();
    mouseListener->onMouseUp = CC_CALLBACK_1(TowerMenu::onMouseUp, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(mouseListener, menu);

    auto theRange = Sprite::create("../Resources/AttackRange.PNG");
    theRange->setScaleX(2*data.AR / theRange->getContentSize().width);
    theRange->setScaleY(2*data.AR / theRange->getContentSize().height);
    theRange->setOpacity(100); 
    auto _theRange = MenuItem::create();
    _theRange->addChild(theRange);
    menu->addChild(_theRange, -10);

    Director::getInstance()->getRunningScene()->addChild(menu,100);
    return true;
}

void TowerMenu::upDate()
{
    if (!menu)
        return;
    if (canUp = Resource::getTowerDataById(_tower->getID()).UPGC[level]<ThisLevel::money){
        up->setSpriteFrame(Resource::getIcon(Resource::getTowerDataById(_tower->getID()).UPGC[level], canUp));
        up->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
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

