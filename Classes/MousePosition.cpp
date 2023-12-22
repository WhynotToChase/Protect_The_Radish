#include "MousePosition.h"

using namespace cocos2d;

bool MousePosition::init() {
    if (!Label::init()) {
        return false;
    }

    // 设置初始位置
    setAnchorPoint(Vec2(1, 0));
    setPosition(Director::getInstance()->getWinSize().width, 0);
    setSystemFontSize(24);

    // 注册鼠标移动事件监听器
    auto mouseListener = EventListenerMouse::create();
    mouseListener->onMouseMove = CC_CALLBACK_1(MousePosition::onMouseMove, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(mouseListener, this);

    // 更新 Label 显示的鼠标位置
    updateMousePosition(Vec2::ZERO);

    return true;
}

void MousePosition::onMouseMove(Event* event) {
    EventMouse* mouseEvent = dynamic_cast<EventMouse*>(event);
    if (mouseEvent) {
        // 获取鼠标的当前位置
        Vec2 mousePos = Vec2(mouseEvent->getCursorX(), mouseEvent->getCursorY());

        // 更新 Label 显示的鼠标位置
        updateMousePosition(mousePos);
    }
}

void MousePosition::updateMousePosition(const Vec2& position) {
    setString(StringUtils::format("Mouse Position: (%.2f, %.2f)", position.x, position.y));
}

