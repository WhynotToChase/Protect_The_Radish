#ifndef __MW_CPP_SYSMENU_H__
#define __MW_CPP_SYSMENU_H__

#include "cocos2d.h"
#include "AppDelegate.h"
#include "ui/CocosGUI.h"
#include "Resource.h"
#include <string>

class SysMenu : public cocos2d::Layer
{
private: 
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

    void SysMenu::FrameReturn(Ref* pSender, std::string name);

    CREATE_FUNC(SysMenu);
    
};

#endif/*__MW_CPP_SYSMENU_H__*/
