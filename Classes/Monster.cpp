#include"Monster.h"
#include<cmath>

using namespace cocos2d;

Resource* Monster::res = nullptr;

int Monster::distributeMask()
{
    static int orginMask = 1;
    static int currentMask = 0;
    currentMask = orginMask;
    orginMask << 1;
    if (orginMask == 0)
        orginMask = 1;
    return currentMask;
}

bool Monster::init(int id, float speed, const int& level)
{
    if (!Sprite::initWithFile(getMonsterImage(id)))
        return false;
    if (!res)
        res = Resource::getInstance();
    monsterID = id;
    moveSpeed = speed * 1.5;
    blood = 1000;

    this->setPosition(ThisPath[level][0].x * 160.0f + 80.0f, ThisPath[level][0].y * 135.0f + 67.5f);
    this->setScale(160 / this->getContentSize().width, 135 / this->getContentSize().height);

    auto body = cocos2d::PhysicsBody::createBox(this->getContentSize());

    // 设置碰撞体的类别和掩码
    body->setCategoryBitmask(distributeMask());  // 类别掩码
    body->setCollisionBitmask(0);  // 碰撞掩码

    // 设置碰撞体为静态
    body->setDynamic(false);

    // 将碰撞体添加到怪物精灵中
    this->setPhysicsBody(body);

    // 设置碰撞回调函数
    auto contactListener = cocos2d::EventListenerPhysicsContact::create();
    contactListener->onContactBegin = CC_CALLBACK_1(Monster::onContactBegin, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);

    // 创建每个移动的目标位置
    float time=0;
    // 创建动画
    auto animation = createMonsterAnimation();
    
    // 将 Animation 转换为 Animate
    auto animate = Animate::create(animation);
    float distance = 0.0f;
    Vector<FiniteTimeAction*>action;
    for (int i = 1; i < 15; i++) {
        if (!ThisPath[level][i].x&&!ThisPath[level][i].y) {
            break;
        }
        else {
            distance = ThisPath[level][i].x * 160.0f + ThisPath[level][i].y * 135.0f;
            time = distance / moveSpeed;
            auto moveBy = MoveBy::create(time, Vec2(ThisPath[level][i].x * 160.0f, ThisPath[level][i].y * 135.0f));
            animate->setDuration(time);
            
            action.pushBack(Spawn::createWithTwoActions(moveBy, animate->clone()));
        }
    }

    auto se = Sequence::create(action);

    // 在动作完成时调用回调函数删除自己
    auto remove = CallFuncN::create([this](Node* sender) {
        this->removeFromParent();
        });

    // 顺序执行整个动作序列和删除自己的动作
    auto finalAction = Sequence::create(se, remove, nullptr);

    this->setTag(0);
    this->runAction(finalAction);
    return true;
}


const char* Monster::getMonsterImage(int id)
{
    switch (id)
    {
        case 1:
            return "../Resources/1_1.png"; 
        case 2:
            return "../Resources/2_1.png";
        case 3:
            return "../Resources/3_1.png";
        case 4:
            return "../Resources/4_1.png";
        default:
            return "../Resources/1_1.png";
    }
}

cocos2d::Animation* Monster::createMonsterAnimation()
{
    const int frameCount = 2;
    cocos2d::Vector<cocos2d::SpriteFrame*> frames;

    for (int i = 1; i <= frameCount; ++i)
    {
        auto frame = cocos2d::SpriteFrame::create(getMonsterMoveImage(monsterID, i), cocos2d::Rect(0, 0, 100, 100));
        frames.pushBack(frame);
    }

    auto animation = cocos2d::Animation::createWithSpriteFrames(frames,0.2f);  // 0.2秒切换一帧
    return animation;
}

float Monster::calculateMoveDuration(const int &distance)
{
    // 根据移动速度计算移动的持续时间，这里简单假设速度越快，时间越短
    return distance / moveSpeed;
}



const std::string Monster::getMonsterMoveImage(const int& id, const int& frameIndex)
{
    // 根据ID和帧索引获取怪物动画帧的图片路径
    return cocos2d::StringUtils::format("../Resources/%d_%d.png", id, frameIndex);
}

bool Monster::onContactBegin(cocos2d::PhysicsContact& contact)
{
    auto spriteA = contact.getShapeA()->getBody()->getNode();
    auto spriteB = contact.getShapeB()->getBody()->getNode();

    // 判断碰撞的两个物体是否是你关心的物体类型
    if (spriteA && spriteB) {
        if (spriteA->getTag() == 0)
            blood -= spriteB->getTag();
        else
            blood -= spriteA->getTag();

        if (blood == 0) {
            this->stopAllActions();
            auto se = Sequence::create(FadeOut::create(0.2f), RemoveSelf::create(), nullptr);
            this->runAction(se);
        }
        return true;
    }

    // 返回 false 表示中断后续逻辑
    return false;
}