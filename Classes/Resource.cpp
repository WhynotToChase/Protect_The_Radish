#include "Resource.h"

//#define RELEASE

bool operator==(const Coor& point1, const Coor& point2)
{
    return point1.x == point2.x && point1.y == point2.y;
}

int operator*(const Coor& point1, const Coor& point2)
{
    return sqrt((point1.x - point2.x) * (point1.x - point2.x) + (point1.y - point2.y) * (point1.y - point2.y) );
}

bool operator<(const Coor& point1, const Coor& point2)
{
    return point1.x < point2.x || point1.x == point2.x && point1.y < point2.y;
}

Resource* Resource::instance=nullptr;

Resource* Resource::getInstance()
{
    if (instance == nullptr)
        instance = new Resource();
    return instance;
}

Resource::Resource()
{
    maxLevel = 10;
    gameData = std::vector<int>(maxLevel + 1, 0);
    carret = { "../Resources/lock.PNG",
               "../Resources/onestar.PNG",
               "../Resources/twostar.PNG",
               "../Resources/threestar.PNG",
               "../Resources/fourstar.PNG" };
    myGame = 0;
    initializeTowerData();
    setIconMap();
    setSellPrice();
    setLevelData();
    setLevelPath();
    initializePathData();
    initializeMonsterData();
}


