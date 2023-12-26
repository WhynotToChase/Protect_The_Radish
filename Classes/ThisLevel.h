#ifndef __THISLEVEL_H__
#define __THISLEVEL_H__


#include "cocos2d.h"
#include"SysMenu.h"
#include "SelectMenu.h"
//#include<vector>
#include"SettingMenu.h"
#include"SoundManager.h"
#include"MousePosition.h"
#include "Resource.h"

class ThisLevel :public cocos2d::Scene {
private:
    SoundManager* this_music;

    MousePosition* this_mouse;

    cocos2d::Sprite* moneyColumn;

    cocos2d::Menu* p;

    int position_x;//��һ���ĸ���xλ��

    int position_y;//��һ���ĸ���yλ��

    float mouseY;

    float mouseX;
public:
    static int money;

    static bool changeMoney(const int num);

    static bool setMoney(const int num);

    bool  changeMoneyColumn(const int money);

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