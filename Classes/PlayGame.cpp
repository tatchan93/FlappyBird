#include "PlayGame.h"
#include "IntroScene.h"
#include "UI/CocosGUI.h"
USING_NS_CC;
using namespace ui;
Scene* PlayGame::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = PlayGame::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool PlayGame::init()
{
    ///////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto anhnen = Sprite::create("anhnen.jpg");
	anhnen->setPosition(visibleSize / 2);
	anhnen->setScale(1.5);
	this->addChild(anhnen);

	auto label = Label::createWithTTF("Con Chim Bay", "fonts/Marker Felt.ttf", 60);
	label->setPosition(Vec2(360, 400));
	label->setColor(Color3B::ORANGE);
	this->addChild(label);

	auto playgame = Button::create("bt1.png");
	playgame->setPosition(visibleSize/2);
	playgame->addTouchEventListener([](Ref *sender, Widget::TouchEventType type)
	{
		switch (type)
		{
		case Widget::TouchEventType::BEGAN:
			break;
		case Widget::TouchEventType::ENDED:
			auto scene = IntroScene::createScene();
			Director::getInstance()->replaceScene(scene);
			break;
		}
	});
	this->addChild(playgame);
    return true;
}

