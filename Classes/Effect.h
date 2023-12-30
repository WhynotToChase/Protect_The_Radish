#ifndef __EFFECT_H__
#define __EFFECT_H__

#include"cocos2d.h"
#include "Resource.h"

class Effect : public cocos2d::Node
{
private:

    cocos2d::Vector<cocos2d::SpriteFrame*> frames;

    void createCartton();


    void bulletEffect(int ID);

    static Resource* res;

public:

    virtual bool init(const cocos2d::Vec2& position,const int ID=0);

    static Effect* create(const cocos2d::Vec2& position,const int ID=0) {
        Effect* pRet = new(std::nothrow) Effect();
        if (pRet && pRet->init(position,ID)) {
            pRet->autorelease();
            return pRet;
        }
        else {
            delete pRet;
            return nullptr;
        }
    }
};

#endif // !__Effect_H__

