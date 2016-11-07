#include "Setting.h"
#include "IntroScene.h"
#include "UI/CocosGUI.h"
#include "SimpleAudioEngine.h"
#include "PlayGame.h"
USING_NS_CC;
using namespace ui;

bool Setting::init()
{
	if (!Layer::init()){
		return false;
	}
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto setting = Button::create("setting.png");
	setting->setPosition(Vec2(origin.x + visibleSize.width - setting->getContentSize().width,
		origin.y + visibleSize.height - setting->getContentSize().height));
	this->addChild(setting);

	auto checkbox = CheckBox::create("checkbox.png", "checkbox1.png");
	checkbox->addTouchEventListener([](Ref *sender, Widget::TouchEventType type)
	{
		switch (type)
		{
		case::Widget::TouchEventType::ENDED:
			CocosDenshion::SimpleAudioEngine::getInstance()->stopAllEffects();
		}
	});
	return true;
}