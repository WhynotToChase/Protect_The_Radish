#ifndef __RESOURCE_H__
#define __RESOURCE_H__

#include <map>
#include <string>

// ������������ݽṹ
struct TowerData {
    //������
    int ATK[4];
    //����
    float AS[4];
    //��͸
    bool PEN;
    //������Χ
    int AR;
    //���컨��
    int BLDC;
    //��������
    int UPGC[4];
    //�ۼ� 60%
    int PR[4];
    //����ͼƬ 3��Ϊһ��
    std::string action[4][3];
    //�ӵ�ͼƬ
    std::string bullte[4][3];
    //��ը��Ч
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