#ifndef __MONSTER_H__
#define __MONSTER_H__

#include<vector>
#include "cocos2d.h"
#include "Resource.h"

class Monster : public cocos2d::Sprite
{
public:

    static Resource* res;

    int monsterID;

    float moveSpeed;

     Coor ThisPath[10][16] = {
         //第一关位移
        {{1,5},{0,-3},{3,0},{0,1},{3,0},{0,-1},{3,0},{0,3},{0,0},{0,0},{0,0} ,{0,0},{0,0},{0,0} ,{0,0} ,{10,5}},
        //第二关位移
        {{4,5},{5,0},{0,-2},{-7,0},{0,-2},{5,0},{0,0},{0,0},{0,0},{0,0} ,{0,0},{0,0},{0,0},{0,0} ,{0,0} ,{7,1}},
        //第三关位移
        {{1,4},{0,-3},{4,0},{0,2},{2,0},{0,2},{1,0},{0,-1},{2,0},{0,0},{0,0} ,{0,0},{0,0},{0,0} ,{0,0} ,{10,4}},
        //第四关位移
        {{0,4},{2,0},{0,-3},{2,0},{0,2},{3,0},{0,-2},{3,0},{0,4},{0,0},{0,0} ,{0,0},{0,0},{0,0} ,{0,0} ,{10,5}},
        //第五关位移
        {{10,1},{0,4},{-3,0},{0,-1},{-3,0},{0,-1},{-3,0},{0,-1},{1,0},{0,-2}, {5,0},{1,0},{0,0},{0,0} ,{0,0} ,{7,1}},
        //第六关位移
        {{0,5},{5,0},{0,-4},{6,0},{0,0},{0,0},{0,0},{0,0}, {0,0},{0,0},{0,0},{0,0},{0,0},{0,0} ,{0,0},{11,1}},
        //第七关位移
        {{1,5},{0,-4},{3,0},{0,2},{4,0},{0,-2},{2,0},{0,4},{-6,0},{0,0},{0,0},{0,0},{0,0},{0,0} ,{0,0},{4,5}},
        //第八关位移
        {{10,4},{0,-1},{-5,0},{0,2},{-5,0},{0,-2},{2,0},{0,-2},{2,0},{0,1},{4,0},{0,0},{0,0},{0,0} ,{0,0},{8,2}},
        //第九关位移
        {{1,1},{0,4},{2,0},{0,-1},{1,0},{0,-1},{1,0},{0,-1},{2,0},{0,1},{1,0},{0,1},{1,0},{0,1},{2,0},{11,5}},
        //第十关位移
        {{1,1},{0,2},{2,0},{0,2},{6,0},{0,-3},{-4,0},{0,-1},{4,0},{0,0},{0,0},{0,0} ,{0,0},{0,0},{0,0} ,{9,1}}
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

