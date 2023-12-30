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

    auto body = cocos2d::PhysicsBody::createBox(Size(60,50));

    // ������ײ�����������
    body->setCategoryBitmask(2);  // �������
    body->setCollisionBitmask(distributeMask());
    body->setContactTestBitmask(1);


    body->setDynamic(true);

    // ����ײ����ӵ����ﾫ����
    this->setPhysicsBody(body);

    // ������ײ�ص�����
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

    // ��������
    Vector<SpriteFrame*> frames;
    for (int i = 1; i <= 2; ++i)
    {
        auto frame = SpriteFrame::create(getMonsterMoveImage(monsterID, i),Rect(0,0,125,100));
        frames.pushBack(frame);
    }
    auto animation = Animation::createWithSpriteFrames(frames, 0.5f, time); // 0.2���л�һ֡
    auto animate = Animate::create(animation);
    animate->setDuration(time);

    auto sp = Spawn::createWithTwoActions(animate, se);

    // �ڶ������ʱ���ûص�����ɾ���Լ�
    auto remove = CallFuncN::create([this](Node* sender) {
        this->removeFromParent();
        });

    // ˳��ִ�������������к�ɾ���Լ��Ķ���
    auto finalAction = Sequence::create(sp, remove, nullptr);

    this->setTag(0);
    this->runAction(finalAction);
    Director::getInstance()->getRunningScene()->addChild(this,40);
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
    // ����ID��֡������ȡ���ﶯ��֡��ͼƬ·��
    return cocos2d::StringUtils::format("../Resources/%d_%d.png", id, frameIndex);
}

bool Monster::onContactBegin(cocos2d::PhysicsContact& contact)
{
    auto bodyA = contact.getShapeA()->getBody();
    auto bodyB = contact.getShapeB()->getBody();
    if (bodyA->getCollisionBitmask() & bodyB->getCollisionBitmask()) {
        auto spriteB = dynamic_cast<Monster*>(contact.getShapeB()->getBody()->getNode());
        if (bodyA->getName() == "4")
            bodyA->setCollisionBitmask(bodyA->getCollisionBitmask() - bodyB->getCollisionBitmask());
        else
            bodyA->setCollisionBitmask(0);
        spriteB->blood -= bodyA->getTag();
        if (spriteB->blood <= 0) {
            Effect::create(spriteB->getPosition());
            auto p = ThisLevel::getInstance();
            p->changeMoney(50);
            auto it = find(p->monsters.begin(), p->monsters.end(), spriteB);
            p->monsters.erase(it);
            spriteB->removeFromParentAndCleanup(true);
        }
    }
    return false;
}