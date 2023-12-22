#ifndef __SOUNDMANAGER_CPP__
#define __SOUNDMANAGER_CPP__

#include "SoundManager.h"
#include "audio/include/AudioEngine.h"

using namespace cocos2d;

SoundManager* SoundManager::instance = nullptr;

SoundManager::SoundManager() {
    // 在构造函数中初始化音频引擎

    AudioEngine::preload("../Resources/music/BGMusic.mp3");
    AudioEngine::preload("../Resources/music/Button.mp3");
    this->buttonEffect = "../Resources/music/Button.mp3";
    this->lastSound = "../Resources/music/BGMusic.mp3";
    onPlaySoundID = AudioEngine::play2d(lastSound,true,soundPower);
    this->Sounds = true;
    this->Effects = true;
}

SoundManager::~SoundManager() {
    // 在析构函数中释放资源等
    AudioEngine::end();
}

SoundManager* SoundManager::getInstance() {
    if (!instance) {
        instance = new SoundManager();
    }
    return instance;
}

void SoundManager::onButtonEffect()
{
    if (Effects)
        AudioEngine::play2d(buttonEffect, false,effectPower);
}

void SoundManager::preloadSound(const char* soundFilePath)
{
    AudioEngine::preload(soundFilePath);
}

bool SoundManager::changeSound(const char* soundFilePath)
{
    if (Sounds) {
        AudioEngine::stop(onPlaySoundID);
        onPlaySoundID=AudioEngine::play2d(soundFilePath, true, soundPower);
        lastSound = soundFilePath;
        return true;
    }
    return false;
}

void SoundManager::controlSounds(const char* soundFilePath)
{
    if (Sounds)
        AudioEngine::stop(onPlaySoundID);
    else {
        if (soundFilePath == nullptr)
            onPlaySoundID = AudioEngine::play2d(lastSound, true, soundPower);
        else {
            onPlaySoundID = AudioEngine::play2d(soundFilePath, true, soundPower);
            lastSound = soundFilePath;
        }
    }
}




#endif  //!__SOUNDMANAGER_CPP__