#ifndef __RESOURCE_H__
#define __RESOURCE_H__

//sys_menu
static const char SysmenuBackground[] = "sys_menu_17.png";
static const char SysmenuSelection[] = "sys_menu_1.png";
static const char SysmenuButton1On[] = "sys_menu_2_1.png";
static const char SysmenuButton1Down[] = "sys_menu_2_2.png";
static const char SysmenuButton2On[] = "sys_menu_3_1.png";
static const char SysmenuButton2Down[] = "sys_menu_3_2.png";
static const char SysmenuButton3On[] = "sys_menu_4_1.png";
static const char SysmenuButton3Down[] = "sys_menu_4_2.png";
static const char SysmenuSecondSelection[] = "sys_menu_5.png";
static const char SysmenuButton4On[] = "sys_menu_6_1.png";
static const char SysmenuButton4Down[] = "sys_menu_6_2.png";
static const char StartScriptOn[] = "sys_menu_7_1.png";
static const char StartScriptDown[] = "sys_menu_7_2.png";
static const char NewGameScriptOn[] = "sys_menu_8_1.png";
static const char NewGameScriptDown[] = "sys_menu_8_2.png";
static const char SaveFile1ScriptOn[] = "sys_menu_9_1.png";
static const char SaveFile1ScriptDown[] = "sys_menu_9_2.png";
static const char SaveFile2ScriptOn[] = "sys_menu_10_1.png";
static const char SaveFile2ScriptDown[] = "sys_menu_10_2.png";
static const char SaveFile3ScriptOn[] = "sys_menu_11_1.png";
static const char SaveFile3ScriptDown[] = "sys_menu_11_2.png";
static const char OptionScriptOn[] = "sys_menu_12_1.png";
static const char OptionScriptDown[] = "sys_menu_12_2.png";
static const char ProductScriptOn[] = "sys_menu_13_1.png";
static const char ProductScriptDown[] = "sys_menu_13_2.png";
static const char LargeFrame[] = "sys_menu_15.png";
static const char SmallFrame[] = "sys_menu_14.png";
static const char ExitScriptOn[] = "sys_menu_16_1.png";
static const char ExitScriptDown[] = "sys_menu_16_2.png";



#define MONITOR_H()  \
private:\
	bool onTouchBegan(cocos2d::Touch * touch, cocos2d::Event * event, cocos2d::Sprite * menu);\
	void monitor(cocos2d::Sprite * menu);\
	void removeTouchListener(); \


#define MONITOR_CPP(x)\
bool x::onTouchBegan(Touch* touch, Event* event, Sprite* menu)\
{\
    Vec2 touchPoint = this->convertToNodeSpace(touch->getLocation());\
    Rect menuBoundingBox = menu->getBoundingBox();\
    if (!menuBoundingBox.containsPoint(touchPoint))\
    {\
        this->removeChild(menu);\
        removeTouchListener();\
    }\
    return true;\
}\
void x::monitor(Sprite* menu)\
{\
    auto touchListener = EventListenerTouchOneByOne::create();\
    touchListener->onTouchBegan = CC_CALLBACK_2(x::onTouchBegan, this, menu);\
    _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, menu);\
}\
void x::removeTouchListener()\
{\
    _eventDispatcher->removeEventListenersForTarget(this);\
}\

#endif // !__RESOURCE_H__
//¼àÊÓÆ÷µÄÄ£°å
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