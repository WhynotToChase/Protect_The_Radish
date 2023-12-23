#ifndef __THISLEVEL_H__
#define __THISLEVEL_H__


#include "cocos2d.h"
#include"SysMenu.h"
#include "SelectMenu.h"
#include"SettingMenu.h"
#include"SoundManager.h"
#include"MousePosition.h"

class ThisLevel :public cocos2d::Scene {
private:
    SoundManager* this_music;

    MousePosition* this_mouse;
public:

    virtual bool init(const int& level);

    void update(float delta);

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