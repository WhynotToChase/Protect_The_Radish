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
        background = Sprite::create("../Rescources/gameover0-hd_8.PNG");
        if (result == 1) {
            sprite = Sprite::create("../Rescources/onestar.PNG");
        }
        else if (result == 2) {
            sprite = Sprite::create("../Rescources/twostar.PNG");
        }
        else {
            sprite = Sprite::create("../Rescources/threestar.PNG");
        }
    }
    else {
        background = Sprite::create("../Rescources/gameover0-hd_1.PNG");
        sprite = Sprite::create("../Rescources/carrot3.PNG");
    }
    background->setAnchorPoint(Vec2(0.5, 0.5));
    background->setPosition(Vec2(960, 540));
    this->addChild(background, 20);

    sprite->setPosition(cocos2d::Vec2(960, 640));
    this->addChild(sprite);
    sprite->setScale(0.0f);
    scaleTo = cocos2d::ScaleTo::create(0.5f, 1.0f); // 在0.5秒内从0缩放到原始大小
    sprite->runAction(scaleTo);

    auto returnButton = MenuItemImage::create(
        "../Resources/Btn_ReturnLight.PNG",
        "../Resources/Btn_Return.png",
        CC_CALLBACK_1(VictoryScene::onReturnButtonClick, this));

    returnButton->setPosition(Vec2(960, 400));

    auto menu = Menu::create(returnButton, nullptr);
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
}