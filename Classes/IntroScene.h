#ifndef __IntroScene_SCENE_H__
#define __IntroScene_SCENE_H__

#include "cocos2d.h"

class IntroScene : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    // a selector callback
	void IntroScene::update(float);
	bool IntroScene::OnTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event);
	void IntroScene::stopFly(float);
    // implement the "static create()" method manually
    CREATE_FUNC(IntroScene);
private:
	void IntroScene::CreatPipe(float);
	cocos2d::Label *label;
	int score = 0;
	cocos2d::Sprite *bird;
	cocos2d::PhysicsWorld *world;
	bool isFalling = true;
	void setPhysicWorld(cocos2d::PhysicsWorld *m_world)
	{
		world = m_world;
	}
};

#endif // __IntroScene_SCENE_H__
