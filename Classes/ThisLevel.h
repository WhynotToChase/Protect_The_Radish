#ifndef __THISLEVEL_H__
#define __THISLEVEL_H__


#include "cocos2d.h"
#include "SelectMenu.h"
#include"SettingMenu.h"
#include"SoundManager.h"
#include "Resource.h"
#include "Tower.h"
#include "Monster.h"
#include"Radish.h"
#include <vector>
#include <map>
#include "VictoryScene.h"

struct towerNature
{
    bool hasSearched;
    Tower* these;
    int RG;
};

class ThisLevel :public cocos2d::Scene 
{
private:
    static  ThisLevel* instance;

    float lastTime;
    float currentTime;
    int currentWave;
    int maxWave;
    int monsterCount;
    std::vector<MonsterPair> p;

    Radish* radish;

    bool isEnd = true;
    float time = 0;

    void settle(const int hp);

    Coor transform(const cocos2d::Vec2& point){return { int(point.x) / 160, int(point.y) / 135 };}

    cocos2d::Vec2 transform(const Coor point){return { point.x * 160.0f + 80.0f,point.y * 135.0f + 67.5f };}

    std::map<Coor, towerNature> towers;

    SoundManager* this_music;

    Resource* res;

    Coor lastPosition;

    Coor mouseP;

    cocos2d::Sprite* pausemenu=nullptr;
    cocos2d::Menu* pauseMenuButtons=nullptr;

    cocos2d::Sprite* moneyNumber=nullptr;

    void pauseMenu();
    
    int money=0;
    
public:

    int this_level = 0;

    std::vector<Monster*> monsters;

    bool changeMoney(const int num, const bool i = false);

    static ThisLevel* getInstance();

    void onMouseMove(cocos2d::Event* event);

    cocos2d::MenuItemSprite* buttonItem=nullptr;

    cocos2d::Menu* selectMenu=nullptr;

    cocos2d::Menu* menu=nullptr;
    bool menuEnabled=true;

    virtual bool init(const int& level);

    void update(float delta);

    void createTower();

    void createTowerMenu(Tower* it);
    int cost = 0;
    int price = 0;
    Tower* it;

    void ToNull();

    std::string SelectLevel(const int& level);


    static ThisLevel* create(const int&level) {
        ThisLevel* pRet = new(std::nothrow) ThisLevel(); if (pRet && pRet->init(level)) {
            pRet->autorelease(); return pRet;
        }
        else {
            delete pRet; pRet = nullptr; return nullptr;
        }
    }
};

#endif/*__SELECTMENU_H__*/