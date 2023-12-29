#ifndef __BULLET_H__
#define __BULLET_H__

#include "cocos2d.h"
#include "Resource.h"
#include "SoundManager.h"

class Bullet
{
private:

    static Bullet* instance;

    Resource* res;

public:

    Bullet();
    
    static Bullet* getInstance();

    void setupBullet(cocos2d::Vec2 startPosition, const cocos2d::Vec2& targetPosition,const int ID,const int level, const float AR);

    cocos2d::Vec2 accFinal(cocos2d::Vec2& startPosition, const cocos2d::Vec2& targetPosition,const float AR, const bool i=false);

    cocos2d::Vec2 accFinal(cocos2d::Vec2& startPosition,const float angle,const float AR);
};

class TheBullet :public cocos2d::Sprite
{
public:

    int ID;

    virtual bool init(const cocos2d::Vec2& start, const cocos2d::Vec2& target, const int ID, const int level);

   static TheBullet* create(const cocos2d::Vec2& startPosition, const cocos2d::Vec2& targetPosition, const int ID, const int level) {
       TheBullet* pRet = new(std::nothrow) TheBullet(); if (pRet && pRet->init(startPosition, targetPosition, ID, level)) {
            pRet->autorelease(); return pRet;
        }
        else {
            delete pRet; pRet = nullptr; return nullptr;
        }
    };

    virtual bool onContactBegin(cocos2d::PhysicsContact& contact);
};

class FanBullet : public cocos2d::Sprite 
{

public:

    int ID;

    virtual bool init(const cocos2d::Vec2& start, const cocos2d::Vec2& target, const int ID, const int level);

    static FanBullet* create(const cocos2d::Vec2& startPosition, const cocos2d::Vec2& targetPosition, const int ID, const int level) {
        FanBullet* pRet = new(std::nothrow) FanBullet(); if (pRet && pRet->init(startPosition, targetPosition, ID, level)) {
            pRet->autorelease(); return pRet;
        }
        else {
            delete pRet; pRet = nullptr; return nullptr;
        }
    };

    virtual bool onContactBegin(cocos2d::PhysicsContact& contact);
};

class MagicBullet : public cocos2d::Sprite 
{

public:
    int ID;

    virtual bool init(const cocos2d::Vec2& start, const cocos2d::Vec2& target, const int ID, const int level);

    static MagicBullet* create(const cocos2d::Vec2& startPosition, const cocos2d::Vec2& targetPosition, const int ID, const int level) {
        MagicBullet* pRet = new(std::nothrow) MagicBullet(); if (pRet && pRet->init(startPosition, targetPosition, ID, level)) {
            pRet->autorelease(); return pRet;
        }
        else {
            delete pRet; pRet = nullptr; return nullptr;
        }
    };

    virtual bool onContactBegin(cocos2d::PhysicsContact& contact);

};

#endif // !__BULLET_H__
