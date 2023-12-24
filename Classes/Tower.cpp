#include "Tower.h"

using namespace cocos2d;

float Tower::currentTime = 0.0f;
std::vector<Tower*> Tower::towers = std::vector<Tower*>();
SoundManager* Tower::music = NULL;

Animate* Tower::createCartton()
{
    Vector<SpriteFrame*> frames;
    frames.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("Items02-hd_24.PNG"));
    frames.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("Items02-hd_208.PNG"));
    frames.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("Items02-hd_175.PNG"));
    frames.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("Items02-hd_89.PNG"));
    auto p = Animation::createWithSpriteFrames(frames, 0.1f);
    auto q =Animate::create(p);
    return q;
}

Animate* Tower::setAttackAction(int ID, int level)
{
    Animate* q;
    Animation* p;
    Vector<SpriteFrame*> frames;
    auto& x = Resource::getTowerDataById(ID)->action;
    for (int j = 0; j < 3; j++) {
        frames.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName(x[level][j]));
    }
    frames.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName(x[level][0]));
    p = Animation::createWithSpriteFrames(frames, 0.1f);
    q = Animate::create(p);
    frames.clear();
    return q;
}

void Tower::clearup()
{
    music = NULL;
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
    if (music == NULL)
        music = SoundManager::getInstance();
    wholeAttack();
    TowerMenu::upDate();
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
    Tower* p;
    switch (ID) {
        case 1:
            p=new BottleTower(position);
            break;
      /* case 3:
            p=new StarTower(position);
            break;
        case 4:
            p= new FanTower(position);
            break;
        case 5:
            p=new MagicTower(position);
            break;*/ 
        default:
            return false;
    }
   // ThisLevel::changeMoney(-getTowerDataById(ID).BLDC);
    towers.push_back(p);
    return true;
}

void Tower::deleteTower()
{
    auto sequence = Sequence::create(RemoveSelf::create(),nullptr);
    getMenu()->runAction(sequence);
    auto z = Sequence::create(createCartton(), RemoveSelf::create(), nullptr);
    auto node = Sprite::create();
    node->setPosition(getPosition());
    node->runAction(z);
    auto iter = std::find(towers.begin(), towers.end(), this);
    if (iter != towers.end()) {
        towers.erase(iter);
        delete this;
    }
}

void Tower::attack()
{
    auto p = Resource::getTowerDataById(getID());
    if (currentTime -getLastTime() > p->AS[getLevel()]) {
        setLastTime(currentTime);
        auto place = getPosition();
        auto tower = getTowerBady();
        Vec2 enemy = Vec2(0, 0);//Monster::searchEnemy(place);
        if (enemy.distance(place) <= p->AR) {
            tower->runAction(Sequence::create((setAttackAction(getID(),getLevel()), nullptr)));
            //Bullet::setupBullet(place, enemy, getID());
        }
    }
}

void Tower::levelUp()
{
    auto z = Sequence::create(createCartton(), RemoveSelf::create(), nullptr);
    auto node = Sprite::create();
    node->setPosition(getPosition());
    node->runAction(z);
    getTowerBady()->setSpriteFrame(Resource::getTowerDataById(getID())->action[getLevel() + 1][0]);
    addLevel();
}


const int BottleTower::ID = 1;

BottleTower::BottleTower(const cocos2d::Vec2& p)
{
    level = 1;
    lastTime = 0.0f;  
    position = p;

    bottle = Sprite::createWithSpriteFrameName("ID1_22.PNG");
    auto lamp = Sprite::createWithSpriteFrameName("ID1_11.PNG");
    lamp->addChild(bottle);
    auto _bottleTower = MenuItemSprite::create(lamp, lamp, [this](Ref* pSender) { TowerMenu::create(this); });
    auto bottleTower = Menu::create(_bottleTower, NULL);
    mine = bottleTower;
    bottleTower->setPosition(p);
    Director::getInstance()->getRunningScene()->addChild(bottleTower,50);

    auto z = Sequence::create(createCartton(), RemoveSelf::create(), nullptr);
    auto node = Sprite::create();
    node->setPosition(p);
    node->runAction(z);
    Director::getInstance()->getRunningScene()->addChild(node, 50);
}

