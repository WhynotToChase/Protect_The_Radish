#ifndef __RADISH_H__
#define __RADISH_H__

#include "cocos2d.h"
#include"SoundManager.h"
#include<vector>
#include"ThisLevel.h"
#include<string>
class Radish :public  cocos2d::Sprite {
private:
	void playAnimation();//�ܲ�����

	void updateButtonImage();

	int blood;
public:

	virtual bool init();
	
	void takeDamage(int damage);

	void initializeRadishData();

	std::vector<std::string>RadishHurt;//���˵�ͼƬ

	std::vector<cocos2d::Vec2>RadishPosition;//ÿ���ܲ���λ��
	 
	std::vector<std::string>RadishMove;//��Ѫ�Ķ���

	SoundManager* this_music;

	ThisLevel* this_level;

};
#endif // !__RADISH_H__