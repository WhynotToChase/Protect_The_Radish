#include "Resource.h"

using namespace std;

// 初始化静态成员变量
std::map<int, TowerData> Resource::towerDataMap;
bool Resource::isInitializeTowerData = false;

std::map<int, std::pair<std::string, std::string>> Resource::iconMap;
bool Resource::isSetIconMap = false;

std::map<int, std::string> Resource::sellPrice;
bool Resource::isSetSellPrice = false;

// 初始化防御塔数据映射
void Resource::initializeTowerData() {
    // 添加不同ID的防御塔数据
//防御塔数据
//ID: 1
//name:瓶子塔 
    towerDataMap.emplace(1,TowerData{ {0, 100, 150, 200}, {0, 0.5f, 0.5f, 0.5f}, false, 100, 100, {0, 150, 200,INT_MAX}, {0, 60, 150, 270},
    {{"","",""}, {"ID1_22.PNG","ID1_13.PNG","ID1_18.PNG"},
                 {"ID1_15.PNG","ID1_12.PNG","ID1_8.PNG"},
                 { "ID1_5.PNG","ID1_3.PNG","ID1_6.PNG"}},
    {{"","",""},{"ID1_0.PNG","ID1_2.PNG","ID1_21.PNG"},
                {"ID1_7.PNG","ID1_9.PNG","ID1_19.PNG"},
                {"ID1_16.PNG","ID1_14.PNG","ID1_17.PNG" }},
                       {"ID1_10.PNG","ID1_20.PNG"} });

    //防御塔数据
    //ID: 3
    //name:星星塔
    towerDataMap[3] = { {0, 120, 180, 240}, {0, 0.7f, 0.7f, 0.7f}, false, 100, 160, {0,  240, 320,INT_MAX}, {0, 96, 240, 432} };

    //防御塔数据
    //ID: 4
    //name:风扇塔
    towerDataMap[4] = { {0, 160, 240, 320}, {0, 0.7f, 0.7f, 0.6f}, true, 100, 160, {0, 240, 320,INT_MAX}, {0, 96, 240, 432} };

    //防御塔数据
    //ID: 5
    //name:魔法塔
    towerDataMap[5] = { {0, 200, 300, 400}, {0, 0.7f, 0.6f, 0.5f}, false, 100, 160, {0, 240, 320,INT_MAX}, {0, 96, 240, 432} };
}

// 根据ID获取防御塔数据
 const TowerData* Resource::getTowerDataById(int id)
{
    if (!isInitializeTowerData) {
        initializeTowerData();
        isInitializeTowerData = true;
    }
    auto it = towerDataMap.find(id);
    if (it != towerDataMap.end()) {
        return &it->second;
    }
    else {
        // 处理ID不存在的情况，这里返回一个默认值
        static TowerData defaultData = { {0, 0, 0, 0}, {0, 0, 0, 0}, false, 0, 0, {0, 0,0,0}, {0, 0, 0, 0} };
        return &defaultData;
    }
}

void Resource::setIconMap()
{
    iconMap[150] = { "levelup_150.png","levelup_no_150.png" };
    iconMap[320] = { "levelup_320.png","levelup_no_320.png" };
    iconMap[200] = { "levelup_200.png","levelup_no_200.png" };
    iconMap[240] = { "levelup_240.png","levelup_no_240.png" };
    iconMap[INT_MAX] = { "ReachHighestLevel.PNG","ReachHighestLevel.PNG" };
}

const std::string& Resource::getIcon(int price, bool i)
{
    if (!isSetIconMap) {
        setIconMap();
        isSetIconMap = true;
    }
    auto it = iconMap.find(price);
    if (it != iconMap.end()) {
        if (i)
            return it->second.first;
        else
            return it->second.second;
    }
    else {
        return "";
    }
}

void Resource::setSellPrice()
{
    sellPrice[60] = "delete_60.png";
    sellPrice[96] = "delete_96.png";
    sellPrice[150] = "delete_150.png";
    sellPrice[240] = "delete_240.png";
    sellPrice[270] = "delete_270.png";
    sellPrice[432] = "delete_432.png";
}

const std::string& Resource::getSellPrice(int price)
{
    if (!isSetSellPrice) {
        setSellPrice();
        isSetSellPrice = true;
    }
    auto it = sellPrice.find(price);
    if (it != sellPrice.end()) {
        return it->second;
    }
    else {
        return "";
    }
}