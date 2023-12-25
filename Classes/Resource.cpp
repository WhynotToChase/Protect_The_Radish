#include "Resource.h"

using namespace std;

// ��ʼ����̬��Ա����
std::map<int, TowerData> Resource::towerDataMap;
bool Resource::isInitializeTowerData = false;

std::map<int, std::pair<std::string, std::string>> Resource::iconMap;
bool Resource::isSetIconMap = false;

std::map<int, std::string> Resource::sellPrice;
bool Resource::isSetSellPrice = false;

// ��ʼ������������ӳ��
void Resource::initializeTowerData() {
    // ��Ӳ�ͬID�ķ���������
    vector<vector<string>> attackName;
    vector<vector<string>> bulletName;
    vector< string> lampName;
    vector<string> effectName;
    //����������
    //ID: 1
    //name:ƿ���� 
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
    towerDataMap.emplace(1, TowerData{ {0, 200, 300, 400}, {0, 0.8f, 0.8f, 0.8f}, false, 320.0f, 100, {0, 150, 200,INT_MAX}, {0, 60, 150, 270},
                          attackName, 0.2f,lampName,bulletName,0.2f,effectName });

    //����������
    //ID: 3
    //name:������
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

    towerDataMap.emplace(3, TowerData{ {0, 200, 250, 300}, {0, 1.2f, 1.2f, 1.2f},false, 400.0f, 160, {0,  240, 320,INT_MAX},{0, 96, 240, 432},
                       attackName,0.5f,lampName,bulletName,4.0f,effectName });

    //����������
    //ID: 4
    //name:������
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
    towerDataMap.emplace(4,TowerData{ {0, 200, 300, 400}, {0, 1.5f, 1.5f,1.5f}, true, 560.0f, 160, {0, 240, 320,INT_MAX}, {0, 96, 240, 432},
                          attackName,0.5f,lampName,bulletName,0.5f,effectName });

    //����������
    //ID: 5
    //name:ħ����
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
    towerDataMap.emplace(5, TowerData{ {0, 300, 450, 600}, {0, 0.7f, 0.6f, 0.5f}, false, 320.0f, 160, {0, 240, 320,INT_MAX}, {0, 96, 240, 432},
                          attackName,0.2f,lampName,bulletName,0.2f,effectName});
}

// ����ID��ȡ����������
 const TowerData& Resource::getTowerDataById(int id)
{
    if (!isInitializeTowerData) {
        initializeTowerData();
        isInitializeTowerData = true;
    }
    auto it = towerDataMap.find(id);
    if (it != towerDataMap.end()) {
        return it->second;
    }
    else {
        // ����ID�����ڵ���������ﷵ��һ��Ĭ��ֵ
        static TowerData defaultData = { {0, 0, 0, 0}, {0, 0, 0, 0}, false, 0, 0, {0, 0,0,0}, {0, 0, 0, 0} };
        return defaultData;
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
        return nullptr;
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
        return nullptr;
    }
}