#ifndef __TOWER_H__
#define __TOWER_H__

#include <vector>
#include "cocos2d.h"
#include "Resource.h"
#include <chrono>
#include "Monster.h"
#include "Bullet.h"
#include "SoundManager.h"

#define MOUSE

class Tower 
{
private:

    static SoundManager* music;

    static std::vector<Tower*> towers;

public:

    static float currentTime;

    static cocos2d::Animate* createCartton();

    static cocos2d::Animate* setAttackAction(int ID,int level);

    static void clearup();

    static void upDate();

    static bool buildTower(const int ID,const cocos2d::Vec2&position);

    static void wholeAttack();

    virtual void deleteTower();

    virtual void levelUp();

    virtual void attack();

    static void getCurrentTime();

    virtual const int getID() = 0;
    virtual int getLevel() = 0;
    virtual void addLevel() = 0;
    virtual float getLastTime() = 0;
    virtual void  setLastTime(float) = 0;
    virtual cocos2d::Menu* getMenu() = 0;
    virtual cocos2d::Sprite* getTowerBady() = 0;
    virtual const cocos2d::Vec2& getPosition() = 0;

};


class BottleTower : public Tower
{
private:
    int level;

    cocos2d::Vec2 position;

    cocos2d::Menu* mine;

    cocos2d::Sprite* bottle;

    const static int ID;

    float lastTime;

public:

    virtual const int getID() { return ID; }
    virtual int getLevel() { return level; }
    virtual void addLevel() { level++; }
    virtual float getLastTime() { return lastTime; }
    virtual void  setLastTime(float i) { lastTime=i; }
    virtual cocos2d::Menu* getMenu() { return mine; }
    virtual cocos2d::Sprite* getTowerBady() { return bottle; }
    virtual const cocos2d::Vec2& getPosition() { return position; }

    BottleTower(const cocos2d::Vec2& p);

    virtual void attack()override;
};

class TowerMenu :public cocos2d::Menu
{
private:

    static cocos2d::Vec2 position;

    static bool canUp;

    static Tower* _tower;

    static cocos2d::Sprite* up;

    const static TowerData* data;

    static int level;

    static cocos2d::Menu* menu;

    void onMouseUp(cocos2d::Event* event);
#ifdef MOUSE
    void onMouseMove(cocos2d::Event* event);
    cocos2d::Label* p;
#endif // MOUSE


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
/*class StarTower : public Tower
{
private:
    int level;

    cocos2d::Vec2 position;


public:
    const static ID3 attr;

    StarTower(const cocos2d::Vec2& p, const int i = 1);

    virtual void deleteTower();

    virtual void attack(const float& time);
};

class FanTower : public Tower
{
private:
    int level;

    cocos2d::Vec2 position;


public:
    const static ID4 attr;

    FanTower(const cocos2d::Vec2& p, const int i = 1);

    virtual void deleteTower();

    virtual void attack(const float& time);
};

class MagicTower : public Tower
{
private:
    int level;

    cocos2d::Vec2 position;


public:
    const static ID5 attr;

    MagicTower(const cocos2d::Vec2& p, const int i = 1);

    virtual void deleteTower();

    virtual void attack(const float& time);
};
*/



#endif // !__TOWER_H__

