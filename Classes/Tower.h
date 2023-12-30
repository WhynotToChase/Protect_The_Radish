#ifndef __TOWER_H__
#define __TOWER_H__



#include "cocos2d.h"
#include <vector>
#include "Resource.h"
#include "Bullet.h"
#include "Effect.h"

class Tower: public cocos2d::Sprite
{
public:

    static Bullet* bul;

    static Resource* res;

    static void setUp();

    int ID;

    virtual void attack(const float delat, const cocos2d::Vec2& enemy) = 0;

    const TowerData* data;

    float lastTime;

    int level;

    cocos2d::Vec2 position;

    cocos2d::Sprite* lamp;

    cocos2d::Sprite* body;
 
    void destoryTower();

    virtual void levelUp();

    virtual bool init(const int ID, const cocos2d::Vec2& p);

};

class BottleTower : public Tower
{
public:

    virtual void attack(const float delat, const cocos2d::Vec2& enemy);

    static BottleTower* create(const int ID, const cocos2d::Vec2& p) {
        BottleTower* pRet = new(std::nothrow) BottleTower(); if (pRet && pRet->init(ID, p)) {
            pRet->autorelease(); return pRet;
        }
        else {
            delete pRet; pRet = nullptr; return nullptr;
        }
    };
};


class StarTower : public Tower
{
public:

    virtual void levelUp()override;

    virtual void attack(const float delat, const cocos2d::Vec2& enemy);

    static StarTower* create(const int ID, const cocos2d::Vec2& p) {
        StarTower* pRet = new(std::nothrow) StarTower(); if (pRet && pRet->init(ID, p)) {
            pRet->autorelease(); return pRet;
        }
        else {
            delete pRet; pRet = nullptr; return nullptr;
        }
    };
};

class FanTower : public Tower
{
public:

    virtual void attack(const float delat, const cocos2d::Vec2& enemy);

    virtual void levelUp()override;

    static FanTower* create(const int ID, const cocos2d::Vec2& p) {
        FanTower* pRet = new(std::nothrow) FanTower(); if (pRet && pRet->init(ID, p)) {
            pRet->autorelease(); return pRet;
        }
        else {
            delete pRet; pRet = nullptr; return nullptr;
        }
    };
};

class MagicTower : public Tower
{
public:

    virtual void attack(const float delat, const cocos2d::Vec2& enemy);

    static MagicTower* create(const int ID, const cocos2d::Vec2& p) {
        MagicTower* pRet = new(std::nothrow) MagicTower(); if (pRet && pRet->init(ID, p)) {
            pRet->autorelease(); return pRet;
        }
        else {
            delete pRet; pRet = nullptr; return nullptr;
        }
    };
};


#endif // !__TOWER_H__

