#include "GameOver.h"
#include "IntroScene.h"
#include "PlayGame.h"
#include "UI/CocosGUI.h"
USING_NS_CC;

Scene* GameOver::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = GameOver::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool GameOver::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto overPanel = Sprite::create("gameover.jpg");
	overPanel->setPosition(visibleSize / 2);
	this->addChild(overPanel);

	auto menuPlay = ui::Button::create("button.jpg");
	menuPlay->setPosition(Vec2(origin.x + visibleSize.width - menuPlay->getContentSize().width,
		origin.y + menuPlay->getContentSize().height));
	menuPlay->setTitleText("Replay");
	menuPlay->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type)
	{
		switch (type)
		{
		     case ui::Widget::TouchEventType::BEGAN:
				break;
		     case ui::Widget::TouchEventType::ENDED:
				 auto introscene = IntroScene::createScene();
				 Director::getInstance()->replaceScene(introscene);
				break;
		}
	});
	this->addChild(menuPlay);



    return true;
}
