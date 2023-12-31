#include"Radish.h"
#include"ThisLevel.h"
using namespace cocos2d;

bool Radish::init() {
	this_music = SoundManager::getInstance();

	initializeRadishData();

    if (!Sprite::init())
    {
        return false;
    }
	auto Hp = Sprite::create("../Resources/Hp.png");
	Hp->setScale(1.5f);
	Hp->setPosition(RadishPosition[ThisLevel::getInstance()->this_level - 1].x * 160 + 100,
		RadishPosition[ThisLevel::getInstance()->this_level - 1].y * 135 + 200);
	addChild(Hp, 100);
	HP = Sprite::create("../Resources/num10.png");
	HP->setScale(1.5f);
	HP->setPosition(RadishPosition[ThisLevel::getInstance()->this_level - 1].x * 160 + 120,
		RadishPosition[ThisLevel::getInstance()->this_level - 1].y * 135 + 200);
	addChild(HP, 100);
	Sprite* MyRadish = Sprite::create("../Resources/move10.PNG");
	MyRadish->setScale(1.5f);
	MenuItemSprite* MyRadishMenu = MenuItemSprite::create(MyRadish, MyRadish,
		[this](Ref* pSender) {
			if (blood == 10) {
				this_music->onEffect(11);
				playAnimation();
			}
		});
	menu = Menu::create(MyRadishMenu, nullptr);
	menu->setPosition(RadishPosition[ThisLevel::getInstance()->this_level-1].x*160+100,
		RadishPosition[ThisLevel::getInstance()->this_level-1].y*135+100);
	addChild(menu,100);

	lastTime = currentTime = 0.0f;
	return true;
}

void Radish::playAnimation()
{
	Vector<SpriteFrame*> frames;
	auto sprite = Sprite::create("../Resources/2.png");
	this->addChild(sprite, 110);
	for (const auto& frameName : RadishMove) {
		auto frame = SpriteFrame::create(frameName, Rect(0, 0, 171,183));
		frames.pushBack(frame);
	}
	auto animation = Animation::createWithSpriteFrames(frames, 0.05f);
	auto animate = Animate::create(animation);
	auto sequence = Sequence::create(animate, RemoveSelf::create(), nullptr);
	sprite->setPosition(RadishPosition[ThisLevel::getInstance()->this_level - 1].x * 160 + 100,
		RadishPosition[ThisLevel::getInstance()->this_level - 1].y * 135 + 100);
	sprite->runAction(sequence);
	auto sequence1 = Sequence::create(
		Place::create(Vec2(-1000,-1000)),
		DelayTime::create(0.5f),
		Place::create(Vec2(RadishPosition[ThisLevel::getInstance()->this_level - 1].x * 160 + 100,
			RadishPosition[ThisLevel::getInstance()->this_level - 1].y * 135 + 100)),
		nullptr
	);
	menu->runAction(sequence1);
}

bool Radish::takeDamage(int damage) {
	blood -= 1;	
	this_music->onEffect(14);
	if (blood <= 0) {
		blood = 0;
		return true;
	}

	updateButtonImage();
	return false;
}

void Radish::outoMusic(float delta)
{
	currentTime += delta;
	if (currentTime - lastTime >= 10.0f) {
		lastTime = currentTime;
		if (blood > 7)
			this_music->onEffect(11);
		else if (blood <= 3)
			this_music->onEffect(13);
		else
			this_music->onEffect(12);
	}
}

void Radish::updateButtonImage() {
	
	std::string imagePath;

	if (blood == 0) {
		
	}
	else if (blood<=3) {
		imagePath = RadishHurt[blood - 1];
	}
	else if(blood<=6){
		imagePath = RadishHurt[3];
	}
	else if (blood <= 8) {
		imagePath = RadishHurt[4];
	}
	else if (blood == 9) {
		imagePath = RadishHurt[5];
	}
	else {
		imagePath = RadishHurt[7];
	}

	// ¸ü¸Ä°´Å¥Í¼Ïñ
	auto sprite = Sprite::create(imagePath);
	auto menuItemSprite = MenuItemSprite::create(sprite, sprite,[this](Ref* pSender) {});
	auto newmenu = Menu::create(menuItemSprite,nullptr);
	newmenu->setScale(1.5f);
	newmenu->setGlobalZOrder(150);
	newmenu->setPosition((RadishPosition[ThisLevel::getInstance()->this_level - 1].x+3) * 160 + 100,
		(RadishPosition[ThisLevel::getInstance()->this_level - 1].y+2) * 135 + 100);
	this->addChild(newmenu);
	menu->removeFromParentAndCleanup(true);
	menu = newmenu;
	auto Hp = Sprite::create(cocos2d::StringUtils::format("../Resources/num%d.png", blood));
	Hp->setScale(1.5f);
	Hp->setGlobalZOrder(150);
	Hp->setPosition(RadishPosition[ThisLevel::getInstance()->this_level - 1].x * 160 +110,
		RadishPosition[ThisLevel::getInstance()->this_level - 1].y * 135 + 200);
	Hp->setScale(1.5f);
	this->addChild(Hp);
	HP->removeFromParentAndCleanup(true);
	HP = Hp;
}

void Radish::initializeRadishData() {
	RadishHurt = {
		"../Resources/carrot00.PNG","../Resources/carrot11.PNG","../Resources/carrot22.PNG",
		"../Resources/carrot33.PNG","../Resources/carrot44.PNG"
		,"../Resources/carrot55.PNG","../Resources/carrot66.PNG",
		"../Resources/Items01-hd_30.PNG"
	};
	RadishMove = {
		"../Resources/move0.PNG","../Resources/move1.PNG",
		"../Resources/move2.PNG","../Resources/move3.PNG",
		"../Resources/move4.PNG","../Resources/move5.PNG",
		"../Resources/move6.PNG","../Resources/move7.PNG",
		"../Resources/move8.PNG","../Resources/move9.PNG"
	};
	RadishPosition={
		{10,5},{7,1},{10,4},{10,5},{7,1},{11,1},{4,5},{8,2} ,{11,5},{9,1}
	};
	blood = 10;
}