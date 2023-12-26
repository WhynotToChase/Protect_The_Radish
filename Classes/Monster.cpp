#include"Monster.h"
#include<cmath>

using namespace cocos2d;

bool Monster::init(int id, float speed, const int& level, b2World* world)
{
    if (!Sprite::initWithFile(getMonsterImage(id)))
        return false;

    monsterID = id;
    moveSpeed = speed * 1.5;

    this->setPosition(cocos2d::Vec2(ThisPath[level][0].PathX * 160 + 80, ThisPath[level][0].PathY * 135 + 67));
    this->setScale(160 / this->getContentSize().width, 135 / this->getContentSize().height);

    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(this->getPositionX() , this->getPositionY() );

    monsterBody = world->CreateBody(&bodyDef);

    b2PolygonShape dynamicBox;
    dynamicBox.SetAsBox(this->getContentSize().width / 2 , this->getContentSize().height / 2 );

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &dynamicBox;
    fixtureDef.density = 1.0f;
    fixtureDef.friction = 0.3f;
    monsterBody->CreateFixture(&fixtureDef);

    // ����ÿ���ƶ���Ŀ��λ��
    std::vector<MoveTo*>targetPosition;
    int i;
    float AllTime=0;
    for (i = 1; i < 10; i++) {
        if (ThisPath[level][i].PathX * ThisPath[level][i].PathY == 0) {
            break;
        }
        else {
            targetPosition.push_back(MoveTo::create(calculateMoveDuration(fabs(ThisPath[level][i].PathX -
                ThisPath[level][i - 1].PathX) * 160 + fabs(ThisPath[level][i].PathY - ThisPath[level][i - 1].PathY) * 135)
                , Vec2(ThisPath[level][i].PathX * 160 + 80, ThisPath[level][i].PathY * 135 + 67)));
            AllTime = AllTime + calculateMoveDuration(fabs(ThisPath[level][i].PathX -
                ThisPath[level][i - 1].PathX) * 160 + fabs(ThisPath[level][i].PathY - ThisPath[level][i - 1].PathY) * 135);
        }
    }
    // ��������
    auto animation = createMonsterAnimation();
    
    // �� Animation ת��Ϊ Animate
    auto animate = Animate::create(animation);
    animate->setDuration(AllTime);

    // ʹ�� RepeatForever ��װ Animate
    auto repeatAnimation = RepeatForever::create(animate);

    // ͬʱ���ж����Ͱ���˳���ƶ���Ŀ��λ��
    std::vector<Spawn*>spawnAction;
    for (int j = 0; j < targetPosition.size(); j++) {
        if (j == 0) {
            spawnAction.push_back(Spawn::create(repeatAnimation, targetPosition[j], nullptr));
        }
        else {
            spawnAction.push_back(Spawn::create(repeatAnimation->clone(), targetPosition[j], nullptr));
        }
    }

    // ˳��ִ��n���ƶ��Ͷ����Ķ���
    Vector<FiniteTimeAction*> sequenceActions;
    sequenceActions.pushBack(spawnAction[0]); // ��ӵ�һ������
    for (int j = 1; j < spawnAction.size(); j++) {
        sequenceActions.pushBack(DelayTime::create(calculateMoveDuration(5.0f))); // ����ӳ�
        sequenceActions.pushBack(spawnAction[j]); // ��Ӻ����Ķ���
    }

    auto sequenceAction = Sequence::create(sequenceActions);

    // �ڶ������ʱ���ûص�����ɾ���Լ�
    auto removeSelfCallback = CallFuncN::create([this](Node* sender) {
        this->removeFromParent();
        });

    // ˳��ִ�������������к�ɾ���Լ��Ķ���
    auto finalAction = Sequence::create(sequenceAction, removeSelfCallback, nullptr);

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