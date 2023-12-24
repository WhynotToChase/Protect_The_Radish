#include "Effect.h"

using namespace cocos2d;

bool Effect::init(int num, const Vec2& position)
{
    if (!Node::init()) {
        // 处理初始化失败的情况
        return false;
    }

    switch (num) {
        case CARTTON:
            createCartton();
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