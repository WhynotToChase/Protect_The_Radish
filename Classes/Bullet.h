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

    // ���RocketBullet���ض�����Ϊ����������������Լ��ķ���������

    CREATE_FUNC(RocketBullet);

    // ��д�����update����
    virtual void update(float delta) override;
};

class LaserBullet : public Bullet {
public:
    virtual bool init();

    // ���LaserBullet���ض�����Ϊ����������������Լ��ķ���������

    CREATE_FUNC(LaserBullet);

    // ��д�����update����
    virtual void update(float delta) override;
};


#endif // !__BULLET_H__
