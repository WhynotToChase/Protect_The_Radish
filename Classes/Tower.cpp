#include "Tower.h"
using namespace cocos2d;

#define SIZE 1.8f

Bullet* Tower::bul=nullptr;
Resource* Tower::res = nullptr;

void Tower::setUp()
{
    bul = Bullet::getInstance();
    res = Resource::getInstance();
}

bool Tower::init(const int ID, const cocos2d::Vec2& p)
{
    if (!Sprite::init())
        return false;
    Tower::ID = ID;
    level = 1;
    lastTime = -1.0f;
    position = p;
    data = res->getTowerDataById(ID);

    body = Sprite::createWithSpriteFrameName(data->action[level][0]);
    body->setScale(SIZE);
    if (ID != 5) {
        lamp = Sprite::createWithSpriteFrameName(data->lamp[level]);
        lamp->setScale(SIZE);
    }
    else
        lamp = nullptr;
    if (ID != 5)
        this->addChild(lamp);
    this->addChild(body);
    this->setPosition(position);

    Director::getInstance()->getRunningScene()->addChild(this, 50);
    Effect::create(position);
    return true;
}

void Tower::levelUp()
{
    if (level < 3) {
        this->stopAllActions();
        SoundManager::getInstance()->onEffect(7);
        Effect::create(position);
        body->setSpriteFrame(data->action[level + 1][0]);
        level++;
    }
}

void Tower::destoryTower()
{
    this->stopAllActions();
    SoundManager::getInstance()->onEffect(6);
    this->removeFromParentAndCleanup(true);
    Effect::create(position);
}

void BottleTower::attack(const float delat, const Vec2& enemy)
{
    if ((lastTime += delat) > data->AS[level]) {
        lastTime = 0.0f;  
        Vec2 normalizedDirection = (enemy - position).getNormalized();
        // 计算旋转角度（弧度）
        float angle = CC_RADIANS_TO_DEGREES(atan2(normalizedDirection.y, normalizedDirection.x));
        // 创建旋转动画
        auto rotateTo = RotateTo::create(fabs(angle / 540.0f), -angle);
        Vector<SpriteFrame*> frames;
        for (auto& z : data->action[level])
            frames.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName(z));
        frames.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName(data->action[level][0]));
        Animation* p = Animation::createWithSpriteFrames(frames, 0.2f);
        Animate* q = Animate::create(p);

        auto action = Sequence::create(rotateTo, q, nullptr);
        body->runAction(action);
        bul->setupBullet(position, enemy, ID, level, data->AR);
    }
}

void StarTower::levelUp()
{ 
    Tower::levelUp();
    lamp->setSpriteFrame(data->lamp[level]);
}

void StarTower::attack(const float delat, const Vec2& enemy)
{
    if ((lastTime += delat) > data->AS[level]) {
        lastTime = 0.0f;
        auto circle = RotateBy::create(data->actionDelay, 360.0f);
        body->runAction(circle);
        bul->setupBullet(position, enemy, ID, level, data->AR);
    }
}

void FanTower::attack(const float delat, const Vec2& enemy)
{
    if ((lastTime += delat) > data->AS[level]) {
        lastTime = 0.0f;
        auto circle = RotateBy::create(data->actionDelay, 360.0f);
        body->runAction(circle);
        bul->setupBullet(position, enemy, ID, level, data->AR);
    }
}

void FanTower::levelUp()
{  
    Tower::levelUp();
    lamp->setSpriteFrame(data->lamp[level]);
}

void MagicTower::attack(const float delat, const Vec2& enemy)
{
    if ((lastTime += delat) > data->AS[level]) {
        lastTime = 0.0f;
        Vector<SpriteFrame*> frames;
        for (auto& z : data->action[level])
            frames.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName(z));
        frames.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName(data->action[level][0]));
        Animation* p = Animation::createWithSpriteFrames(frames, 0.2f);
        Animate* q = Animate::create(p);
        body->runAction(q);
        bul->setupBullet(position, enemy, ID, level, data->AR);
    }
}