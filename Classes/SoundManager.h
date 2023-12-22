#ifndef __SOUNDMANAGER_H__
#define __SOUNDMANAGER_H__

#include "cocos2d.h"
#include "audio/include/AudioEngine.h"
#include <string>

class SoundManager {
public:

    static SoundManager* getInstance();
    
    //�����ļ���Ԥ��������
     void preloadSound(const char* soundFilePath);
  
    //����·���л�����
    //ǰ�����������ִ�
    bool changeSound(const char* soundFilePath);
    
    //ÿ�ε��û�ı䲥��״̬
    void controlSounds();
    void controlEffects() { Effects = !Effects; };

    //��ť��Ч���̶���
   void onButtonEffect();

    //ս����Ч
    bool fightEffect(const char* soundFilePath);

    bool getSounds() { return Sounds; }

    bool getEffects() { return Effects; }
private:
    
    bool Sounds;

    const float soundPower=0.4f;

    int onPlaySoundID;

   std::string lastSound;

    bool Effects;

    int onPlayEffectID;

    const float effectPower=1.5f;

    const std::string buttonEffect = "../Resources/music/Button.mp3";

    SoundManager();
    
    ~SoundManager();
    
    static SoundManager* instance;
};


#endif // !__SOUNDMANAGER_H__
