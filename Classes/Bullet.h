#ifndef __BULLET_H__
#define __BULLET_H__

#include "cocos2d.h"

class Bullet : public cocos2d::Sprite {
public:
    virtual bool init();

    static void setupBullet(const cocos2d::Vec2& startPosition, const cocos2d::Vec2& targetPosition,const int ID);

    virtual void update(float delta);

    CREATE_FUNC(Bullet);

protected:
    float speed;
    cocos2d::Vec2 target;
};

class RocketBullet : public Bullet {
public:
    virtual bool init();

    // 如果RocketBullet有特定的行为，可以在这里添加自己的方法和属性

    CREATE_FUNC(RocketBullet);

    // 重写基类的update方法
    virtual void update(float delta) override;
};

class LaserBullet : public Bullet {
public:
    virtual bool init();

    // 如果LaserBullet有特定的行为，可以在这里添加自己的方法和属性

    CREATE_FUNC(LaserBullet);

    // 重写基类的update方法
    virtual void update(float delta) override;
};


#endif // !__BULLET_H__
