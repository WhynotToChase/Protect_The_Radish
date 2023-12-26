#include"Monster.h"
#include<cmath>

using namespace cocos2d;

bool Monster ::init(int id, float speed)
{
    if (!Sprite::initWithFile(getMonsterImage(id)))  // ����ID��ȡ����ͼƬ·��
        return false;

    monsterID = id;
    moveSpeed = speed;

    // ���ù���ĳ�ʼλ��
    this->setPosition(cocos2d::Vec2(500, 500));

    // �ƶ�����Ķ�����ʹ���ƶ���Vec2(600, 600)
    auto moveAction = cocos2d::MoveTo::create(calculateMoveDuration(), cocos2d::Vec2(600, 600));

    // ʹ�ö���
    auto animation = createMonsterAnimation();
    this->runAction(cocos2d::RepeatForever::create(cocos2d::Animate::create(animation)));

    // ִ���ƶ�����
    this->runAction(moveAction);

    return true;
}

const char* Monster::getMonsterImage(int id)
{
    switch (id)
    {
        case 1:
            return "..../Resources/1-1.PNG";  // ���滻Ϊʵ�ʵĹ���ͼƬ·��
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

    auto animation = cocos2d::Animation::createWithSpriteFrames(frames, 0.2f);  // 0.2���л�һ֡
    return animation;
}

float Monster::calculateMoveDuration()
{
    // �����ƶ��ٶȼ����ƶ��ĳ���ʱ�䣬����򵥼����ٶ�Խ�죬ʱ��Խ��
    return 5.0f / moveSpeed;
}



const char* Monster::getMonsterImage(int id, int frameIndex)
{
    // ����ID��֡������ȡ���ﶯ��֡��ͼƬ·��
    return cocos2d::StringUtils::format("..../Resources/%d-%d.PNG", id, frameIndex).c_str();
}