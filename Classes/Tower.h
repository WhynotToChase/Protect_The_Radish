#ifndef __TOWER_H__
#define __TOWER_H__

#include <map>
#include "cocos2d.h"
#include "Resource.h"
#include <chrono>
#include "Monster.h"

class Tower 
{
private:

    static std::map<cocos2d::Vec2,Tower*>towers;

public:

    static float currentTime;

    static cocos2d::Animate* cartoon;

    static cocos2d::Animate* createCartton();

    static cocos2d::Animate** setAttackAction(int ID);

    void clearup();

    bool buildTower(const int ID,const cocos2d::Vec2&position);

    virtual void deleteTower()=0;

    void wholeAttack();

    virtual void levelUp() = 0;

    virtual void attack()=0;

    float getCurrentTime();

};

class TowerMenu
{
private:

    static bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event, cocos2d::Menu* menu);

    static void monitor(cocos2d::Menu* menu);

    static void removeTouchListener();

public:

    static void create(Tower* tower);
  
};


class BottleTower : public Tower
{
private:
    int level;

    cocos2d::Vec2 position;

    cocos2d::Menu* mine;

    cocos2d::Sprite* bottle;

    static cocos2d::Animate** attackAction;

public:

    static float lastTime;

    const static int ID;

    BottleTower(const cocos2d::Vec2& p);

    virtual void deleteTower();

    virtual void levelUp();

    virtual void attack();
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

