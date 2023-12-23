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

// ����������ӳ��
std::map<int, TowerData> towerDataMap;

// ��ʼ������������ӳ��
void initializeTowerData() {
    // ��Ӳ�ͬID�ķ���������
//����������
//ID: 1
//name:ƿ���� 
    towerDataMap[1] = { {0, 100, 150, 200}, {0, 0.5f, 0.5f, 0.5f}, false, 100, 100, {0, 0, 150, 200}, {0, 60, 150, 270},
    {{"","",""}, {"ID1_22.PNG","ID1_13.PNG","ID1_18.PNG"},
                 {"ID1_15.PNG","ID1_12.PNG","ID1_8.PNG"},
                 { "ID1_5.PNG","ID1_3.PNG","ID1_6.PNG"}},
    {{"","",""},{"ID1_0.PNG","ID1_2.PNG","ID1_21.PNG"},
                {"ID1_7.PNG","ID1_9.PNG","ID1_19.PNG"},
                {"ID1_16.PNG","ID1_14.PNG","ID1_17.PNG" }},
                       {"ID1_10.PNG","ID1_20.PNG"} };
 
//����������
//ID: 3
//name:������
    towerDataMap[3] = { {0, 120, 180, 240}, {0, 0.7f, 0.7f, 0.7f}, false, 100, 160, {0, 0, 240, 320}, {0, 96, 240, 432} };

//����������
//ID: 4
//name:������
    towerDataMap[4] = { {0, 160, 240, 320}, {0, 0.7f, 0.7f, 0.6f}, true, 100, 160, {0, 0, 240, 320}, {0, 96, 240, 432} };

//����������
//ID: 5
//name:ħ����
    towerDataMap[5] = { {0, 200, 300, 400}, {0, 0.7f, 0.6f, 0.5f}, false, 100, 160, {0, 0, 240, 320}, {0, 96, 240, 432} };
}

// ����ID��ȡ����������
const TowerData& getTowerDataById(int id) {
    auto it = towerDataMap.find(id);
    if (it != towerDataMap.end()) {
        return it->second;
    }
    else {
        // ����ID�����ڵ��������������׳��쳣���߷���һ��Ĭ��ֵ
        // ���ﷵ��һ��Ĭ��ֵ������Ը���ʵ���������
        static TowerData defaultData = { {0, 0, 0, 0}, {0, 0, 0, 0}, false, 0, 0, {0, 0, 0, 0}, {0, 0, 0, 0} };
        return defaultData;
    }
}



//��һЩ���ܻ��õ���ģ��

/*
auto dead = CallFunc::create([=]() {
    // �ص�������ִ�����پ���Ĳ���
    p->removeFromParentAndCleanup(true);
    });
*/

//��������ģ��
/*
private:
    bool onTouchBegan(cocos2d::Touch * touch, cocos2d::Event * event, cocos2d::Sprite * menu);
    void monitor(cocos2d::Sprite * menu);
    void removeTouchListener(); 


bool %%%%%::onTouchBegan(Touch* touch, Event* event, Sprite* menu)
{
    Vec2 touchPoint = this->convertToNodeSpace(touch->getLocation());
    Rect menuBoundingBox = menu->getBoundingBox();
    if (!menuBoundingBox.containsPoint(touchPoint))
    {
        this->removeChild(menu);
        removeTouchListener();
    }
    return true;
}
void %%%%%::monitor(Sprite* menu)
{
    auto touchListener = EventListenerTouchOneByOne::create();
    touchListener->onTouchBegan = CC_CALLBACK_2(%%%%%::onTouchBegan, this, menu);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, menu);
}
void %%%%%::removeTouchListener()
{
    _eventDispatcher->removeEventListenersForTarget(this);
}
*/

#endif // !__RESOURCE_H__