//初始化路径
void Resource::initializePathData() {
    //十条路径
    detailLevelPath.clear();
    detailLevelPath.resize(10);
    detailLevelPath[0] = { {1,5},{1,4} ,{1,3}, {1,2},{2,2},{3,2}, {4,2},{4,3},{5,3},{6,3}, {7, 3}, { 7,2 },
        {8,2},{9,2}, { 10,2 },{10,3},{10,4}, { 10,5 } };
    detailLevelPath[1] = { {4,5},{5,5},{6,5},{7,5},{8,5}, {9,5},{9,4}, {9,3},{8,3},{7,3},{6,3},{5,3},{4,3},
        {3,3}, {2,3},{2,2}, {2,1},{3,1},{4,1},{5,1},{6,1}, {7,1} };
    detailLevelPath[2] = { {1,4},{1,3},{1,2}, {1,1},{2,1},{3,1},{4,1}, {5,1},{5,2}, {5,3},{6,3}, {7,3},{7,4},
        {7,5},{8,5},{8,4},{9,4}, {10,4} };
    detailLevelPath[3] = { {0,4},{1,4}, {2,4},{2,3},{2,2}, {2,1},{3,1}, {4,1},{4,2}, {4,3},{5,3},{6,3}, {7,3},
        {7,2}, {7,1},{8,1},{9,1}, {10,1},{10,2},{10,3},{10,4}, {10,5} };
    detailLevelPath[4] = { {10,1},{10,2},{10,3},{10,4}, {10,5},{9,5},{8,5}, {7,5},{7,4},{6,4},{5,4}, {4,4},
        {4,3},{3,3},{2,3}, {1,3},{1,2},{2,2},{2,1}, {2,0},{3,0},{4,0},{5,0},{6,0} ,{7,0},{7,1} };
    detailLevelPath[5] = { {0,5},{1,5},{2,5},{3,5},{4,5}, {5,5},{5,4},{5,3},{5,2}, {5,1},{6,1},{7,1},{8,1},
        {9,1},{10,1}, {11,1} };
    detailLevelPath[6] = { {1,5},{1,4},{1,3},{1,2}, {1,1},{2,1},{3,1}, {4,1},{4,2}, {4,3},{5,3},{6,3},{7,3},
        {8,3},{8,2}, {8,1},{9,1}, {10,1},{10,2},{10,3},{10,4}, {10,5},{9,5},{8,5},{7,5},{6,5} ,{5,5}, {4,5} };
    detailLevelPath[7] = { {10,4},{10,3},{9,3},{8,3},{7,3},{6,3}, {5,3},{5,4}, {5,5},{4,5},{3,5},{2,5},{1,5},
        {0,5},{0,4}, {0,3},{1,3}, {2,3},{2,2}, {2,1},{3,1}, {4,1},{4,2},{5,2},{6,2},{7,2}, {8,2} };
    detailLevelPath[8] = { {1,1},{1,2},{1,3},{1,4}, {1,5},{2,5}, {3,5},{3,4},{4,4},{4,3},{5,3},{5,2},{6,2},
        {7,2},{7,3}, {8,3},{8,4},{9,4},{9,5},{10,5}, {11,5} };
    detailLevelPath[9] = { {1,1},{1,2}, {1,3},{2,3}, {3,3},{3,4}, {3,5},{4,5},{5,5},{6,5},{7,5},{8,5}, {9,5},
        {9,4},{9,3}, {9,2},{8,2},{7,2},{6,2}, {5,2},{5,1},{6,1},{7,1},{8,1}, {9,1} };
}
// 初始化防御塔数据映射
void Resource::initializeTowerData() {
    using namespace std;
    // 添加不同ID的防御塔数据
    vector<vector<string>> attackName;
    vector<vector<string>> bulletName;
    vector< string> lampName;
    vector<string> effectName;
    //防御塔数据
    //ID: 1
    //name:瓶子塔 
    attackName.clear();
    attackName.resize(4);
    attackName[0]={ "","","" };
    attackName[1]={ "ID1_22.PNG","ID1_13.PNG","ID1_18.PNG" };
    attackName[2]={ "ID1_15.PNG","ID1_12.PNG","ID1_8.PNG" };
    attackName[3]={ "ID1_5.PNG","ID1_3.PNG","ID1_6.PNG" };

    lampName.clear();
    lampName.resize(2);
    lampName[0] = "";
    lampName[1] = "ID1_11.PNG";

    bulletName.clear();
    bulletName.resize(4);
    bulletName[0]={ "","","" };
    bulletName[1]={ "ID1_0.PNG","ID1_2.PNG","ID1_21.PNG" };
    bulletName[2]={ "ID1_7.PNG","ID1_9.PNG","ID1_19.PNG" };
    bulletName[3]={ "ID1_16.PNG","ID1_14.PNG","ID1_17.PNG" };

    effectName.clear();
    effectName.resize(2);
    effectName[0]="ID1_10.PNG";
    effectName[1]="ID1_20.PNG";
    towerDataMap.emplace(1, TowerData{ {0, 200, 300, 400}, {0, 1.0f, 1.0f, 1.0f}, false, 320.0f, 100, {0, 150, 200,INT_MAX}, {0, 60, 150, 270},
                          attackName, 0.2f,lampName,bulletName,0.2f,effectName });

    //防御塔数据
    //ID: 3
    //name:星星塔
    attackName.clear();
    attackName.resize(4);
    attackName[0] = { ""};
    attackName[1] = { "ID3_101.png" };
    attackName[2] = { "ID3_71.PNG" };
    attackName[3] = { "ID3_0.PNG" };

    lampName.clear();
    lampName.resize(4);
    lampName[0] = "";
    lampName[1] = "ID3_89.PNG";
    lampName[2] = "ID3_56.PNG";
    lampName[3] = "ID3_84.PNG";

    bulletName.clear();
    bulletName.resize(4);
    bulletName[0] = {"","","",""};
    bulletName[1] = { "ID3_80.png","ID3_81.png","ID3_82.png","ID3_83.png","ID3_79.PNG" };
    bulletName[2] = { "ID3_80.png","ID3_81.png","ID3_82.png","ID3_83.png","ID3_79.PNG" };
    bulletName[3] = { "ID3_80.png","ID3_81.png","ID3_82.png","ID3_83.png","ID3_79.PNG" };

    effectName.clear();
    effectName.resize(2);
    effectName[0] = "ID3_85.PNG";
    effectName[1] = "ID3_73.PNG";

    towerDataMap.emplace(3, TowerData{ {0, 200, 250, 300}, {0, 1.5f, 1.5f, 1.5f},false, 400.0f, 160, {0,  240, 320,INT_MAX},{0, 96, 240, 432},
                       attackName,0.5f,lampName,bulletName,4.0f,effectName });

    //防御塔数据
    //ID: 4
    //name:风扇塔
    attackName.clear();
    attackName.resize(4);
    attackName[0] = { "" };
    attackName[1] = { "ID4_26.PNG" };
    attackName[2] = { "ID4_10.PNG" };
    attackName[3] = { "ID4_12.PNG" };

    lampName.clear();
    lampName.resize(4);
    lampName[0] = "";
    lampName[1] = "ID4_0.PNG";
    lampName[2] = "ID4_1.PNG";
    lampName[3] = "ID4_2.PNG";

    bulletName.clear();
    bulletName.resize(4);
    bulletName[0] = { "" };
    bulletName[1] = { "ID4_16.PNG" };
    bulletName[2] = { "ID4_17.PNG" };
    bulletName[3] = { "ID4_11.PNG" };

    effectName.clear();
    effectName.resize(2);
    effectName[0] = { "ID4_14.PNG" };
    effectName[1] = { "ID4_15.PNG" };
    towerDataMap.emplace(4,TowerData{ {0, 150, 225, 300}, {0, 1.8f, 1.8f,1.8f}, true, 400.0f, 160, {0, 240, 320,INT_MAX}, {0, 96, 240, 432},
                          attackName,0.5f,lampName,bulletName,0.5f,effectName });

    //防御塔数据
    //ID: 5
    //name:魔法塔
    attackName.clear();
    attackName.resize(4);
    attackName[0] = { "" ,"","",""};
    attackName[1] = { "ID5_16.PNG","ID5_17.PNG","ID5_19.PNG", "ID5_20.PNG" };
    attackName[2] = { "ID5_28.PNG","ID5_25.PNG","ID5_29.PNG","ID5_30.PNG" };
    attackName[3] = { "ID5_8.PNG","ID5_5.PNG","ID5_4.PNG","ID5_3.PNG" };

    lampName.clear();

    bulletName.clear();
    bulletName.resize(2);
    bulletName[0] = { "","","" };
    bulletName[1] = { "ID5_2.PNG","ID5_1.PNG","ID5_0.PNG" };

    effectName.clear();
    effectName.resize(2);
    effectName[0] = { "ID5_23.PNG" };
    effectName[1] = { "ID5_14.PNG" };
    towerDataMap.emplace(5, TowerData{ {0, 300, 450, 600}, {0, 1.0f, 1.0f, 1.0f}, false, 320.0f, 160, {0, 240, 320,INT_MAX}, {0, 96, 240, 432},
                          attackName,0.2f,lampName,bulletName,0.2f,effectName});


}

