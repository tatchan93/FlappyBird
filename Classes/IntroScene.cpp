#include "IntroScene.h"
#include "GameOver.h"
USING_NS_CC;
using namespace std;
Scene* IntroScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::createWithPhysics();
	scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
	scene->getPhysicsWorld()->setGravity(Vec2(0,0));
    // 'layer' is an autorelease object
    auto layer = IntroScene::create();
	layer->setPhysicWorld(scene->getPhysicsWorld());
    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool IntroScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }

	gameScore = 0;
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

	__String *teapScore = __String::createWithFormat("%i", score);
	label = Label::createWithTTF(teapScore->getCString(), "fonts/Marker Felt.ttf", visibleSize.height*0.1);
	label->setPosition(Vec2(origin.x + label->getContentSize().width, origin.y + visibleSize.height - label->getContentSize().height));
	label->setColor(Color3B::RED);
	this->addChild(label);

	bird = Sprite::create("chim.png");
	bird->setPosition(visibleSize / 2);
	auto birdPhysic = PhysicsBody::createBox(bird->getContentSize());
	birdPhysic->setContactTestBitmask(true);
	birdPhysic->setCollisionBitmask(4);
	bird->setPhysicsBody(birdPhysic);
	this->addChild(bird);

	auto edgeBody = PhysicsBody::createEdgeBox(visibleSize, PHYSICSBODY_MATERIAL_DEFAULT, 5);
	edgeBody->setCollisionBitmask(2);
	edgeBody->setContactTestBitmask(true);
	auto edgeNode = Node::create();
	edgeNode->setPosition(visibleSize / 2);
	edgeNode->setPhysicsBody(edgeBody);
	this->addChild(edgeNode);

	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->onTouchBegan = CC_CALLBACK_2(IntroScene::OnTouchBegan, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);

	auto contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = CC_CALLBACK_1(IntroScene::OnContactBegan, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);

	this->scheduleUpdate();
	this->schedule(schedule_selector(IntroScene::CreatPipe), 0.0025*visibleSize.width);
    
    return true;
}

void IntroScene::CreatPipe(float dt)
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	auto topPipe = Sprite::create("ong.png");
	auto botPipe = Sprite::create("ong1.png");

	auto topPhysic = PhysicsBody::createBox(topPipe->getContentSize());
	topPhysic->setCollisionBitmask(2);
	topPhysic->setContactTestBitmask(true);
	topPipe->setPhysicsBody(topPhysic);

	auto botPhysic = PhysicsBody::createBox(botPipe->getContentSize());
	botPhysic->setCollisionBitmask(2);
	botPhysic->setContactTestBitmask(true);
	botPipe->setPhysicsBody(botPhysic);

	topPhysic->setDynamic(false);
	botPhysic->setDynamic(false);

	auto random = CCRANDOM_0_1();
	if (random < 0.50)
	{
		random = 0.50;
	}
	else
	{
		if (random > 0.75)
		{
			random = 0.75;
		}
	}

	auto topPipePosition = visibleSize.height*random + topPipe->getContentSize().height / 2;
	topPipe->setPosition(Vec2(visibleSize.width + topPipe->getContentSize().width, topPipePosition));
	botPipe->setPosition(Vec2(topPipe->getPositionX(), topPipePosition - bird->getContentSize().height * 4
		- topPipe->getContentSize().height));

	this->addChild(topPipe);
	this->addChild(botPipe);

	auto topMove = MoveBy::create(0.01*visibleSize.width, Vec2(-visibleSize.width*1.5, 0));
	auto botMove = MoveBy::create(0.01*visibleSize.width, Vec2(-visibleSize.width*1.5, 0));
	topPipe->runAction(topMove);
	botPipe->runAction(botMove);

	auto pointNode = Node::create();
	pointNode->setPosition(Vec2(topPipe->getPositionX(), topPipe->getPositionY() - topPipe->getContentSize().height / 2
		- (bird->getContentSize().height * 4) / 2));
	auto nodePhysic = PhysicsBody::createBox(Size(1, bird->getContentSize().height*4));
	nodePhysic->setCollisionBitmask(3);
	nodePhysic->setContactTestBitmask(true);
	nodePhysic->setDynamic(false);
	pointNode->setPhysicsBody(nodePhysic);

	auto nodeMove = MoveBy::create(0.01*visibleSize.width, Vec2(-visibleSize.width*1.5, 0));
	pointNode->runAction(nodeMove);
	this->addChild(pointNode);
}

bool IntroScene::OnContactBegan(const cocos2d::PhysicsContact &contact)
{
	PhysicsBody *shapeA  = contact.getShapeA()->getBody();
	PhysicsBody *shapeB = contact.getShapeB()->getBody();
	if (shapeA->getCollisionBitmask() == 3 && shapeB->getCollisionBitmask() == 4 ||
		shapeA->getCollisionBitmask() == 4 && shapeB->getCollisionBitmask() == 3)
	{
		++score;
		__String *teapScore = __String::createWithFormat("%i", score);
		label->setString(teapScore->getCString());
		gameScore = score; 
	}
	else
	{
		if (shapeA->getCollisionBitmask() == 4 && shapeB->getCollisionBitmask() == 2 ||
			shapeA->getCollisionBitmask() == 2 && shapeB->getCollisionBitmask() == 4);
		{
			auto gameoverScene = GameOver::createScene();
			Director::getInstance()->replaceScene(gameoverScene);
		}
	}
	return true;
}

void IntroScene::update(float dt)
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	if (isFalling == true)
	{
		bird->setPosition(visibleSize.width / 2, bird->getPositionY() - visibleSize.height*0.0025);
	}
	else
	{
		bird->setPosition(visibleSize.width / 2, bird->getPositionY() + visibleSize.height*0.05);
	}
}

void IntroScene::stopFly(float dt)
{
	isFalling = true;
}

bool IntroScene::OnTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event)
{
	isFalling = false;
	this->schedule(schedule_selector(IntroScene::stopFly, 0.5f));
	return true;
}

