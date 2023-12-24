#ifndef __EFFECT_H__
#define __EFFECT_H__

#include"cocos2d.h"

#define CARTTON 0

class Effect : public cocos2d::Node
{
private:

    cocos2d::Vector<cocos2d::SpriteFrame*> frames;

    void createCartton();

public:
    virtual bool init(int num, const cocos2d::Vec2& position);

    static Effect* create(int num, const cocos2d::Vec2& position) {
        Effect* pRet = new(std::nothrow) Effect();
        if (pRet && pRet->init(num, position)) {
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

