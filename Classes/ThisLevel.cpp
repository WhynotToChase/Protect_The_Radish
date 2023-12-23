#include "ThisLevel.h"

using namespace cocos2d;

bool ThisLevel::init(const int&level)
{
    this_music = SoundManager::getInstance();

    this_mouse = MousePosition::create();
    addChild(this_mouse);

    if (!Scene::init())
    {
        return false;
    }


    ////////////////// 
    Size WinSize = Director::getInstance()->getWinSize();

    //先建立一个大背景第level关的背景
    auto sp = Sprite::create(ThisLevel::SelectLevel(level));
    Size spritesize = sp->getContentSize();
    sp->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
    sp->setScale(WinSize.width / spritesize.width, WinSize.height / spritesize.height); // 设置初始缩放
    this->addChild(sp, -10, 1);



    this->schedule(CC_SCHEDULE_SELECTOR(ThisLevel::update), 0.1f);

    return true;
}

std::string ThisLevel::SelectLevel(const int&level) {
    switch (level) {
        case 1:return "../Resources/level1.png";
        case 2:return "../Resources/level2.png";
        case 3:return "../Resources/level3.png";
        case 4:return "../Resources/level4.png";
        case 5:return "../Resources/level5.png";
        case 6:return "../Resources/level6.png";
        case 7:return "../Resources/level7.png";
        case 8:return "../Resources/level8.png";
        case 9:return "../Resources/level9.png";
        case 10:return "../Resources/level10.png";
        default:
            break;
    }
    return "";
}

void ThisLevel::update(float delta) {

}