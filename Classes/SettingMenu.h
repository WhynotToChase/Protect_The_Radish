#ifndef __SETTINGMENU_H__
#define __SETTINGMWNU_H__

#include "cocos2d.h"
#include "SoundManager.h"
#include "MousePosition.h"

#define MOUSE

class SettingMenu :public cocos2d::Scene {
private:
#ifdef MOUSE
	MousePosition* position;
#endif // MOUSE

	SoundManager* music;

public:

	void returnHome(Ref* pSender);

	virtual bool init();

	CREATE_FUNC(SettingMenu);
};

#endif //!__SETTINGMENU_H_
