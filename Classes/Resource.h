#ifndef __RESOURCE_H__
#define __RESOURCE_H__

#include <map>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <cstdio>

// 定义防御塔数据结构
struct TowerData {
    //攻击力
    int ATK[4];
    //射速
    float AS[4];
    //穿透
    bool PEN;
    //攻击范围
    float AR;
    //建造花费
    int BLDC;
    //升级花费
    int UPGC[4];
    //售价 60%
    int PR[4];
    //攻击图片
    std::vector<std::vector<std::string>> action;
    float actionDelay;
    //底座
    std::vector<std::string> lamp;
    //子弹图片
    std::vector<std::vector<std::string>>bullet;
    float bulletDelay;
    //爆炸特效
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
    //关卡序号
    int level;
    //出怪时间，出怪种类，出怪数量，出怪间隔
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