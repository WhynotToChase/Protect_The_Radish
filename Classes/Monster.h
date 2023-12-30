#ifndef __MONSTER_H__
#define __MONSTER_H__

#include<vector>
#include "cocos2d.h"
#include "Resource.h"
#include "Effect.h"
#include "SoundManager.h"

class Monster : public cocos2d::Sprite
{
public:

    static SoundManager* music;

    static Resource* res;

    int monsterID;

    float moveSpeed;

    virtual bool init(int id,const int& level);
    
    static Monster* create(int id, const int& level)
    {
        Monster* monster = new Monster();
        if (monster && monster->init(id,level))
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
    
    static const char* getMonsterImage(int id);

    static const std::string  getMonsterMoveImage(const int& id, const int& frameIndex);
   
    bool onContactBegin(cocos2d::PhysicsContact& contact);
};

#endif // !__MONSTER_H__

