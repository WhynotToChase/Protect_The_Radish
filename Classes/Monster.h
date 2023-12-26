#ifndef __MONSTER_H__
#define __MONSTER_H__

#include "cocos2d.h"

#include "cocos2d.h"

class Monster : public cocos2d::Sprite
{
public:

    int monsterID;
    float moveSpeed;

    virtual bool init(int id, float speed);
   

    static Monster* create(int id, float speed)
    {
        Monster* monster = new Monster();
        if (monster && monster->init(id, speed))
        {
            monster->autorelease();
            return monster;
        }
        CC_SAFE_DELETE(monster);
        return nullptr;
    }

private:
    const char* getMonsterImage(int id);
    

    float calculateMoveDuration();
  
    cocos2d::Animation* createMonsterAnimation();
    

    const char* getMonsterImage(int id, int frameIndex);
   
};

#endif // !__MONSTER_H__

