#ifndef __SELECTMENU_H__
#define __SELECTMENU_H__

#include "cocos2d.h"
#include"SysMenu.h"
#include "SelectMenu.h"
#include "Resource.h"
#include"SettingMenu.h"
#include"SoundManager.h"
#include"MousePosition.h"
#include<string>


class SelectMenu : public cocos2d::Layer
{
private:
    MousePosition* this_mouse;

    cocos2d::Menu* The_middleSprite_menu;

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

#endif/*__SELECTMENU_H__*/
