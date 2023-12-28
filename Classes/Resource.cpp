#include "Resource.h"

bool operator==(Coor& point1, Coor& point2)
{
    return point1.x == point2.x && point1.y == point2.y;
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
    setLevelDataMap();
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
    bulletName.resize(2);
    bulletName[0] = {"","","",""};
    bulletName[1] = { "ID3_80.png","ID3_81.png","ID3_82.png","ID3_83.png","ID3_79.PNG" };

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
    towerDataMap.emplace(4,TowerData{ {0, 200, 300, 400}, {0, 1.8f, 1.8f,1.8f}, true, 560.0f, 160, {0, 240, 320,INT_MAX}, {0, 96, 240, 432},
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

bool Resource::find(const float mouseX,const float mouseY,const int this_level) {//
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
        case 1:return level_1[int(mouseX / 160)][int(mouseY / 135)];
        case 2:return level_2[int(mouseX / 160)][int(mouseY / 135)];
        case 3:return level_3[int(mouseX / 160)][int(mouseY / 135)];
        case 4:return level_4[int(mouseX / 160)][int(mouseY / 135)];
        case 5:return level_5[int(mouseX / 160)][int(mouseY / 135)];
        case 6:return level_6[int(mouseX / 160)][int(mouseY / 135)];
        case 7:return level_7[int(mouseX / 160)][int(mouseY / 135)];
        case 8:return level_8[int(mouseX / 160)][int(mouseY / 135)];
        case 9:return level_9[int(mouseX / 160)][int(mouseY / 135)];
        case 10:return level_10[int(mouseX / 160)][int(mouseY / 135)];
        default:
            break;
    }
    return false;
}

void Resource::setLevelPath()
{
    LevelPath.push_back({});
}

void Resource::setLevelDataMap()
{
    std::vector<MonsterPair> temp;
    temp.resize(3);

    levelDataMap.emplace();
}

const LevelData& Resource::getLevelData(const int level)
{
    auto it = levelDataMap.find(level);
    if (it != levelDataMap.end()) {
        return it->second;
    }
    else {
        static LevelData p{ 0,{MonsterPair{0,0,0,0}} };
        return p;
    }
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
    std::string path = "../saveData/game";
    switch (which) {
        case 1:
            path += "one";
            break;
        case 2:
            path += "two";
            break;
        case 3:
            path += "three";
            break;
        default:
            return "";
    }
    path += ".txt";
    return path;
}

void Resource::readData(const int which)
{
    if (which == 0) {
        myGame = which;
        gameData.clear();
        gameData.resize(maxLevel+1);
        gameData[1] = 4;
        return;
    }
    else {
        std::string path = getSavePath(which);
        if (path == "")
            return;
        myGame = which;
        std::fstream inFile(path, std::ios::in);
        if (!inFile.is_open()) {
            return ;
        }
        for (auto& p : gameData) {
            inFile >> p;
        }
        inFile.close();
    }
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
