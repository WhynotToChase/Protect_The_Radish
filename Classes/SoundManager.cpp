#include "SoundManager.h"

#include <iostream>
#include <fstream>
#include <cstdio>

using namespace cocos2d;

SoundManager* SoundManager::instance = nullptr;

const std::string SoundManager::soundPath = "../Resources/music/BGMusic.mp3";

const std::vector<std::string> SoundManager::allEffects = {
    //ID0  ��ťĬ����
    "../Resources/music/Button.mp3",
    //1 ����1������
    "../Resources/music/1.mp3",
    //2 ����������
    "../Resources/music/TowerBulid.mp3",
    //3 ����3������
    "../Resources/music/3.mp3",
    //4 ����4������
    "../Resources/music/4.mp3",
    //5 ����5������
    "../Resources/music/5.mp3",
    //6 ����������
    "../Resources/music/TowerSell.mp3",
    //7 ����������
    "../Resources/music/TowerUpdata.mp3",
    //8 ���������
    "../Resources/music/Create.mp3",
    //9 ս��ʧ��
    "../Resources/music/Lose.mp3",
    //10 ս��ʤ��
    "../Resources/music/Perfect.mp3",
    //11 �ܲ�״̬����
    "../Resources/music/carretgood.mp3",
    //12 �ܲ�״̬����
    "../Resources/music/carretnormal.mp3",
    //13 �ܲ�״̬�ܲ�
    "../Resources/music/carretbad.mp3",
    //14 �ܲ���ҧ 
    "../Resources/music/carretcrash.mp3",
    //15 ��Ǯ����
    "../Resources/music/CountDown.mp3"
};

const std::vector<float> SoundManager::allEffectsLoud = { 1.5f,  1.5f,  3.0f, 1.5f ,2.5f, 9.0f,
                                                                 1.5f,  1.5f, 1.5f ,1.5f, 1.5f,
                                                                 1.5f,  1.5f, 1.5f ,1.5f, 1.5f };
SoundManager::SoundManager() {
    // �ڹ��캯���г�ʼ����Ƶ����
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
    // �������������ͷ���Դ��

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
