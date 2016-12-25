#ifndef __LEVEL_SELECT_SCENE_H__
#define __LEVEL_SELECT_SCENE_H__

#include "cocos2d.h"

class LevelSelectScene : public cocos2d::Scene
{
public:
	CREATE_FUNC(LevelSelectScene);

	static cocos2d::Scene* createScene();

	LevelSelectScene() {};
	virtual ~LevelSelectScene() {};

	virtual bool init() override;
};

#endif