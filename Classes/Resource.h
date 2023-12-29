#ifndef __RESOURCE_H__
#define __RESOURCE_H__

#include <map>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <cstdio>
#include "cocos2d.h"

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
    float time;//出的时间
    int ID;//怪的类型
    int num;//数量
    float delay;//延时
};

struct LevelData
{
    //关卡序号
    int level;
    //出怪时间，出怪种类，出怪数量，出怪间隔
    std::vector<MonsterPair>monsters;
};

struct MonsterData 
{
    //怪物的血量
    int BLOOD[4];
    //移动速度
    int SPEED[4];
    //移动图片
    std::vector<std::vector<std::string>> monsteraction;
    //死亡图片
    std::vector<std::vector<std::string>> monsterdead;
};

struct Coor
{
    int x;
    int y;
};

bool operator==(Coor& point1, Coor& point2);

class Resource {
public:
    static Resource* instance;
    static Resource* getInstance();

    Resource::Resource();

    const TowerData* getTowerDataById(const int id);

    const std::string& getIcon(const int price, bool i);
   
    const std::string& getSellPrice(const int price);
    
    const LevelData& getLevelData(const int level);
   
    bool find(const Coor& mouseP, const int this_level);
    
    std::vector<int>gameData;
    
    bool saveGame();
    
    void readData(const int which);
    
    void removeData();
    
    std::vector<std::string>Resource::carret;

private:
    
    int myGame;
    
    std::map<int, TowerData> towerDataMap;
    
    void initializeTowerData();
    
    void initializeMonsterData();

    std::map<int, std::pair<std::string, std::string>> iconMap;
    
    void setIconMap();

    std::map<int, std::string> sellPrice;
    
    void setSellPrice();

    std::map<int, LevelData>levelDataMap;
    
    void setLevelDataMap();

    std::string getSavePath(const int which);
    
    void setLevelPath();

    std::vector<Coor>LevelPath;

    int maxLevel;
};

#endif // !__RESOURCE_H__