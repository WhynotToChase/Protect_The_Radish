#include"Monster.h"
#include<cmath>
#include "ThisLevel.h"

using namespace cocos2d;

Resource* Monster::res = nullptr;
SoundManager* Monster::music = nullptr;

int Monster::distributeMask()
{
    static int orginMask = 1;
    static int currentMask = 0;
    currentMask = orginMask;
    orginMask= orginMask << 1;
    if (orginMask == 0)
        orginMask = 1;
    return currentMask;
}

bool Monster::init(int id ,const int& level)
{
    if (!Sprite::initWithFile(getMonsterImage(id)))
        return false;
    if (!res) {
        res = Resource::getInstance();
        music = SoundManager::getInstance();
    }

    monsterID = id;
    moveSpeed = res->monsterData[id].speed;
    blood = res->monsterData[id].blood;

    this->setPosition(res->levelPath[level][0].x * 160.0f + 80.0f, res->levelPath[level][0].y * 135.0f + 105.0f);
    this->setScale(1.5f);

    auto body = cocos2d::PhysicsBody::createBox(this->getContentSize());

    // 设置碰撞体的类别和掩码
    body->setCategoryBitmask(0xffffffff);  // 类别掩码
    body->setCollisionBitmask(0);
    body->setContactTestBitmask(0);

    // 设置碰撞体为静态
    body->setDynamic(true);

    // 将碰撞体添加到怪物精灵中
    this->setPhysicsBody(body);

    // 设置碰撞回调函数
    auto contactListener = cocos2d::EventListenerPhysicsContact::create();
    contactListener->onContactBegin = CC_CALLBACK_1(Monster::onContactBegin, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);
  
    float distance = 0.0f;
    Vector<FiniteTimeAction*>action;
    Coor p;
    float time = 0.0f;
    float delta = 0.0f;
    for (int i = 1;i< res->levelPath[level].size();i++) {
        p = res->levelPath[level][i];
        distance = p.x * 160.0f + p.y * 135.0f;
        delta = fabs(distance) / moveSpeed;
        time += delta;
        action.pushBack(MoveBy::create(delta, Vec2(p.x * 160.0f, p.y * 135.0f)));
    }
    auto se = Sequence::create(action);

    // 创建动画
    Vector<SpriteFrame*> frames;
    for (int i = 1; i <= 2; ++i)
    {
        auto frame = SpriteFrame::create(getMonsterMoveImage(monsterID, i),Rect(0,0,125,100));
        frames.pushBack(frame);
    }
    auto animation = Animation::createWithSpriteFrames(frames, 0.5f, time); // 0.2秒切换一帧
    auto animate = Animate::create(animation);
    animate->setDuration(time);

    auto sp = Spawn::createWithTwoActions(animate, se);

    // 在动作完成时调用回调函数删除自己
    auto remove = CallFuncN::create([this](Node* sender) {
        this->removeFromParent();
        });

    // 顺序执行整个动作序列和删除自己的动作
    auto finalAction = Sequence::create(sp, remove, nullptr);

    this->setTag(0);
    this->runAction(finalAction);
    Director::getInstance()->getRunningScene()->addChild(this);
    music->onEffect(8);
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
            Effect::create(this->getPosition());
            auto p = ThisLevel::getInstance();
            p->changeMoney(50);
            auto it = find(p->monsters.begin(), p->monsters.end(), this);
            p->monsters.erase(it);
            auto se = Sequence::create(FadeOut::create(0.2f), RemoveSelf::create(), nullptr);
            this->runAction(se);
        }
        return true;
    }

    // 返回 false 表示中断后续逻辑
    return false;
}