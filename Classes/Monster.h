#ifndef __MONSTER_H__
#define __MONSTER_H__

#include "Box2D/Box2D.h"
#include "extensions/cocos-ext.h"
#include<vector>
#include "cocos2d.h"

class Search
{
public:
    static std::vector<cocos2d::Sprite*> monsters;
    
    static cocos2d::Vec2 searchEnemy(cocos2d::Vec2&, const int ID);

    static std::vector < std::vector<cocos2d::Vec2>> currentEnemy;

    static void cleanUp();

    static void upDate();

    static int range[20];
};

class Monster : public cocos2d::Sprite
{
public:

    int monsterID;

    float moveSpeed;

    b2Body* monsterBody;

    struct pair {
        int x;
        int  y;
    };

     pair ThisPath[10][10] = {
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

