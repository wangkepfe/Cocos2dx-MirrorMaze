#ifndef __THEME_SCENE_H__
#define __THEME_SCENE_H__

#include "cocos2d.h"

class ThemeScene : public cocos2d::Scene
{
public:
	static ThemeScene * create(int param);
	static cocos2d::Scene* createScene(int param);

	ThemeScene() {};
	virtual ~ThemeScene() {};

	virtual bool init(int param);
private:
};

#endif