#pragma once
#ifndef __MW_CPP_SYSMENU_H__
#define __MW_CPP_SYSMENU_H__

#include "cocos2d.h"
#include"SysMenu.h"
#include "SelectMenu.h"
#include "Resource.h"
#include"SettingMenu.h"
#include"SoundManager.h"
#include<string>


class SelectMenu : public cocos2d::Layer
{
private:
    Sprite* middleSprite;

    int Level;

    int IsChange;

    SoundManager* this_music;
public:

    virtual bool init();


    static cocos2d::Scene* scene();

    std::string SelectLevel(const int& level);

    void ThisSet();

    void moveSprites(Ref* pSender);


    CREATE_FUNC(SelectMenu);
};

#endif/*__MW_CPP_SYSMENU_H__*/
