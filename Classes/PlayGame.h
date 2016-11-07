#ifndef __PlayGame_SCENE_H__
#define __PlayGame_SCENE_H__

#include "cocos2d.h"
#include "Setting.h"

class PlayGame : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
	Setting* setting;
    // a selector callback
    
    // implement the "static create()" method manually
    CREATE_FUNC(PlayGame);
};

#endif // __PlayGame_SCENE_H__
