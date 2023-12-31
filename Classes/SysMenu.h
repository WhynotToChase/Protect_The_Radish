#ifndef __SYSMENU_H__
#define __SYSMENU_H__

#include "cocos2d.h"
#include <string>
#include "SoundManager.h"
#include "SettingMenu.h"
#include"SelectMenu.h"
#include "Tower.h"

class SysMenu : public cocos2d::Layer
{
private: 

    Resource* res;

    SoundManager* music;

    bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event, cocos2d::Sprite* menu); 

    void monitor(cocos2d::Sprite* menu);

    void removeTouchListener();


public:

    virtual bool init();

    static cocos2d::Scene* scene();

    void OnOption(Ref* pSender);

    void OnProduct(Ref* pSender);

    void OnStart(Ref* pSender);

    void OnExit(Ref* pSender);

    void StartGame(Ref* pSender,int num);

    void FrameReturn(Ref* pSender, std::string name);

    CREATE_FUNC(SysMenu);
    
};

#endif/*__SYSMENU_H__*/
