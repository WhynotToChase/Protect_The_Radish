#ifndef __MW_CPP_SYSMENU_H__
#define __MW_CPP_SYSMENU_H__

#include "cocos2d.h"
#include "AppDelegate.h"
#include "ui/CocosGUI.h"
#include "Resource.h"

class SysMenu : public cocos2d::Layer
{
    MONITOR_H();
public:
  

    virtual bool init();

    static cocos2d::Scene* scene();

    void OnOption(Ref* pSender);

    void OnProduct(Ref* pSender);

    void OnStart(Ref* pSender);

    void OnExit(Ref* pSender);

    void StartGame(Ref* pSender,int num);

    CREATE_FUNC(SysMenu);
    
};

#endif/*__MW_CPP_SYSMENU_H__*/
