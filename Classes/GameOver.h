#ifndef __GameOver_SCENE_H__
#define __GameOver_SCENE_H__

#include "cocos2d.h"

class GameOver : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene(int score);
    virtual bool init();
	void addScore(int score);
	int score;
    // a selector callback
    // implement the "static create()" method manually
    CREATE_FUNC(GameOver);
};

#endif // __GameOver_SCENE_H__
