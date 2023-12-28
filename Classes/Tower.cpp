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

Tower* Tower::buildTower(const int ID, const cocos2d::Vec2& position)
{
    Tower* it=nullptr;
    switch (ID) {
        case 1:
            it = new BottleTower(ID, position);
            break;
        case 3:
            it = new StarTower(ID, position);
            break;
        case 4:
            it = new FanTower(ID, position);
            break;
        case 5:
            it = new MagicTower(ID, position);
            break;
    }
    return it;
}

Tower::Tower(const int ID, const cocos2d::Vec2& p)
{
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
    whole = Sprite::create();
    if (ID != 3)
        whole->addChild(lamp);
    whole->addChild(body);
    whole->setPosition(position);

    Director::getInstance()->getRunningScene()->addChild(whole, 50);
    Effect::create(CARTTON, position);
}

void Tower::levelUp()
{
    if (level < 3) {
        SoundManager::getInstance()->onEffect(7);
        Effect::create(CARTTON, position);
        body->setSpriteFrame(data->action[level + 1][0]);
        level++;
    }
}

Tower::~Tower()
{
    SoundManager::getInstance()->onEffect(6);
    auto sequence = Sequence::create(RemoveSelf::create(), nullptr);
    whole->runAction(sequence);
    Effect::create(CARTTON, position);
}

void BottleTower::attack(const float delat, const Vec2& enemy)
{
    if ((lastTime += delat) > data->AS[level]) {
        lastTime = 0.0f;  
        Vec2 normalizedDirection = (enemy - position).getNormalized();
        // 计算旋转角度（弧度）
        float angle = CC_RADIANS_TO_DEGREES(atan2(normalizedDirection.y, normalizedDirection.x));
        // 创建旋转动画
        auto rotateTo = RotateTo::create(fabs(angle / 360.0f), -angle);
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
    lamp->setSpriteFrame(data->lamp[level + 1]);
    Tower::levelUp();
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
    lamp->setSpriteFrame(data->lamp[level + 1]);
    Tower::levelUp();
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