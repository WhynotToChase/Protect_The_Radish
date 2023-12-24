#ifndef __RESOURCE_H__
#define __RESOURCE_H__

#include <map>
#include <string>

// 定义防御塔数据结构
struct TowerData {
    //攻击力
    int ATK[4];
    //射速
    float AS[4];
    //穿透
    bool PEN;
    //攻击范围
    int AR;
    //建造花费
    int BLDC;
    //升级花费
    int UPGC[4];
    //售价 60%
    int PR[4];
    //攻击图片 3张为一组
    std::string action[4][3];
    //子弹图片
    std::string bullte[4][3];
    //爆炸特效
    std::string effect[2];
};

class Resource {
public:
    static const TowerData* getTowerDataById(int id);
    static const std::string& getIcon(int price, bool i);
    static const std::string& getSellPrice(int price);

private:
    static std::map<int, TowerData> towerDataMap;
    static bool isInitializeTowerData;
    static void initializeTowerData();

    static std::map<int, std::pair<std::string, std::string>> iconMap;
    static bool isSetIconMap;
    static void setIconMap();

    static std::map<int, std::string> sellPrice;
    static bool isSetSellPrice;
    static void setSellPrice();
};

#endif // !__RESOURCE_H__