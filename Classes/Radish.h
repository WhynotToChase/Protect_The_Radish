#ifndef __RADISH_H__
#define __RADISH_H__

#include "cocos2d.h"
#include"SoundManager.h"
#include<vector>
#include"ThisLevel.h"
#include<string>
class Radish :public  cocos2d::Sprite {
private:
	void playAnimation();//萝卜动作

	void updateButtonImage();

	int blood;
public:

	virtual bool init();
	
	void takeDamage(int damage);

	void initializeRadishData();

	std::vector<std::string>RadishHurt;//受伤的图片

	std::vector<cocos2d::Vec2>RadishPosition;//每关萝卜的位置
	 
	std::vector<std::string>RadishMove;//满血的动作

	SoundManager* this_music;

	ThisLevel* this_level;

};
#endif // !__RADISH_H__