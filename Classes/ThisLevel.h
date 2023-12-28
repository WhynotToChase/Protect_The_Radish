#ifndef __THISLEVEL_H__
#define __THISLEVEL_H__


#include "cocos2d.h"
#include "SelectMenu.h"
#include"SettingMenu.h"
#include"SoundManager.h"
#include "Resource.h"
#include "Tower.h"
#include <vector>

class ThisLevel :public cocos2d::Scene {
private:

    SoundManager* this_music;

    Resource* res;

    Coor lastPosition;

    Coor mouseP;

    cocos2d::Sprite* pausemenu;
    cocos2d::Menu* pauseMenuButtons;

    cocos2d::Sprite* moneyNumber;

    void pauseMenu();
    
    int money=0;
    
    Tower* towers[12][8] = { 0 }; 
    
    int this_level;

    bool changeMoney(const int num, const bool i = false);

public:

    Coor transform(cocos2d::Vec2& point) { return { int(point.x) / 160, int(point.y) / 135 }; }

    cocos2d::Vec2 transform(Coor point) { return { point.x * 160.0f + 80.0f,point.y * 135.0f + 67.5f }; }

    void onMouseMove(cocos2d::Event* event);

    cocos2d::MenuItemSprite* buttonItem;

    cocos2d::Menu* selectMenu=nullptr;

    cocos2d::Menu* menu;
    bool menuEnabled=true;

    //void onMouseUp(Event* event);

    virtual bool init(const int& level);

    void update(float delta);

    void createTower();

    void createTowerMenu(Tower* it);
    bool canUp = true;
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