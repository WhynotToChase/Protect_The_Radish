#include "VictoryScene.h"
#include"SelectMenu.h"
using namespace cocos2d;


bool VictoryScene::init(const int level,const int result )
{
    if (!Scene::init())
    {
        return false;
    }
   music = SoundManager::getInstance();

     Size WinSize = Director::getInstance()->getWinSize();
     auto sp = Sprite::create("../Resources/background101.png");
     Size spritesize = sp->getContentSize();
     sp->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
     sp->setScale(WinSize.width/ spritesize.width,WinSize.height/ spritesize.height); // ÉèÖÃ³õÊ¼Ëõ·Å
      this->addChild(sp, -10);

     Sprite* background;
    Sprite* sprite;
    ScaleTo* scaleTo;
    if (result != 4) {
        background = Sprite::create("../Resources/victory.png");
        if (result == 1) {
            sprite = Sprite::create("../Resources/onestar.PNG");
        }
        else if (result == 2) {
            sprite = Sprite::create("../Resources/twostar.PNG");
        }
        else {
            sprite = Sprite::create("../Resources/threestar.PNG");
        }
        music->onEffect(10);
    }
    else {
         music->onEffect(9);
        background = Sprite::create("../Resources/defeat.png");
        sprite = Sprite::create("../Resources/RR.png");
    }
    background->setAnchorPoint(Vec2(0.5, 0.5));
    background->setScale(5.0f);
    background->setPosition(Vec2(960, 740));
    this->addChild(background, 20);
    scaleTo = cocos2d::ScaleTo::create(0.5f, 1.5f);
    background->runAction(scaleTo);

    sprite->setPosition(cocos2d::Vec2(960, 240));
    this->addChild(sprite);
    sprite->setScale(10.0f);
    sprite->setLocalZOrder(150);
    scaleTo = cocos2d::ScaleTo::create(0.5f, 3.0f);
    sprite->runAction(scaleTo);
    auto returnButton = MenuItemImage::create(
        "../Resources/select1.png",
        "../Resources/select0.png",
        CC_CALLBACK_1(VictoryScene::onReturnButtonClick, this));

    auto menu = Menu::create(returnButton, nullptr);
    menu->setPosition(760, 400);
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
    auto p = SelectMenu::scene();
    Director::getInstance()->replaceScene(p);
}