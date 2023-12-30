#ifndef __VICTORY_SCENE_H__
#define __VICTORY_SCENE_H__

#include "cocos2d.h"

class VictoryScene : public cocos2d::Scene
{
public:

    virtual bool init() override;

    void onReturnButtonClick(cocos2d::Ref* sender);

    void menuCloseCallback(cocos2d::Ref* pSender);

    CREATE_FUNC(VictoryScene);

private:
    void returnToMainScene();
};

#endif // __VICTORY_SCENE_H__