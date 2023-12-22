#ifndef __RESOURCE_H__
#define __RESOURCE_H__

//放一些可能会用到的模板

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