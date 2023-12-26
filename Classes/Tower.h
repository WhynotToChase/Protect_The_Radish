#ifndef __TOWER_H__
#define __TOWER_H__

#include <set>
#include <chrono>
#include <vector>
#include <string>
#include "cocos2d.h"
#include "Resource.h"
#include "Monster.h"
#include "Bullet.h"
#include "SoundManager.h"
#include "Effect.h"
#include "ThisLevel.h"

#define MOUSE

class Tower 
{
private:

    static std::vector<Tower*> towers;

public:

    static void setAttackAction(const int ID,const int level,cocos2d::Sprite* tower,cocos2d::Sequence* action=nullptr);

    static void clearup();

    static bool hasBuilt(const cocos2d::Vec2& position);

    static void upDate(const float delat);

    static bool buildTower(const int ID,const cocos2d::Vec2&position);

    virtual void deleteTower();

    virtual void levelUp();

    virtual void attack(const float& delat);

    virtual const int getID() = 0;
    virtual int getLevel() = 0;
    virtual void addLevel() = 0;
    virtual float& getLastTime() = 0;
    virtual void  setLastTime() = 0;
    virtual cocos2d::Sprite* getWhole() = 0;
    virtual cocos2d::Sprite* getTowerBady() = 0;
    virtual cocos2d::Sprite* getTowerLamp() { return nullptr; }
    virtual const cocos2d::Vec2& getPosition() = 0;

};


class BottleTower : public Tower
{
private:
    int level;

    cocos2d::Vec2 position;

    cocos2d::Sprite* whole;

    cocos2d::Sprite* body;

    const static int ID;

    float lastTime;

public:

    virtual const int getID() { return 1; }
    virtual int getLevel() { return level; }
    virtual void addLevel() { level++; }
    virtual float& getLastTime() { return lastTime; }
    virtual void  setLastTime() { lastTime=0; }
    virtual cocos2d::Sprite* getWhole() { return whole; }
    virtual cocos2d::Sprite* getTowerBady() { return body; }
    virtual const cocos2d::Vec2& getPosition() { return position; }

    BottleTower(const cocos2d::Vec2& p);

    virtual void attack(const float& delat)override;
};


class StarTower : public Tower
{
private:
    int level;

    cocos2d::Vec2 position;

    cocos2d::Sprite* whole;

    cocos2d::Sprite* body;

    cocos2d::Sprite* lamp;

    const static int ID;

    float lastTime;

public:

    virtual const int getID() { return 3; }
    virtual int getLevel() { return level; }
    virtual void addLevel() { level++; }
    virtual float& getLastTime() { return lastTime; }
    virtual void  setLastTime() { lastTime = 0.0f; }
    virtual cocos2d::Sprite* getWhole() { return whole; }
    virtual cocos2d::Sprite* getTowerBady() { return body; }
    virtual cocos2d::Sprite* getTowerLamp() override{ return lamp; }
    virtual const cocos2d::Vec2& getPosition() { return position; }

    StarTower(const cocos2d::Vec2& p);
};

class FanTower : public Tower
{
private:
    int level;

    cocos2d::Vec2 position;

    cocos2d::Sprite* whole;

    cocos2d::Sprite* body;

    cocos2d::Sprite* lamp;

    const static int ID;

    float lastTime;

public:

    virtual const int getID() { return 4; }
    virtual int getLevel() { return level; }
    virtual void addLevel() { level++; }
    virtual float& getLastTime() { return lastTime; }
    virtual void setLastTime() { lastTime = 0.0f; }
    virtual cocos2d::Sprite* getWhole() { return whole; }
    virtual cocos2d::Sprite* getTowerBady() { return body; }
    virtual cocos2d::Sprite* getTowerLamp() override { return lamp; }
    virtual const cocos2d::Vec2& getPosition() { return position; }

   FanTower(const cocos2d::Vec2& p);
};

class MagicTower : public Tower
{
private:
    int level;

    cocos2d::Vec2 position;

    cocos2d::Sprite* whole;

    cocos2d::Sprite* body;

    const static int ID;

    float lastTime;

public:

    virtual const int getID() { return 5; }
    virtual int getLevel() { return level; }
    virtual void addLevel() { level++; }
    virtual float& getLastTime() { return lastTime; }
    virtual void  setLastTime() { lastTime = 0.0f; }
    virtual cocos2d::Sprite* getWhole() { return whole; }
    virtual cocos2d::Sprite* getTowerBady() { return body; }
    virtual const cocos2d::Vec2& getPosition() { return position; }

    MagicTower(const cocos2d::Vec2& p);
};


class TowerMenu :public cocos2d::Menu
{
private:

    static cocos2d::Rect range;

    static bool canUp;

    static Tower* _tower;

    static cocos2d::Sprite* up;

    static cocos2d::MenuItem* levelup;

    static int level;

    static cocos2d::Menu* menu;

    void onMouseUp(cocos2d::Event* event);

public:

    static void upDate();

    virtual bool init(Tower* tower);

    static TowerMenu* create(Tower* tower) {
        TowerMenu* pRet = new(std::nothrow) TowerMenu(); if (pRet && pRet->init(tower)) {
            pRet->autorelease(); return pRet;
        }
        else {
            delete pRet; pRet = nullptr; return nullptr;
        }
    };
};



#endif // !__TOWER_H__

