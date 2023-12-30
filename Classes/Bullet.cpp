
#include "Bullet.h"
#include <cmath>

#define SPEED 320.0f
#define SIZE 1.6f

using namespace cocos2d;

Bullet* Bullet::instance = nullptr;

Resource* Bullet::res = nullptr;
Resource* TheBullet::res = nullptr;
Resource* FanBullet::res = nullptr;
Resource* MagicBullet::res = nullptr;
int TheBullet::ID = 1;
int FanBullet::ID = 4;
int MagicBullet::ID = 5;



Bullet* Bullet::getInstance()
{
	if (instance == nullptr)
		instance = new Bullet;
	return instance;
}

int Bullet::distributeMask()
{
	static int orginMask = 1;
	static int currentMask = 0;
	currentMask = orginMask;
	orginMask = orginMask << 1;
	if (orginMask == 0)
		orginMask = 1;
	return currentMask;
}

void Bullet::setupBullet(Vec2 start, const Vec2& target, const int ID,const int level,const float AR)
{
	if (!res)
		res = Resource::getInstance();
	Vec2 final;
	switch (ID) {
		case 1:
			final = accFinal(start, target, AR,1);
			TheBullet::create(start, final, ID, level);
			break;
		case 4:
			final = accFinal(start, target, AR, 1);
			FanBullet::create(start, final, ID, level);
			break;
		case 3:
			for (float i = 0.0f; i <= 2 * M_PI; i += M_PI_4) {
				final = accFinal(start, i, AR);
				TheBullet::create(start, final, ID, 1);
			}
			break;
		case 5:
			start.y += 40;
			MagicBullet::create(start, target, ID, level);
			break;
		default:
			break;
	}
}

Vec2 Bullet::accFinal(Vec2& start, const Vec2& target, const float AR,const bool i)
{
	float angle = atan2(target.y - start.y , target.x - start.x);
	Vec2 final;
	final.x = start.x + AR * cos(angle);
	final.y = start.y + AR * sin(angle);
	if (i) {
		start.x += 50 * cos(angle);
		start.y += 50 * sin(angle);
	}
	return final;
}

Vec2 Bullet::accFinal( Vec2& start, const float angle, const float AR)
{
	Vec2 final;
	final.x = start.x + AR * cos(angle);
	final.y = start.y + AR * sin(angle);
	return final;
}

bool TheBullet::init(const Vec2& start, const Vec2 & final, const int ID, const int level)
{ 
	if (!res)
		res = Resource::getInstance();

	auto data = res->getTowerDataById(ID);
	SoundManager::getInstance()->onEffect(ID);
	if (!Sprite::initWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(data->bullet[level][0]))) {
		return false;
	}

	Vector<SpriteFrame*> frames;
	for (auto& x : data->bullet[level])
		frames.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName(x));
	Animation* animation;
	if (ID == 1)
		animation = Animation::createWithSpriteFrames(frames, data->bulletDelay);
	else
		animation = Animation::createWithSpriteFrames(frames, data->AR / SPEED / data->bulletDelay);
	Animate* animate = Animate::create(animation);
	animate->setDuration(data->AR / SPEED);
	auto move = MoveTo::create(data->AR / SPEED, final);
	auto act = Spawn::createWithTwoActions(animate, move);

	auto fadeOut = FadeOut::create(0.1f);
	auto sequence = Sequence::create(act, fadeOut, RemoveSelf::create(), nullptr);
	this->runAction(sequence);

	auto& size = SpriteFrameCache::getInstance()->getSpriteFrameByName(data->bullet[level][0])->getOriginalSize();

	auto bulletBody = PhysicsBody::createCircle(size.height * SIZE / 2);
	bulletBody->setDynamic(true);
	bulletBody->setCategoryBitmask(1);
	bulletBody->setCollisionBitmask(0xffffffff);
	bulletBody->setContactTestBitmask(2);
	this->setPhysicsBody(bulletBody);
	bulletBody->setTag(data->ATK[level]);
	bulletBody->setName("1");

	this->setScale(SIZE);
	this->setRotation(-CC_RADIANS_TO_DEGREES(atan2(final.y - start.y, final.x - start.x)));
	this->setPosition(start);
	Director::getInstance()->getRunningScene()->addChild(this, 55);


	auto contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = CC_CALLBACK_1(TheBullet::onContactBegin, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener, this);

	return true;
}

