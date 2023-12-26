#ifndef __RESOURCE_H__
#define __RESOURCE_H__

#include <map>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <cstdio>

// ������������ݽṹ
struct TowerData {
    //������
    int ATK[4];
    //����
    float AS[4];
    //��͸
    bool PEN;
    //������Χ
    float AR;
    //���컨��
    int BLDC;
    //��������
    int UPGC[4];
    //�ۼ� 60%
    int PR[4];
    //����ͼƬ
    std::vector<std::vector<std::string>> action;
    float actionDelay;
    //����
    std::vector<std::string> lamp;
    //�ӵ�ͼƬ
    std::vector<std::vector<std::string>>bullet;
    float bulletDelay;
    //��ը��Ч
    std::vector<std::string> effect;
};

struct MonsterPair
{
    float time;
    int ID;
    int num;
    float delay;
};

struct LevelData
{
    //�ؿ����
    int level;
    //����ʱ�䣬�������࣬�������������ּ��
    std::vector<MonsterPair>monsters;
};

class Resource {
public:
    static const TowerData& getTowerDataById(const int id);
    static const std::string& getIcon(const int price, bool i);
    static const std::string& getSellPrice(const int price);
    static const LevelData& getLevelData(const int level);
    static bool find(const float mouseX, const float mouseY, const int this_level);
    static std::vector<int>gameData;
    static bool setData(const int level, const int star);
    static bool saveGame();
    static bool saveSetting(const bool sound, const bool effect);
    static void readData(const int which);
    static void removeData();
private:
    static int myGame;
    static std::map<int, TowerData> towerDataMap;
    static bool isInitializeTowerData;
    static void initializeTowerData();

    static std::map<int, std::pair<std::string, std::string>> iconMap;
    static bool isSetIconMap;
    static void setIconMap();

    static std::map<int, std::string> sellPrice;
    static bool isSetSellPrice;
    static void setSellPrice();

    static std::map<int, LevelData>levelDataMap;
    static bool isSetLevelDataMap;
    static void setLevelDataMap();

    static std::string getPath(const int which);
    static int maxLevel;
};

#endif // !__RESOURCE_H__