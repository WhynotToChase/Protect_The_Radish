#ifndef __RADISH_H__
#define __RADISH_H__

#include "cocos2d.h"
#include"SoundManager.h"
#include<vector>

#include<string>


class Radish :public  cocos2d::Sprite {
private:
	void playAnimation();//�ܲ�����

	void updateButtonImage();

	int blood;
public:

	virtual bool init();
	
	cocos2d::Sprite* HP= nullptr;

	cocos2d::Menu* menu = nullptr;
	
	void takeDamage(int damage);

	void initializeRadishData();

	std::vector<std::string>RadishHurt;//���˵�ͼƬ

	std::vector<cocos2d::Vec2>RadishPosition;//ÿ���ܲ���λ��
	 
	std::vector<std::string>RadishMove;//��Ѫ�Ķ���
	 
	SoundManager* this_music;

	static Radish* create() {
		Radish* pRet = new(std::nothrow) Radish(); if (pRet && pRet->init()) {
			pRet->autorelease(); return pRet;
		}
		else {
			delete pRet; pRet = nullptr; return nullptr;
		}
	};
};
#endif // !__RADISH_H__