bool TheBullet::onContactBegin(PhysicsContact& contact)
{
	auto bodyA=contact.getShapeA()->getBody();
	auto bodyB = contact.getShapeB()->getBody();
	if (bodyA->getCollisionBitmask() & bodyB->getCollisionBitmask()) {
		bodyA->getNode()->runAction(RemoveSelf::create());
		Effect::create(bodyA->getNode()->getPosition(), ID);
	}
	return false;
}

bool FanBullet::init(const Vec2& start, const Vec2 & final, const int ID, const int level)
{
	if (!res)
		res = Resource::getInstance();

	SoundManager::getInstance()->onEffect(ID);
	auto data = res->getTowerDataById(ID);

	if (!Sprite::initWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(data->bullet[level][0])))
		return false;

	this->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(data->bullet[level][0]));
	auto loop = RotateBy::create(data->AR / SPEED, 360.0f* data->AR / SPEED / data->bulletDelay);
	auto move = MoveTo::create(data->AR / SPEED, final);
	auto act = Spawn::create(loop, move, nullptr);

	auto fadeOut = FadeOut::create(0.1f);
	auto sequence = Sequence::create(act, fadeOut, RemoveSelf::create(), nullptr);
	this->runAction(sequence);

	auto& size = SpriteFrameCache::getInstance()->getSpriteFrameByName(data->bullet[level][0])->getOriginalSize();


	auto bulletBody = PhysicsBody::createCircle(size.height/2);
	bulletBody->setCategoryBitmask(1);
	bulletBody->setCollisionBitmask(0xffffffff);
	bulletBody->setContactTestBitmask(2);
	this->setPhysicsBody(bulletBody);
	bulletBody->setDynamic(true);
	bulletBody->setTag(data->ATK[level]);
	bulletBody->setName("4");

	auto contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = CC_CALLBACK_1(FanBullet::onContactBegin, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener, this);

	this->setScale(SIZE);
	this->setPosition(start);
	Director::getInstance()->getRunningScene()->addChild(this, 55);
	return true;
}

bool FanBullet::onContactBegin(PhysicsContact& contact)
{
	auto bodyA = contact.getShapeA()->getBody();
	auto bodyB = contact.getShapeB()->getBody();

	if (bodyA->getCollisionBitmask() & bodyB->getCollisionBitmask()) {
		Effect::create(bodyA->getNode()->getPosition(), ID);
	}
	return false;
}

bool MagicBullet::init(const Vec2& start, const Vec2 & final, const int ID, const int level)
{
	if (!res)
		res = Resource::getInstance();

	SoundManager::getInstance()->onEffect(ID);
	auto data = res->getTowerDataById(ID);

	if (!Sprite::create("../Resources/0.png"))
		return false;

	float angle = CC_RADIANS_TO_DEGREES(atan2(final.y - start.y, final.x - start.x));
	Vector<SpriteFrame*> frames;
	for (auto& x : data->bullet[1]) {
		frames.pushBack( SpriteFrameCache::getInstance()->getSpriteFrameByName(x));
	}
	Animation* animation = Animation::createWithSpriteFrames(frames, data->bulletDelay);
	Animate* animate = Animate::create(animation);
	auto act = Sequence::create(animate, RemoveSelf::create(), nullptr);
	auto node = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(data->bullet[1][2]));
	node->setPosition((start + final) / 2);
	node->setRotation(-angle+90.0f);
	node->setScale(final.distance(start)/node->getContentSize().height);
	node->runAction(act);
	Director::getInstance()->getRunningScene()->addChild(node,55);

	auto bulletBody = PhysicsBody::createCircle(10);
	bulletBody->setCategoryBitmask(1);
	bulletBody->setCollisionBitmask(0xffffffff);
	bulletBody->setContactTestBitmask(2);
	bulletBody->setDynamic(true);
	this->setPhysicsBody(bulletBody);
	bulletBody->setTag(data->ATK[level]);
	bulletBody->setName("1");

	auto delay = DelayTime::create(0.1f);
	auto se = Sequence::create(delay, RemoveSelf::create(), nullptr);
	this->runAction(se);

	auto contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = CC_CALLBACK_1(MagicBullet::onContactBegin, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener, this);

	this->setPosition(final);
	Director::getInstance()->getRunningScene()->addChild(this, 45);
	return true;
}

bool MagicBullet::onContactBegin(PhysicsContact& contact)
{
	auto bodyA = contact.getShapeA()->getBody();
	auto bodyB = contact.getShapeB()->getBody();
	if (bodyA->getCollisionBitmask() & bodyB->getCollisionBitmask()) {
		bodyA->getNode()->runAction(RemoveSelf::create());
		Effect::create(bodyA->getNode()->getPosition(), ID);
	}
	return false;
}