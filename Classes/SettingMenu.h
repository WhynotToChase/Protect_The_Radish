#ifndef __SETTINGMENU_H__
#define __SETTINGMENU_H__

#include "cocos2d.h"
#include "SoundManager.h"
#include "MousePosition.h"
#include "SysMenu.h"
#include "Resource.h"


class SettingMenu :public cocos2d::Scene {
private:

	Resource* res;

	SoundManager* music;

public:

	static bool inside;

	void lastPage();

	void returnHome();

	virtual bool init();
	static SettingMenu* create(bool i) {
		inside = i;
		SettingMenu* pRet = new(std::nothrow) SettingMenu(); if (pRet && pRet->init()) {
			pRet->autorelease(); return pRet;
		}
		else {
			delete pRet; pRet = nullptr; return nullptr;
		}
	};

};

#endif //!__SETTINGMENU_H_
