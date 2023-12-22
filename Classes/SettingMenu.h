#ifndef __SETTINGMENU_H__
#define __SETTINGMENU_H__

#include "cocos2d.h"
#include "SoundManager.h"
#include "MousePosition.h"
#include "SysMenu.h"

#define MOUSE

class SettingMenu :public cocos2d::Scene {
private:
#ifdef MOUSE
	MousePosition* position;
#endif // MOUSE

	SoundManager* music;

	void saveGame();

	void resetGame();

public:

	bool inside;

	void lastPage();

	void returnHome();

	virtual bool init();

	CREATE_FUNC(SettingMenu);
};

#endif //!__SETTINGMENU_H_
