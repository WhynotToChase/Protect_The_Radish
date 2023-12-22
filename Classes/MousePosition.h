#ifndef __MOUSEPOSITION_H__
#define __MOUSEPOSITION_H__

#include "cocos2d.h"

class MousePosition : public cocos2d::Label {
public:
    CREATE_FUNC(MousePosition);

    bool init();

    void onMouseMove(cocos2d::Event* event);

    void updateMousePosition(const cocos2d::Vec2& position);
};

#endif // !___MOUSEPOSITION_H__

