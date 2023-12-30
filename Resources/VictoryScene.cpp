#include "VictoryScene.h"
#include"SelectMenu.h"
using namespace cocos2d;


bool VictoryScene::init(const int&level,const int&result )
{
    if (!Scene::init())
    {
        return false;
    }

    Size WinSize = Director::getInstance()->getWinSize();
    auto sp = Sprite::create("../Resources/MonsterNest_0.PNG");
    Size spritesize = sp->getContentSize();
    sp->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
    sp->setScale(WinSize.width / spritesize.width, WinSize.height / spritesize.height); // 设置初始缩放
    this->addChild(sp, -10, 1);

    Sprite* background;
    Sprite* sprite;
    ScaleTo* scaleTo;
    if (result != 4) {
        background = Sprite::create("../Resources/gameover0-hd_8.PNG");
        if (result == 1) {
            sprite = Sprite::create("../Resources/onestar.PNG");
        }
        else if (result == 2) {
            sprite = Sprite::create("../Resources/twostar.PNG");
        }
        else {
            sprite = Sprite::create("../Resources/threestar.PNG");
        }
    }
    else {
        background = Sprite::create("../Resources/gameover0-hd_1.PNG");
        sprite = Sprite::create("../Resources/carrot3.PNG");
    }
    background->setAnchorPoint(Vec2(0.5, 0.5));
    background->setPosition(Vec2(960, 540));
    background->setScale(2.0f);
    this->addChild(background, 20);

    sprite->setPosition(cocos2d::Vec2(960, 640));
    this->addChild(sprite);
    sprite->setScale(10.0f);
    sprite->setLocalZOrder(150);
    scaleTo = cocos2d::ScaleTo::create(0.5f, 3.0f); // 在0.5秒内从0缩放到原始大小
    sprite->runAction(scaleTo);

    auto returnButton = MenuItemImage::create(
        "../Resources/select1.png",
        "../Resources/select0.png",
        CC_CALLBACK_1(VictoryScene::onReturnButtonClick, this));

    auto menu = Menu::create(returnButton, nullptr);
    menu->setPosition(960, 400);
    menu->setScale(1.5f);
    this->addChild(menu, 10);

    return true;
}

void VictoryScene::onReturnButtonClick(Ref* sender)
{
    returnToMainScene();
}

void VictoryScene::returnToMainScene()
{
    Director::getInstance()->popScene();
    Director::getInstance()->popScene();
}