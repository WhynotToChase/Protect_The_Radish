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

    // ������ײ�����������
    body->setCategoryBitmask(distributeMask());  // �������
    body->setCollisionBitmask(0);  // ��ײ����

    // ������ײ��Ϊ��̬
    body->setDynamic(false);

    // ����ײ����ӵ����ﾫ����
    this->setPhysicsBody(body);

    // ������ײ�ص�����
    auto contactListener = cocos2d::EventListenerPhysicsContact::create();
    contactListener->onContactBegin = CC_CALLBACK_1(Monster::onContactBegin, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);

    // ����ÿ���ƶ���Ŀ��λ��
    float time=0;
    // ��������
    auto animation = createMonsterAnimation();
    
    // �� Animation ת��Ϊ Animate
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

    // �ڶ������ʱ���ûص�����ɾ���Լ�
    auto remove = CallFuncN::create([this](Node* sender) {
        this->removeFromParent();
        });

    // ˳��ִ�������������к�ɾ���Լ��Ķ���
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

    auto animation = cocos2d::Animation::createWithSpriteFrames(frames,0.2f);  // 0.2���л�һ֡
    return animation;
}

float Monster::calculateMoveDuration(const int &distance)
{
    // �����ƶ��ٶȼ����ƶ��ĳ���ʱ�䣬����򵥼����ٶ�Խ�죬ʱ��Խ��
    return distance / moveSpeed;
}



const std::string Monster::getMonsterMoveImage(const int& id, const int& frameIndex)
{
    // ����ID��֡������ȡ���ﶯ��֡��ͼƬ·��
    return cocos2d::StringUtils::format("../Resources/%d_%d.png", id, frameIndex);
}

bool Monster::onContactBegin(cocos2d::PhysicsContact& contact)
{
    auto spriteA = contact.getShapeA()->getBody()->getNode();
    auto spriteB = contact.getShapeB()->getBody()->getNode();

    // �ж���ײ�����������Ƿ�������ĵ���������
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

    // ���� false ��ʾ�жϺ����߼�
    return false;
}