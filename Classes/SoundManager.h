#ifndef __SOUNDMANAGER_H__
#define __SOUNDMANAGER_H__

#include "cocos2d.h"
#include <string>
#include <vector>
#include "audio/include/AudioEngine.h"

class SoundManager {
public:

    static SoundManager* getInstance();
    
    //每次调用会改变播放状态
    void controlSounds();
    void controlEffects();

    //音效
    void onEffect(const int ID = 0);

    bool getSounds() { return Sounds; }

    bool getEffects() { return Effects; }

    void saveSetting();
private:
    
    bool Sounds;

    const float soundPower=0.3f;

    bool Effects;

    int onPlaySound;

    static const std::vector<std::string> allEffects; 

    static const std::vector<float> allEffectsLoud;

    static const std::string soundPath;

    SoundManager();
    
    ~SoundManager();
    
    static SoundManager* instance;
};


#endif // !__SOUNDMANAGER_H__
