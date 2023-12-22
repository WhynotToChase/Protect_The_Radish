#include "MousePosition.h"

using namespace cocos2d;

bool MousePosition::init() {
    if (!Label::init()) {
        return false;
    }

    // ���ó�ʼλ��
    setAnchorPoint(Vec2(1, 0));
    setPosition(Director::getInstance()->getWinSize().width, 0);
    setSystemFontSize(24);

    // ע������ƶ��¼�������
    auto mouseListener = EventListenerMouse::create();
    mouseListener->onMouseMove = CC_CALLBACK_1(MousePosition::onMouseMove, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(mouseListener, this);

    // ���� Label ��ʾ�����λ��
    updateMousePosition(Vec2::ZERO);

    return true;
}

void MousePosition::onMouseMove(Event* event) {
    EventMouse* mouseEvent = dynamic_cast<EventMouse*>(event);
    if (mouseEvent) {
        // ��ȡ���ĵ�ǰλ��
        Vec2 mousePos = Vec2(mouseEvent->getCursorX(), mouseEvent->getCursorY());

        // ���� Label ��ʾ�����λ��
        updateMousePosition(mousePos);
    }
}

void MousePosition::updateMousePosition(const Vec2& position) {
    setString(StringUtils::format("Mouse Position: (%.2f, %.2f)", position.x, position.y));
}

