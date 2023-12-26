#ifndef __MONSTER_H__
#define __MONSTER_H__

#include "Box2D/Box2D.h"
#include "extensions/cocos-ext.h"
#include<vector>
#include "cocos2d.h"

class Monster : public cocos2d::Sprite
{
public:

    int monsterID;

    float moveSpeed;

    b2Body* monsterBody;

    struct MonsterPath {
        int PathX;
        int PathY;
    };
    MonsterPath ThisPath[10][10] = {
        {{1,5},{1,2},{4,2},{4,3},{7,3},{7,2},{10,2},{10,5},{0,0},{0,0} },
        {{1,5},{1,2},{4,2},{4,3},{7,3},{7,2},{10,2},{10,5},{0,0},{0,0} },
        {{1,5},{1,2},{4,2},{4,3},{7,3},{7,2},{10,2},{10,5},{0,0},{0,0} },
        {{1,5},{1,2},{4,2},{4,3},{7,3},{7,2},{10,2},{10,5},{0,0},{0,0} },
        {{1,5},{1,2},{4,2},{4,3},{7,3},{7,2},{10,2},{10,5},{0,0},{0,0} },
        {{1,5},{1,2},{4,2},{4,3},{7,3},{7,2},{10,2},{10,5},{0,0},{0,0} },
        {{1,5},{1,2},{4,2},{4,3},{7,3},{7,2},{10,2},{10,5},{0,0},{0,0} },
        {{1,5},{1,2},{4,2},{4,3},{7,3},{7,2},{10,2},{10,5},{0,0},{0,0} },
        {{1,5},{1,2},{4,2},{4,3},{7,3},{7,2},{10,2},{10,5},{0,0},{0,0} },
        {{1,5},{1,2},{4,2},{4,3},{7,3},{7,2},{10,2},{10,5},{0,0},{0,0} }
    };

    virtual bool init(int id, float speed,const int& level, b2World* world);
   
    
    static Monster* create(int id, float speed, const int& level, b2World* world)
    {
        Monster* monster = new Monster();
        if (monster && monster->init(id, speed,level,world))
        {
            monster->autorelease();
            return monster;
        }
        CC_SAFE_DELETE(monster);
        return nullptr;
    }

private:
    const char* getMonsterImage(int id);
    

    float calculateMoveDuration(const int& distance);
  
    cocos2d::Animation* createMonsterAnimation();
    

    const std::string  getMonsterMoveImage(const int& id, const int& frameIndex);
   
};

#endif // !__MONSTER_H__

