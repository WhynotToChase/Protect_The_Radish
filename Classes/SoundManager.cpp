#include "SoundManager.h"

#include <iostream>
#include <fstream>
#include <cstdio>

using namespace cocos2d;

SoundManager* SoundManager::instance = nullptr;

const std::string SoundManager::soundPath = "../Resources/music/BGMusic.mp3";

const std::vector<std::string> SoundManager::allEffects = {
    //ID0  按钮默认音
    "../Resources/music/Button.mp3",
    //1 炮塔1发射音
    "../Resources/music/1.mp3",
    //2 炮塔建造音
    "../Resources/music/TowerBulid.mp3",
    //3 炮塔3发射音
    "../Resources/music/3.mp3",
    //4 炮塔4发射音
    "../Resources/music/4.mp3",
    //5 炮塔5发射音
    "../Resources/music/5.mp3",
    //6 炮塔出售音
    "../Resources/music/TowerSell.mp3",
    //7 炮塔升级音
    "../Resources/music/TowerUpdata.mp3",
    //8 怪物出现音
    "../Resources/music/Create.mp3",
    //9 战斗失败
    "../Resources/music/Lose.mp3",
    //10 战斗胜利
    "../Resources/music/Perfect.mp3",
    //11 萝卜状态良好
    "../Resources/music/carretgood.mp3",
    //12 萝卜状态还行
    "../Resources/music/carretnormal.mp3",
    //13 萝卜状态很差
    "../Resources/music/carretbad.mp3",
    //14 萝卜被咬 
    "../Resources/music/carretcrash.mp3",
    //15 金钱增长
    "../Resources/music/CountDown.mp3"
};

const std::vector<float> SoundManager::allEffectsLoud = { 1.5f,  1.5f,  3.0f, 1.5f ,2.5f, 9.0f,
                                                                 1.5f,  1.5f, 1.5f ,1.5f, 1.5f,
                                                                 1.5f,  1.5f, 1.5f ,1.5f, 1.5f };
SoundManager::SoundManager() {
    // 在构造函数中初始化音频引擎
    std::fstream in("../saveData/settings.txt", std::ios::in);

    if (!in.is_open()) {
        Sounds = true;
        Effects = true;
    }
    else {
        in >> Sounds >> Effects;
    }


    AudioEngine::preload("../Resources/music/BGMusic.mp3");
    for (auto& p : allEffects)
        AudioEngine::preload(p);
    if (Sounds)
        onPlaySound = AudioEngine::play2d(soundPath, true, soundPower);
    else
        onPlaySound = 0;
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

void SoundManager::onEffect(const int ID)
{
    if (Effects && ID >= 0 && ID <= 15)
        AudioEngine::play2d(allEffects[ID], false,allEffectsLoud[ID]);
}

void SoundManager::saveSetting()
{
    std::fstream outFile("../saveData/settings.txt", std::ios::out | std::ios::trunc);
    outFile << Sounds << std::endl << Effects;
    outFile.close();
}

void SoundManager::controlSounds()
{
    if (Sounds)
        AudioEngine::stop(onPlaySound);
    else
        onPlaySound=AudioEngine::play2d(soundPath, true, soundPower);
    Sounds = !Sounds;
}

void SoundManager::controlEffects() 
{
    Effects = !Effects;
}
