#pragma once
#ifndef __MW_CPP_SYSMENU_H__
#define __MW_CPP_SYSMENU_H__

#include "cocos2d.h"
#include "AppDelegate.h"
#include "ui/CocosGUI.h"
#include"SysMenu.h"
#include<string>


class SelectMenu : public cocos2d::Layer
{
private:
    Sprite* middleSprite;

    int Level;

    int IsChange;
public:

    virtual bool init();


    static cocos2d::Scene* scene();

    std::string SelectLevel(const int& level);

    void moveSprites(Ref* pSender);


    void OnOption(Ref* pSender);


    void OnStart(Ref* pSender);


    CREATE_FUNC(SelectMenu);
};

#endif/*__MW_CPP_SYSMENU_H__*/
