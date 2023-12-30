
#include "Bullet.h"
#include <cmath>

#define SPEED 320.0f
#define SIZE 1.6f

using namespace cocos2d;

Bullet* Bullet::instance = nullptr;

Bullet* Bullet::getInstance()
{
	if (instance == nullptr)
		instance = new Bullet;
	return instance;
}

Bullet::Bullet():res(Resource::getInstance()){}

void Bullet::setupBullet(Vec2 start, const Vec2& target, const int ID,const int level,const float AR)
{
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
				TheBullet::create(start, final, ID, level);
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
	static Resource* res = Resource::getInstance();

	auto data = res->getTowerDataById(ID);
	SoundManager::getInstance()->onEffect(ID);
	if (!Sprite::initWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(data->bullet[level][0]))) {
		return false;
	}
	TheBullet::ID = ID;

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
	bulletBody->setCategoryBitmask(0);
	bulletBody->setDynamic(true);
	bulletBody->setCollisionBitmask(0xFFFFFFFF);
	this->setPhysicsBody(bulletBody);
	this->setTag(data->ATK[level]);

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
	static Resource* res = Resource::getInstance();

	auto data = res->getTowerDataById(ID);
	Vector<SpriteFrame*> bombframes;
	for (auto& x : data->effect)
		bombframes.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName(x));
	auto bombtion = Animation::createWithSpriteFrames(bombframes, 0.2f);
	auto bombte = Animate::create(bombtion);
	auto se = Sequence::create(bombte, RemoveSelf::create());
	this->runAction(se);
	return false;
}

bool FanBullet::init(const Vec2& start, const Vec2 & final, const int ID, const int level)
{
	FanBullet::ID = ID;
	SoundManager::getInstance()->onEffect(ID);
	static Resource* res = Resource::getInstance();
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


	auto bulletBody = PhysicsBody::createCircle(size.height);
	bulletBody->setCategoryBitmask(0);
	bulletBody->setCollisionBitmask(0);
	bulletBody->setContactTestBitmask(0xFFFFFfff);
	this->setPhysicsBody(bulletBody);
	bulletBody->setDynamic(true);
	this->setTag(data->ATK[level]);

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
	auto spriteA = contact.getShapeA()->getBody();
	auto spriteB = contact.getShapeB()->getBody();

	if (!spriteA->getCategoryBitmask())
		spriteA->setCollisionBitmask(spriteA->getCollisionBitmask() - spriteB->getCategoryBitmask());
	else
		spriteB->setCollisionBitmask(spriteB->getCollisionBitmask() - spriteA->getCategoryBitmask());

	return false;
}

bool MagicBullet::init(const Vec2& start, const Vec2 & final, const int ID, const int level)
{
	MagicBullet::ID = ID;
	SoundManager::getInstance()->onEffect(ID);
	static Resource* res = Resource::getInstance();
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
	bulletBody->setCategoryBitmask(0);
	bulletBody->setCollisionBitmask(0xFFFFFFFF);
	bulletBody->setDynamic(true);
	this->setPhysicsBody(bulletBody);
	this->setTag(data->ATK[level]);
	
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
	static Resource* res = Resource::getInstance();
	Vector<SpriteFrame*> bombframes;
	for (auto& x : res->getTowerDataById(ID)->effect)
		bombframes.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName(x));
	auto bombtion = Animation::createWithSpriteFrames(bombframes, 0.2f);
	auto bombte = Animate::create(bombtion);
	auto se = Sequence::create(bombte, RemoveSelf::create());
	this->runAction(se);
	return false;
}