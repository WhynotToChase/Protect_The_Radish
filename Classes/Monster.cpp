#include"Monster.h"
#include<cmath>

using namespace cocos2d;

bool Monster ::init(int id, float speed)
{
    if (!Sprite::initWithFile(getMonsterImage(id)))  // 根据ID获取怪物图片路径
        return false;

    monsterID = id;
    moveSpeed = speed;

    // 设置怪物的初始位置
    this->setPosition(cocos2d::Vec2(500, 500));

    // 移动怪物的动作，使其移动到Vec2(600, 600)
    auto moveAction = cocos2d::MoveTo::create(calculateMoveDuration(), cocos2d::Vec2(600, 600));

    // 使用动画
    auto animation = createMonsterAnimation();
    this->runAction(cocos2d::RepeatForever::create(cocos2d::Animate::create(animation)));

    // 执行移动动作
    this->runAction(moveAction);

    return true;
}

const char* Monster::getMonsterImage(int id)
{
    switch (id)
    {
        case 1:
            return "..../Resources/1-1.PNG";  // 请替换为实际的怪物图片路径
        case 2:
            return "..../Resources/2-1.PNG";
        case 3:
            return "..../Resources/3-1.PNG";
        case 4:
            return "..../Resources/4-1.PNG";
        default:
            return "..../Resources/1-1.PNG";
    }
}

cocos2d::Animation* Monster::createMonsterAnimation()
{
    const int frameCount = 2;
    cocos2d::Vector<cocos2d::SpriteFrame*> frames;

    for (int i = 1; i <= frameCount; ++i)
    {
        auto frame = cocos2d::SpriteFrame::create(getMonsterImage(monsterID, i), cocos2d::Rect(0, 0, 100, 100));
        frames.pushBack(frame);
    }

    auto animation = cocos2d::Animation::createWithSpriteFrames(frames, 0.2f);  // 0.2秒切换一帧
    return animation;
}

float Monster::calculateMoveDuration()
{
    // 根据移动速度计算移动的持续时间，这里简单假设速度越快，时间越短
    return 5.0f / moveSpeed;
}



const char* Monster::getMonsterImage(int id, int frameIndex)
{
    // 根据ID和帧索引获取怪物动画帧的图片路径
    return cocos2d::StringUtils::format("..../Resources/%d-%d.PNG", id, frameIndex).c_str();
}