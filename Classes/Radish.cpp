#include"Radish.h"

using namespace cocos2d;

bool Radish::init() {
	this_music = SoundManager::getInstance();

	this_level = ThisLevel::getInstance();


	initializeRadishData();

    if (!Sprite::init())
    {
        return false;
    }

	auto MyRadish = Sprite::create("..Resources/Items01-hd_30.PNG");
	MyRadish->setScale(160 / MyRadish->getContentSize().width, 135 / MyRadish->getContentSize().height);

	MenuItemSprite* MyRadishMenu = MenuItemSprite::create(MyRadish, MyRadish,
		[this](Ref* pSender) {
			if (blood == 10) {
				this_music->onEffect(11);
				playAnimation();
			}
		});
	auto menu = Menu::create(MyRadishMenu, nullptr);
	menu->setPosition(RadishPosition[this_level.this_level]);
	addChild(menu);
}

void Radish::playAnimation()
{
	Vector<SpriteFrame*> frames;

	// Load animation frames from RadishMove array
	for (const auto& frameName : RadishMove) {
		auto frame = SpriteFrame::create(frameName, Rect(0, 0, 160, 135));
		frames.pushBack(frame);
	}

	auto animation = Animation::createWithSpriteFrames(frames, 0.05f);
	auto animate = Animate::create(animation);

	auto sequence = Sequence::create(animate,nullptr);

	this->runAction(sequence);
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

	if (blood <= 0) {
		// 血量为0时使用 RadishHurt 中的第一张图像
		imagePath = RadishHurt.front();
	}
	else if (blood < RadishHurt.size()) {
		// 根据血量选择 RadishHurt 中的对应图像
		imagePath = RadishHurt[blood - 1];
	}
	else {
		// 血量大于等于 RadishHurt 大小时，使用最后一张图像
		imagePath = RadishHurt.back();
	}

	// 更改按钮图像
	auto menu = dynamic_cast<Menu*>(getChildByTag(1));
	auto button = dynamic_cast<MenuItemSprite*>(menu->getChildren().at(0));
	button->setNormalImage(Sprite::create(imagePath));
	button->setSelectedImage(Sprite::create(imagePath));

}

void Radish::initializeRadishData() {
	RadishHurt = {
		"..Resources/carrot0.PNG","..Resources/carrot1.PNG","..Resources/carrot2.PNG",
		"..Resources/carrot3.PNG","..Resources/carrot4.PNG"
		,"..Resources/carrot5.PNG","..Resources/carrot6.PNG",
		"..Resources/Items01-hd_30.PNG"
	};
	RadishMove = {
		"..Resources/Items01-hd_0.PNG","..Resources/Items01-hd_3.PNG",
		"..Resources/Items01-hd_6.PNG","..Resources/Items01-hd_10.PNG",
		"..Resources/Items01-hd_13.PNG","..Resources/Items01-hd_16.PNG",
		"..Resources/Items01-hd_19.PNG","..Resources/Items01-hd_22.PNG",
		"..Resources/Items01-hd_28.PNG","..Resources/Items01-hd_29.PNG",
		"..Resources/Items01-hd_30.PNG"
	};
	RadishPosition={
		{10,5},{7,1},{10,4},{10,5},{7,1},{11,1},{4,5},{8,2} ,{11,5},{9,1}
	};
}