// 根据ID获取防御塔数据
 const TowerData* Resource::getTowerDataById(const int id)
{
    auto it = towerDataMap.find(id);
    if (it != towerDataMap.end()) {
        return&it->second;
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

const std::string& Resource::getIcon(const int price, bool i)
{
    auto it = iconMap.find(price);
    if (it != iconMap.end()) {
        if (i)
            return it->second.first;
        else
            return it->second.second;
    }
    else {
        static std::string p = "";
        return p;
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

const std::string& Resource::getSellPrice(const int price)
{
    auto it = sellPrice.find(price);
    if (it != sellPrice.end()) {
        return it->second;
    }
    else {
        static std::string p = "";
        return p;
    }
}

bool Resource::find(const Coor& mouseP,const int this_level) {
    int level_1[12][8] = {//第一关
        //0                 1                2                  3
        {0,0,1,1,1,1,1,0},{0,0,0,0,0,0,0,0},{0,1,0,1,1,1,1,0},{0,1,0,1,1,1,1,0},
        //4                 5                6                  7
        {1,1,0,0,1,1,1,0},{1,1,1,0,1,1,1,0},{1,1,1,0,1,1,1,0},{1,1,0,0,1,1,1,0},
        //8                 9                10                 11
        {0,1,0,1,1,1,1,0},{0,1,0,1,1,1,1,0} ,{0,0,0,0,0,0,0,0},{0,0,1,1,1,1,1,0}
    };
    int level_2[12][8] = {//第二关
        //0                 1                2                  3
        {0,0,1,1,1,1,1,0},{0,0,1,1,1,1,1,0},{0,0,0,0,1,1,1,0},{0,0,1,0,1,1,1,0},
        //4                 5                6                  7
        {1,0,1,0,1,0,1,0},{1,0,1,0,1,0,1,0},{1,0,1,0,1,0,1,0},{1,0,1,0,1,0,1,0},
        //8                 9                10                 11
        {0,0,1,0,1,0,1,0} ,{0,1,1,0,0,0,1,0} ,{0,0,1,1,1,1,1,0},{0,0,1,1,1,1,1,0}
    };
    int level_3[12][8] = {//第三关
        //0                 1                2                  3
        {0,1,1,1,1,1,1,0},{0,0,0,0,0,1,1,0},{0,0,1,1,1,1,1,0},{0,0,1,1,1,1,1,0},
        //4                 5                6                  7
        {1,0,1,1,1,1,1,0},{1,0,0,0,1,1,1,0},{1,1,1,0,1,1,1,0},{1,1,1,0,0,0,1,0},
        //8                 9                10                 11
        {1,1,1,1,0,0,1,0},{0,1,1,1,0,1,1,0} ,{0,1,1,1,0,1,1,0},{0,0,1,1,1,1,1,0}
    };
    int level_4[12][8] = {//第四关
        //0                 1                2                  3
        {0,0,1,1,0,1,1,0},{0,0,1,1,0,1,1,0},{0,0,0,0,0,1,1,0},{0,0,1,1,1,1,1,0},
        //4                 5                6                  7
        {1,0,0,0,1,1,1,0},{1,1,1,0,1,1,1,0},{1,1,1,0,1,1,1,0},{1,0,0,0,1,1,1,0},
        //8                 9                10                 11
        {0,0,1,1,1,1,1,0},{0,0,1,1,1,1,1,0} ,{0,0,0,0,0,0,1,0},{0,0,1,1,1,1,1,0}
    };
    int level_5[12][8] = {//第五关
        //0                 1                2                  3
        {0,0,1,1,1,1,1,0},{0,1,0,0,1,1,1,0},{0,0,0,0,1,1,1,0},{0,1,1,0,1,1,1,0},
        //4                 5                6                  7
        {0,1,1,0,0,1,1,0},{0,1,1,1,0,1,1,0},{0,1,1,1,0,1,1,0},{0,0,0,1,0,0,1,0},
        //8                 9                10                 11
        {0,1,1,1,1,0,1,0},{0,1,1,1,1,0,1,0} ,{0,0,0,0,0,0,1,0},{0,0,1,1,1,1,1,0}
    };
    int level_6[12][8] = {//第六关
        //0                 1                2                  3
        {0,0,1,1,1,0,1,0},{0,0,1,1,1,0,1,0},{0,1,1,1,1,0,1,0},{0,1,1,1,1,0,1,0},
        //4                 5                6                  7
        {1,1,1,1,1,0,1,0},{1,0,0,0,0,0,1,0},{1,0,1,1,1,1,1,0},{1,0,1,1,1,1,1,0},
        //8                 9                10                 11
        {0,0,1,1,1,1,1,0},{0,0,1,1,1,1,1,0} ,{0,0,1,1,1,1,1,0},{0,0,1,1,1,1,1,0}
    };
    int level_7[12][8] = {//第七关
        //0                 1                2                  3
        {0,0,1,1,1,1,1,0},{0,0,0,0,0,0,1,0},{0,0,1,1,1,1,1,0},{0,0,1,1,1,1,1,0},
        //4                 5                6                  7
        {0,0,0,0,1,0,1,0},{1,1,1,0,1,0,1,0},{1,1,1,0,1,0,1,0},{1,1,1,0,1,0,1,0},
        //8                 9                10                 11
        {0,0,0,0,1,0,1,0},{0,0,1,1,1,0,1,0} ,{0,0,0,0,0,0,1,0},{0,0,1,1,1,1,1,0}
    };
    int level_8[12][8] = {//第八关
        //0                 1                2                  3
        {0,0,1,0,0,0,1,0},{0,0,1,0,0,0,1,0},{0,0,0,0,1,0,1,0},{0,0,1,1,1,0,1,0},
        //4                 5                6                  7
        {0,0,0,1,1,0,1,0},{1,1,0,0,0,0,1,0},{1,1,0,0,1,1,1,0},{0,1,0,0,1,1,1,0},
        //8                 9                10                 11
        {0,1,0,0,1,1,1,0},{0,1,1,0,1,1,1,0} ,{0,0,1,0,0,1,1,0},{0,0,1,1,1,1,1,0}
    };
    int level_9[12][8] = {//第九关
        //0                 1                2                  3
        {0,0,1,1,1,1,1,0},{0,0,0,0,0,0,1,0},{0,1,1,1,1,0,1,0},{0,1,1,1,0,0,1,0},
        //4                 5                6                  7
        {1,1,1,0,0,1,1,0},{1,1,0,0,1,1,1,0},{1,1,0,1,1,1,1,0},{1,1,0,0,1,1,1,0},
        //8                 9                10                 11
         {0,1,1,0,0,1,1,0},{0,1,1,1,0,0,1,0} ,{0,0,1,1,1,0,1,0},{0,0,1,1,1,0,1,0}
    };
    int level_10[12][8] = {//第十关
        //0                 1                2                  3
        {0,0,1,1,1,1,1,0},{0,0,0,0,1,1,1,0},{0,1,1,0,1,1,1,0},{0,1,1,0,0,0,1,0},
        //4                 5                6                  7
        {1,1,1,1,1,0,1,0},{1,0,0,1,1,0,1,0},{1,0,0,1,1,0,1,0},{0,0,0,1,1,0,1,0},
        //8                 9                10                 11
       {0,0,0,1,1,0,1,0},{0,0,0,0,0,0,1,0} ,{0,0,1,1,1,1,1,0},{0,0,1,1,1,1,1,0}
    };
    switch (this_level) {
        case 1:return level_1[mouseP.x][mouseP.y];
        case 2:return level_2[mouseP.x][mouseP.y];
        case 3:return level_3[mouseP.x][mouseP.y];
        case 4:return level_4[mouseP.x][mouseP.y];
        case 5:return level_5[mouseP.x][mouseP.y];
        case 6:return level_6[mouseP.x][mouseP.y];
        case 7:return level_7[mouseP.x][mouseP.y];
        case 8:return level_8[mouseP.x][mouseP.y];
        case 9:return level_9[mouseP.x][mouseP.y];
        case 10:return level_10[mouseP.x][mouseP.y];
        default:
            break;
    }
    return false;
}

void Resource::setLevelPath()
{
    levelPath.push_back({ {0,0} ,{ 10,5 }, {7,1}, {10,4},{10,5} ,{7,1} ,{11,1}, {4,5},{8,2},{11,5},{9,1} });
    levelPath.push_back({ {1,5},{0,-3},{3,0},{0,1},{3,0},{0,-1},{3,0},{0,3} });
    levelPath.push_back({ {4,5},{5,0},{0,-2},{-7,0},{0,-2},{5,0} });
    levelPath.push_back({ {1, 4}, { 0,-3 }, { 4,0 }, { 0,2 }, { 2,0 }, { 0,2 }, { 1,0 }, { 0,-1 }, { 2,0 } });
    levelPath.push_back({ {0,4},{2,0},{0,-3},{2,0},{0,2},{3,0},{0,-2},{3,0},{0,4} });
    levelPath.push_back({ {10,1},{0,4},{-3,0},{0,-1},{-3,0},{0,-1},{-3,0},{0,-1},{1,0},{0,-2}, {5,0},{1,0} });
    levelPath.push_back({ {0,5},{5,0},{0,-4},{6,0} });
    levelPath.push_back({ {1,5},{0,-4},{3,0},{0,2},{4,0},{0,-2},{2,0},{0,4},{-6,0} });
    levelPath.push_back({ {10,4},{0,-1},{-5,0},{0,2},{-5,0},{0,-2},{2,0},{0,-2},{2,0},{0,1},{4,0} });
    levelPath.push_back({ {1,1},{0,4},{2,0},{0,-1},{1,0},{0,-1},{1,0},{0,-1},{2,0},{0,1},{1,0},{0,1},{1,0},{0,1},{2,0}});
    levelPath.push_back({ {1,1},{0,2},{2,0},{0,2},{6,0},{0,-3},{-4,0},{0,-1},{4,0} });
}

void Resource::setLevelData()
{
    levelData.resize(maxLevel + 1);
    levelData[1] = { 1,1,5000,{{6.0f,1,10,2.5f}} };
    levelData[2] = { 1,5,600,{{6.0f,1,10,2.5f},{6.0f,2,20,2.5f},{6.0f,3,20,2.5f},{6.0f,4,20,2.5f},{6.0f,4,20,1.5f} } };
    levelData[3] = { 1,5,600,{{6.0f,1,10,2.5f},{6.0f,2,20,2.5f},{6.0f,3,20,2.5f},{6.0f,4,20,2.5f},{6.0f,4,20,1.5f} } };
    levelData[4] = { 1,5,600,{{6.0f,1,10,2.5f},{6.0f,2,20,2.5f},{6.0f,3,20,2.5f},{6.0f,4,20,2.5f},{6.0f,4,20,1.5f} } };
    levelData[5] = { 1,5,600,{{6.0f,1,10,2.5f},{6.0f,2,20,2.5f},{6.0f,3,20,2.5f},{6.0f,4,20,2.5f},{6.0f,4,20,1.5f} } };
    levelData[6] = { 1,5,600,{{6.0f,1,10,2.5f},{6.0f,2,20,2.5f},{6.0f,3,20,2.5f},{6.0f,4,20,2.5f},{6.0f,4,20,1.5f} } };
    levelData[7] = { 1,5,600,{{6.0f,1,10,2.5f},{6.0f,2,20,2.5f},{6.0f,3,20,2.5f},{6.0f,4,20,2.5f},{6.0f,4,20,1.5f} } };
    levelData[8] = { 1,5,600,{{6.0f,1,10,2.5f},{6.0f,2,20,2.5f},{6.0f,3,20,2.5f},{6.0f,4,20,2.5f},{6.0f,4,20,1.5f} } };
    levelData[9] = { 1,5,600,{{6.0f,1,10,2.5f},{6.0f,2,20,2.5f},{6.0f,3,20,2.5f},{6.0f,4,20,2.5f},{6.0f,4,20,1.5f} } };
    levelData[10] = { 1,5,600,{{6.0f,1,10,2.5f},{6.0f,2,20,2.5f},{6.0f,3,20,2.5f},{6.0f,4,20,2.5f},{6.0f,4,20,1.5f} } };
    levelData[0] = { 1,1,600,{{6.0f,1,10,2.5f}} };
}

void Resource::initializeMonsterData()
{
    monsterData.resize(5);
    monsterData[0] = {};
    monsterData[1] = { 1800,70 };
    monsterData[2] = { 2000,90 };
    monsterData[3] = { 1500,60 };
    monsterData[4] = { 2500,100 };
}

bool Resource::saveGame()
{
    std::string path = getSavePath(myGame);
    if (path == "")
        return false;
    std::ofstream outFile(path, std::ios::out | std::ios::trunc);
    if (!outFile.is_open()) {
        return false;
    }
    for (auto p : gameData) {
        outFile << p << std::endl;
    }
    outFile.close();
    return true;
}

std::string Resource::getSavePath(const int which)
{
#ifdef RELEASE
    std::string path = "Resources/game";
#endif // !RELEASE
#ifndef RELEASE
    std::string path = "../Resources/game";
#endif // !RELEASE

    switch (which) {
        case 1:
            path += "One";
            break;
        case 2:
            path += "Two";
            break;
        case 3:
            path += "Three";
            break;
        default:
            return "";
    }
    path += ".txt";
    return path;
}

void Resource::readData(const int which)
{
    std::string path = getSavePath(which);
    if (path == "")
        return;
    myGame = which;
    std::fstream inFile(path, std::ios::in);
    if (!inFile.is_open()) {
        gameData.resize(maxLevel + 1, 0);
        gameData[1] = 4;
    }
    else
        for (auto& p : gameData) {
            inFile >> p;
        }
    inFile.close();
}

void Resource::removeData()
{
    std::string path = getSavePath(myGame);
    gameData.clear();
    gameData.resize(maxLevel + 1);
    gameData[1] = 4;
    // 使用 remove 函数删除文件
    std::remove(path.c_str());
}
