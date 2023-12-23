#ifndef __BULLET_H__
#define __BULLET_H__

#include "cocos2d.h"

class Bullet : public cocos2d::Sprite {
public:
    virtual bool init();

    void setupBullet(const cocos2d::Vec2& startPosition, const cocos2d::Vec2& targetPosition);

    virtual void update(float delta);

    static Bullet* create();

    CREATE_FUNC(TowerBullet);

protected:
    float speed;
    cocos2d::Vec2 target;
};

class RocketBullet : public Bullet {
public:
    virtual bool init();

    // ���RocketBullet���ض�����Ϊ����������������Լ��ķ���������

    static RocketBullet* create();

    CREATE_FUNC(RocketBullet);

    // ��д�����update����
    virtual void update(float delta) override;
};

class LaserBullet : public Bullet {
public:
    virtual bool init();

    // ���LaserBullet���ض�����Ϊ����������������Լ��ķ���������

    static LaserBullet* create();

    CREATE_FUNC(LaserBullet);

    // ��д�����update����
    virtual void update(float delta) override;
};


#endif // !__BULLET_H__
