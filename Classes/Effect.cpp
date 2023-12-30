#include "Effect.h"

using namespace cocos2d;

bool Effect::init(const Vec2& position)
{
    if (!Node::init()) {
        // �����ʼ��ʧ�ܵ����
        return false;
    }

    createCartton();

    auto animation = Animation::createWithSpriteFrames(frames, 0.1f);
    auto animate = Animate::create(animation);
    auto sequence = Sequence::create(animate, RemoveSelf::create(), nullptr);

    auto sprite = Sprite::create(); // ʹ�� Sprite ��չʾ����
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