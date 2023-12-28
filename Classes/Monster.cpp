#include"Monster.h"
#include<cmath>

using namespace cocos2d;

int Search::range[20] = { 1,-11,-12,-13,-1,11,12,13,2,-24,-2,24,-10,-23,-25,-14,10,23,25,-14 };

std::vector<Sprite*> Search::monsters;

cocos2d::Vec2 Search::searchEnemy(cocos2d::Vec2&p,const int ID)
{
    int point = p.x / 160 * 12 + p.y / 135;
    int max = ID == 4 ? 20 : 12;
    for (int i = 0; i < max;i++) {
        if (currentEnemy[point + range[i]].size() != 0)
            return currentEnemy[point + range[i]][0];
    }
    return Vec2(0, 0);
}

void Search::upDate()
{
    currentEnemy.clear();
    currentEnemy.resize(96);
    Vec2 p;
    for (auto it : monsters) {
        p = it->getPosition();
        currentEnemy[p.x / 160 * 12 + p.y / 135].push_back(p);
    }
}

std::vector < std::vector<Vec2>> Search::currentEnemy = std::vector < std::vector<Vec2>>(12 * 8, { NULL });

void Search::cleanUp()
{
    monsters.clear();
    currentEnemy.clear();
    currentEnemy.resize(96);
}

bool Monster::init(int id, float speed, const int& level, b2World* world)
{
    if (!Sprite::initWithFile(getMonsterImage(id)))
        return false;

    monsterID = id;
    moveSpeed = speed * 1.5;

    this->setPosition(ThisPath[level][0].x * 160.0f + 80.0f, ThisPath[level][0].y * 135.0f + 67.5f);
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
    float time=0;
    // ��������
    auto animation = createMonsterAnimation();
    
    // �� Animation ת��Ϊ Animate
    auto animate = Animate::create(animation);
    float distance = 0.0f;
    Vector<FiniteTimeAction*>action;
    for (int i = 1; i < 9; i++) {
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
        auto it = std::find(Search::monsters.begin(), Search::monsters.end(),this);
        Search::monsters.erase(it);
        this->removeFromParent();
        });

    // ˳��ִ�������������к�ɾ���Լ��Ķ���
    auto finalAction = Sequence::create(se, remove, nullptr);

    this->runAction(finalAction);
    Search::monsters.push_back(this);
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