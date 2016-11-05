#include "GameOver.h"
#include "IntroScene.h"
#include "PlayGame.h"
#include "UI/CocosGUI.h"
USING_NS_CC;

Scene* GameOver::createScene(int score)
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = GameOver::create();
	layer->score = score;
	layer->addScore(layer->score);
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
	menuPlay->setPosition(Vec2(origin.x + menuPlay->getContentSize().width, origin.y + menuPlay->getContentSize().height));
	menuPlay->setTitleText("Menu");
	menuPlay->setScale(1.5);
	menuPlay->addTouchEventListener([](Ref* sender, ui::Widget::TouchEventType type)
	{
		switch (type)
		{
		case ui::Widget::TouchEventType::BEGAN:
			break;
		case ui::Widget::TouchEventType::ENDED:
			auto playscene = PlayGame::createScene();
			Director::getInstance()->replaceScene(playscene);
			break;
		}
	});
	this->addChild(menuPlay);

	auto replay = ui::Button::create("button.jpg");
	replay->setPosition(Vec2(origin.x + visibleSize.width - replay->getContentSize().width,
		origin.y + replay->getContentSize().height));
	replay->setTitleText("Replay");
	replay->setScale(1.5);
	replay->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type)
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
	this->addChild(replay);


    return true;
}

void GameOver::addScore(int score){
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	__String *teapScore = __String::createWithFormat("%i", score);
	auto label = Label::createWithTTF(teapScore->getCString(), "fonts/Marker Felt.ttf", visibleSize.height*0.1);
	label->setPosition(Vec2(origin.x + label->getContentSize().width * 2, origin.y + visibleSize.height - label->getContentSize().height));
	label->setColor(Color3B::RED);
	this->addChild(label);

}
