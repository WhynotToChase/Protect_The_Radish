#ifndef __THISLEVEL_H__
#define __THISLEVEL_H__


#include "cocos2d.h"
#include"SysMenu.h"
#include "SelectMenu.h"
#include<vector>
#include"SettingMenu.h"
#include"SoundManager.h"
#include"MousePosition.h"

class ThisLevel :public cocos2d::Scene {
private:
    SoundManager* this_music;

    MousePosition* this_mouse;

    cocos2d::Menu* p;

    int position_x;//上一个的格子x位置

    int position_y;//上一个的格子y位置

    float mouseY;

    float mouseX;
public:
    int money;

    int this_level;

    void onMouseMove(cocos2d::Event* event);

    cocos2d::MenuItemSprite* buttonItem;

    cocos2d::Menu* menu;

    cocos2d::Menu* leftmenu;
    cocos2d::Menu* rightmenu;
    cocos2d::Menu* topmenu;
    cocos2d::Menu* bottommenu;

    virtual bool init(const int& level);

    void update(float delta);

    void createTower();

    void ToNull();

    bool  find();

    std::string SelectLevel(const int& level);


    static ThisLevel* create(const int&level) {
        ThisLevel* pRet = new(std::nothrow) ThisLevel(); if (pRet && pRet->init(level)) {
            pRet->autorelease(); return pRet;
        }
        else {
            delete pRet; pRet = nullptr; return nullptr;
        }
    };
};

#endif/*__SELECTMENU_H__*/