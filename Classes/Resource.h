#ifndef __RESOURCE_H__
#define __RESOURCE_H__

#include <map>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <cstdio>
#include "cocos2d.h"



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
    float time;//����ʱ��
    int ID;//�ֵ�����
    int num;//����
    float delay;//��ʱ
};

struct LevelData
{
    //�ؿ����
    int level;
    //�ֵĲ���
    int count;
    //��Ǯ
    int moneyNum;
    //����ʱ�䣬�������࣬�������������ּ��
    std::vector<MonsterPair>monsters;
};

struct MonsterData 
{
    //�����Ѫ��
    int blood;
    //�ƶ��ٶ�
    float speed;
};

struct Coor
{
    int x;
    int y;
};

bool operator==(const Coor& point1,const Coor& point2);

int operator*(const Coor& point1, const Coor& point2);

bool operator<(const Coor& point1, const Coor& point2);

class Resource {
public:
    static Resource* instance;
    static Resource* getInstance();

    Resource::Resource();

    const TowerData* getTowerDataById(const int id);

    const std::string& getIcon(const int price, bool i);
   
    const std::string& getSellPrice(const int price);
   
    bool find(const Coor& mouseP, const int this_level);
    
    std::vector<int>gameData;
    
    bool saveGame();
    
    void readData(const int which);
    
    void removeData();
    
    std::vector<std::string>Resource::carret;

    std::vector<std::vector<Coor>>levelPath;

    std::vector<std::vector<Coor>> detailLevelPath;

    std::vector<LevelData>levelData;

    std::vector<MonsterData>monsterData;


    std::string getSavePath(const int which);

private:
    
    int myGame;
    
    std::map<int, TowerData> towerDataMap;
    
    void initializeTowerData();
    
    void initializePathData();

    void initializeMonsterData();

    std::map<int, std::pair<std::string, std::string>> iconMap;
    
    void setIconMap();

    std::map<int, std::string> sellPrice;
    
    void setSellPrice();

    void setLevelData();
    
    void setLevelPath();

    int maxLevel;
};

#endif // !__RESOURCE_H__