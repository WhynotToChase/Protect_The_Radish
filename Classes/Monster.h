#ifndef __MONSTER_H__
#define __MONSTER_H__

#include<vector>
#include "cocos2d.h"
#include "Resource.h"

class Monster : public cocos2d::Sprite
{
public:

    int monsterID;

    float moveSpeed;

     Coor ThisPath[10][10] = {
        {{1,5},{0,-3},{3,0},{0,1},{3,0},{0,-1},{3,0},{0,3},{0,0},{10,5}},
         {{1,5},{0,-3},{3,0},{0,1},{3,0},{0,-1},{3,0},{0,3},{0,0},{0,0}},
          {{1,5},{0,-3},{3,0},{0,1},{3,0},{0,-1},{3,0},{0,3},{0,0},{0,0}},
           {{1,5},{0,-3},{3,0},{0,1},{3,0},{0,-1},{3,0},{0,3},{0,0},{0,0}},
            {{1,5},{0,-3},{3,0},{0,1},{3,0},{0,-1},{3,0},{0,3},{0,0},{0,0}},
             {{1,5},{0,-3},{3,0},{0,1},{3,0},{0,-1},{3,0},{0,3},{0,0},{0,0}},
              {{1,5},{0,-3},{3,0},{0,1},{3,0},{0,-1},{3,0},{0,3},{0,0},{0,0}},
               {{1,5},{0,-3},{3,0},{0,1},{3,0},{0,-1},{3,0},{0,3},{0,0},{0,0}},
               {{1,5},{0,-3},{3,0},{0,1},{3,0},{0,-1},{3,0},{0,3},{0,0},{0,0}},
               {{1,5},{0,-3},{3,0},{0,1},{3,0},{0,-1},{3,0},{0,3},{0,0},{0,0}}
    };

    virtual bool init(int id, float speed,const int& level);
   
 
    
    static Monster* create(int id, float speed, const int& level)
    {
        Monster* monster = new Monster();
        if (monster && monster->init(id, speed,level))
        {
            monster->autorelease();
            return monster;
        }
        CC_SAFE_DELETE(monster);
        return nullptr;
    }

private: 

    static int distributeMask();

    int blood;
    
    const char* getMonsterImage(int id);
    
    float calculateMoveDuration(const int& distance);
  
    cocos2d::Animation* createMonsterAnimation();

    const std::string  getMonsterMoveImage(const int& id, const int& frameIndex);
   
    bool onContactBegin(cocos2d::PhysicsContact& contact);
};

#endif // !__MONSTER_H__

