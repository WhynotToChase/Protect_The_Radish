#ifndef __SOUNDMANAGER_H__
#define __SOUNDMANAGER_H__

#include "cocos2d.h"
#include "audio/include/AudioEngine.h"
#include <string>

class SoundManager {
public:

    static SoundManager* getInstance();
    
    //根据文件名预加载音乐
     void preloadSound(const char* soundFilePath);
  
    //根据路径切换音乐
    //前提是设置音乐打开
    bool changeSound(const char* soundFilePath);
    
    //每次调用会改变播放状态
    void controlSounds();
    void controlEffects() { Effects = !Effects; };

    //按钮音效（固定）
   void onButtonEffect();

    //战斗音效
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
