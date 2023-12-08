#ifndef __MW_CPP_SYSMENU_H__
#define __MW_CPP_SYSMENU_H__

#include "cocos2d.h"
#include "AppDelegate.h"


class SysMenu : public cocos2d::Layer
{
private:
    Sprite* _ship;
    Size winSize;
public:

    virtual bool init();


    static cocos2d::Scene* scene();


    void onAbout(Ref* pSender);

    void onSettings(Ref* pSender);

    void onButtonEffect();

    void flareEffect(Ref* pSender);


    virtual void update(float dt);


    void onNewGame();

    CREATE_FUNC(SysMenu);
};

#endif/*__MW_CPP_SYSMENU_H__*/
