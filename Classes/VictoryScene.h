#ifndef __VICTORY_SCENE_H__
#define __VICTORY_SCENE_H__

#include "cocos2d.h"
#include "SoundManager.h"

class VictoryScene : public cocos2d::Scene
{
public:

    virtual bool init(const int level, const int result);

    void onReturnButtonClick(cocos2d::Ref* sender);

    static VictoryScene* create(const int level, const int result) {
        VictoryScene* pRet = new(std::nothrow) VictoryScene(); if (pRet && pRet->init( level, result)) {
            pRet->autorelease(); return pRet;
        }
        else {
            delete pRet; pRet = nullptr; return nullptr;
        }
    };

private:

    SoundManager* music;

    void returnToMainScene();
};

#endif // __VICTORY_SCENE_H__