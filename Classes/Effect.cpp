#include "Effect.h"

using namespace cocos2d;

Resource* Effect::res=nullptr;

bool Effect::init(const Vec2& position,const int ID)
{
    if (!res)
        res = Resource::getInstance();
    if (!Node::init()) {
        // 处理初始化失败的情况
        return false;
    }

    switch (ID) {
        case 0:
            createCartton();
            break;
        case 1:
        case 3:
        case 4:
        case 5:
            bulletEffect(ID);
            break;
        default:
            return false;
    }
    auto animation = Animation::createWithSpriteFrames(frames, 0.1f);
    auto animate = Animate::create(animation);
    auto sequence = Sequence::create(animate, RemoveSelf::create(), nullptr);

    auto sprite = Sprite::create(); // 使用 Sprite 来展示动画
    sprite->runAction(sequence);

    this->addChild(sprite);
    this->setPosition(position);

    Director::getInstance()->getRunningScene()->addChild(this, 50);

    return true;
}

void Effect::createCartton()
{
    frames.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("Items02-hd_24.PNG"));
    frames.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("Items02-hd_208.PNG"));
    frames.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("Items02-hd_175.PNG"));
    frames.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("Items02-hd_89.PNG"));
}

void Effect::bulletEffect(int ID)
{
    for (auto& x : res->getTowerDataById(ID)->effect)
        frames.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName(x));
}