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

// 防御塔数据映射
std::map<int, TowerData> towerDataMap;

// 初始化防御塔数据映射
void initializeTowerData() {
    // 添加不同ID的防御塔数据
//防御塔数据
//ID: 1
//name:瓶子塔 
    towerDataMap[1] = { {0, 100, 150, 200}, {0, 0.5f, 0.5f, 0.5f}, false, 100, 100, {0, 0, 150, 200}, {0, 60, 150, 270},
    {{"","",""}, {"ID1_22.PNG","ID1_13.PNG","ID1_18.PNG"},
                 {"ID1_15.PNG","ID1_12.PNG","ID1_8.PNG"},
                 { "ID1_5.PNG","ID1_3.PNG","ID1_6.PNG"}},
    {{"","",""},{"ID1_0.PNG","ID1_2.PNG","ID1_21.PNG"},
                {"ID1_7.PNG","ID1_9.PNG","ID1_19.PNG"},
                {"ID1_16.PNG","ID1_14.PNG","ID1_17.PNG" }},
                       {"ID1_10.PNG","ID1_20.PNG"} };
 
//防御塔数据
//ID: 3
//name:星星塔
    towerDataMap[3] = { {0, 120, 180, 240}, {0, 0.7f, 0.7f, 0.7f}, false, 100, 160, {0, 0, 240, 320}, {0, 96, 240, 432} };

//防御塔数据
//ID: 4
//name:风扇塔
    towerDataMap[4] = { {0, 160, 240, 320}, {0, 0.7f, 0.7f, 0.6f}, true, 100, 160, {0, 0, 240, 320}, {0, 96, 240, 432} };

//防御塔数据
//ID: 5
//name:魔法塔
    towerDataMap[5] = { {0, 200, 300, 400}, {0, 0.7f, 0.6f, 0.5f}, false, 100, 160, {0, 0, 240, 320}, {0, 96, 240, 432} };
}

// 根据ID获取防御塔数据
const TowerData& getTowerDataById(int id) {
    auto it = towerDataMap.find(id);
    if (it != towerDataMap.end()) {
        return it->second;
    }
    else {
        // 处理ID不存在的情况，这里可以抛出异常或者返回一个默认值
        // 这里返回一个默认值，你可以根据实际情况调整
        static TowerData defaultData = { {0, 0, 0, 0}, {0, 0, 0, 0}, false, 0, 0, {0, 0, 0, 0}, {0, 0, 0, 0} };
        return defaultData;
    }
}



//放一些可能会用到的模板

/*
auto dead = CallFunc::create([=]() {
    // 回调函数中执行销毁精灵的操作
    p->removeFromParentAndCleanup(true);
    });
*/

//监视器的模板
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