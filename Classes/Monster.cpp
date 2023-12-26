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

    // 创建每个移动的目标位置
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
    // 创建动画
    auto animation = createMonsterAnimation();
    
    // 将 Animation 转换为 Animate
    auto animate = Animate::create(animation);
    animate->setDuration(AllTime);

    // 使用 RepeatForever 包装 Animate
    auto repeatAnimation = RepeatForever::create(animate);

    // 同时运行动画和按照顺序移动到目标位置
    std::vector<Spawn*>spawnAction;
    for (int j = 0; j < targetPosition.size(); j++) {
        if (j == 0) {
            spawnAction.push_back(Spawn::create(repeatAnimation, targetPosition[j], nullptr));
        }
        else {
            spawnAction.push_back(Spawn::create(repeatAnimation->clone(), targetPosition[j], nullptr));
        }
    }

    // 顺序执行n个移动和动画的动作
    Vector<FiniteTimeAction*> sequenceActions;
    sequenceActions.pushBack(spawnAction[0]); // 添加第一个动作
    for (int j = 1; j < spawnAction.size(); j++) {
        sequenceActions.pushBack(DelayTime::create(calculateMoveDuration(5.0f))); // 添加延迟
        sequenceActions.pushBack(spawnAction[j]); // 添加后续的动作
    }

    auto sequenceAction = Sequence::create(sequenceActions);

    // 在动作完成时调用回调函数删除自己
    auto removeSelfCallback = CallFuncN::create([this](Node* sender) {
        this->removeFromParent();
        });

    // 顺序执行整个动作序列和删除自己的动作
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