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

void Radish::takeDamage(int damage) {
	blood -= damage;
	if (blood < 0) {
		blood = 0;
	}
	this_music->onEffect(14);
	updateButtonImage();
}

void Radish::updateButtonImage() {
	// 根据血量更新按钮图像
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

	// 更改按钮图像
	auto menu = dynamic_cast<Menu*>(getChildByTag(66));
	auto button = dynamic_cast<MenuItemSprite*>(menu->getChildren().at(0));
	button->setNormalImage(Sprite::create(imagePath));
	button->setSelectedImage(Sprite::create(imagePath));

}

void Radish::initializeRadishData() {
	RadishHurt = {
		"../Resources/carrot0.PNG","../Resources/carrot1.PNG","../Resources/carrot2.PNG",
		"../Resources/carrot3.PNG","../Resources/carrot4.PNG"
		,"../Resources/carrot5.PNG","../Resources/carrot6.PNG",
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