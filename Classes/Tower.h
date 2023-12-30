#ifndef __TOWER_H__
#define __TOWER_H__



#include "cocos2d.h"
#include <vector>
#include "Resource.h"
#include "Bullet.h"
#include "Effect.h"

class Tower
{
public:

    static Bullet* bul;

    static Resource* res;

    static void setUp();

    int ID;

    virtual void attack(const float delat, const cocos2d::Vec2& enemy){}

    const TowerData* data;

    float lastTime;

    int level;

    cocos2d::Vec2 position;

    cocos2d::Sprite* whole;

    cocos2d::Sprite* lamp;

    cocos2d::Sprite* body;

    ~Tower();

    virtual void levelUp();

    Tower(const int ID, const cocos2d::Vec2& p);
    
    static Tower* buildTower(const int ID, const cocos2d::Vec2& position);

};

class BottleTower : public Tower
{
public:
    BottleTower(const int ID, const cocos2d::Vec2& p):Tower(ID,p){}

    virtual void attack(const float delat, const cocos2d::Vec2& enemy);
};


class StarTower : public Tower
{
public:
    StarTower(const int ID, const cocos2d::Vec2& p) :Tower(ID, p) {}

    virtual void attack(const float delat, const cocos2d::Vec2& enemy);

    virtual void levelUp()override;
};

class FanTower : public Tower
{
public:
    FanTower(const int ID, const cocos2d::Vec2& p) :Tower(ID, p) {}

    virtual void attack(const float delat, const cocos2d::Vec2& enemy);

    virtual void levelUp()override;
};

class MagicTower : public Tower
{
public:
    MagicTower(const int ID, const cocos2d::Vec2& p) :Tower(ID, p) {}

    virtual void attack(const float delat, const cocos2d::Vec2& enemy);
};

#endif // !__TOWER_H__

