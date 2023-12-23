#include "Tower.h"

using namespace cocos2d;

float Tower::currentTime = 0.0f;
std::map<Vec2, Tower*> Tower::towers = std::map<Vec2, Tower*>();
Animate* Tower::cartoon = Tower:: createCartton();

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

Animate** Tower::setAttackAction(int ID)
{
    Animate* q[4];
    Animation* p;
    q[0] = nullptr;
    Vector<SpriteFrame*> frames;
    auto& x = getTowerDataById(ID).action;
    for (int i = 1; i < 4; i++) {
        for (int j = 0; j < 3; j++) {
            frames.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName(x[i][j]));
        }
        frames.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName(x[i][0]));
        p = Animation::createWithSpriteFrames(frames, 0.1f);
        q[i] =Animate::create(p);
        frames.clear();
    }
    return q;
}

void Tower::clearup()
{
    currentTime = 0.0f;
    for (auto& p : towers) {
        delete p.second;
    }
}

// 获取当前时间戳的函数
float Tower::getCurrentTime()
{
    currentTime = std::chrono::duration_cast<std::chrono::milliseconds>(
        std::chrono::system_clock::now().time_since_epoch()
    ).count() / 1000.0f;
}

void Tower::wholeAttack()
{
    getCurrentTime();
    for (auto& tower : towers) {
        tower.second->attack();
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
    towers.insert(std::make_pair(position, p));
    return true;
}

float BottleTower::lastTime = 0;
const int BottleTower::ID = 1;
Animate** BottleTower::attackAction = Tower::setAttackAction(BottleTower::ID);

BottleTower::BottleTower(const cocos2d::Vec2& p)
{
    bottle = Sprite::createWithSpriteFrameName("ID1_22.PNG");
    auto lamp = Sprite::createWithSpriteFrameName("ID1_11.PNG");
    lamp->addChild(bottle);
    auto _bottleTower = MenuItemSprite::create(lamp, lamp, [this](Ref* pSender) { TowerMenu::create(this); });
    auto bottleTower = Menu::create(_bottleTower, NULL);
    bottleTower->runAction(cartoon);
    mine = bottleTower;
    position = p;
    Director::getInstance()->getRunningScene()->addChild(bottleTower,50);
}

void BottleTower::deleteTower()
{
    auto dead = CallFunc::create([=]() {
        // 回调函数中执行销毁精灵的操作
        mine->removeFromParentAndCleanup(true);
        });
    auto sequence = Sequence::create(cartoon, dead);
    mine->runAction(sequence);
}

void BottleTower::levelUp()
{
    CallFunc* change;
    if (level == 1)
        change = CallFunc::create([=]() {
        bottle->setSpriteFrame("ID1_15.PNG"); });
    else if (level == 2)
        change = CallFunc::create([=]() {
        bottle->setSpriteFrame("ID1_5.PNG"); });
    else
        return;

    auto sequence = Sequence::create(cartoon, change);
    bottle->runAction(sequence);
    level++;
}

void BottleTower::attack()
{
    auto p = getTowerDataById(ID).AS[level];
    if (currentTime - lastTime > p) {
        lastTime = currentTime;
        Vec2 enemy = Monster::searchEnemy(bottle->getPosition());
        if(Vec2::distance(enemy,position);
        bottle->runAction(Sequence::create(attackAction[level],nullptr));
    }
}