void BottleTower::attack()
{
    auto p = Resource::getTowerDataById(ID);
    if (currentTime - lastTime > p->AS[level]) {
        lastTime = currentTime;
        Vec2 enemy = Vec2(0, 0);// Monster::searchEnemy(bottle->getPosition());
        if (enemy.distance(position) <= p->AR) {
            Vec2 direction = enemy - position;
            Vec2 normalizedDirection = direction.getNormalized();
            // 计算旋转角度（弧度）
            float angle = CC_RADIANS_TO_DEGREES(atan2(normalizedDirection.y, normalizedDirection.x)) - bottle->getRotation();
            // 创建旋转动画
            auto rotateBy = RotateBy::create(angle / 360.0f, angle);
            bottle->runAction(Sequence::create(rotateBy, setAttackAction(ID,level), nullptr));
           // Bullet::setupBullet(position, enemy, ID);
        }
    }
}

cocos2d::Vec2 TowerMenu::position;
bool TowerMenu::canUp=false;
Tower* TowerMenu::_tower=nullptr;
const TowerData* TowerMenu::data=nullptr;
int TowerMenu::level=1;
cocos2d::Menu* TowerMenu::menu = nullptr;
cocos2d::Sprite* TowerMenu::up = nullptr;

bool TowerMenu::init(Tower* tower) 
{
    if (!Menu::init()) {
        return false;
    }
    _tower = tower;
    position = _tower->getPosition();
    data = Resource::getTowerDataById(_tower->getID());
    level=_tower->getLevel();

    canUp = true;//data.UPGC[level] < ThisLevel::getMoney();
    Sprite* up = Sprite::createWithSpriteFrameName(Resource::getIcon(data->UPGC[level], canUp));
    TowerMenu::up = up;
    Sprite* destory = Sprite::createWithSpriteFrameName(Resource::getSellPrice(data->PR[level]));
    auto levelUp = MenuItemSprite::create(up, up, [this](Ref* pSender) {
        if (canUp) {
            menu->removeFromParentAndCleanup(true);
            _tower->levelUp();
            /* ThisLevel::changeMoney(-data->UPGC[level]);*/
        }});
    auto remove = MenuItemSprite::create(destory, destory, [this](Ref* pSender) {
        _tower->deleteTower();
        menu->removeFromParentAndCleanup(true);
        /*ThisLevel::changeMoney(data->PR[level]);*/ });

    menu = Menu::create(remove, levelUp, NULL);
    menu->alignItemsVerticallyWithPadding(100);
    menu->setPosition(position);
    auto fadeIn = FadeIn::create(0.4f);
    menu->setOpacity(0);
    menu->runAction(fadeIn);
    Director::getInstance()->getRunningScene()->addChild(menu,100);

    // 注册鼠标移动事件监听器
    auto mouseListener = EventListenerMouse::create();
    mouseListener->onMouseUp = CC_CALLBACK_1(TowerMenu::onMouseUp, this);
#ifdef MOUSE
    mouseListener->onMouseMove = CC_CALLBACK_1(TowerMenu::onMouseMove, this);
    p = Label::create();
    p->setAnchorPoint(Vec2(1, 0));
    p->setPosition(Director::getInstance()->getWinSize().width, 0);
    p->setSystemFontSize(24);
#endif // MOUSE
    _eventDispatcher->addEventListenerWithSceneGraphPriority(mouseListener, menu);

    return true;
}

void TowerMenu::upDate()
{
    if (!menu)
        return;
    if (canUp != false) {//(data->UPGC[level]<ThisLevel::getMenoy))
        up->setSpriteFrame(Resource::getIcon(data->UPGC[level], canUp));
    }
}

void TowerMenu::onMouseUp(Event* event)
{
    EventMouse* e = dynamic_cast<EventMouse*>(event); // 将事件对象转换为鼠标事件对象

    if (e)
    {
        Rect boundingBox = menu->getBoundingBox();
        Vec2 mousePosition = Vec2(e->getCursorX(), e->getCursorY());
        if (boundingBox.containsPoint(mousePosition))
            menu->removeFromParentAndCleanup(true);
    }
}

#ifdef MOUSE
void TowerMenu::onMouseMove(Event* event)
{
    EventMouse* e = dynamic_cast<EventMouse*>(event); // 将事件对象转换为鼠标事件对象

    if (e)
    {
        Vec2 mousePosition = Vec2(e->getCursorX(), e->getCursorY());
        p->setAnchorPoint(Vec2(1, 0));
        p->setPosition(Director::getInstance()->getWinSize().width, 0);
        p->setSystemFontSize(24);
        p->setString(StringUtils::format("Mouse Position: (%.2f, %.2f)", position.x, position.y));
    }
}
#endif // MOUSE
