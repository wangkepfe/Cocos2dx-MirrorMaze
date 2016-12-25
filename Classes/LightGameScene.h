#ifndef __LIGHT_GAME_SCENE_H__
#define __LIGHT_GAME_SCENE_H__

#include "cocos2d.h"
#include "Light.h"
#include "CMap.h"
#include "CAudio.h"


class LightGameScene : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene(int param);

    virtual bool init(int param);
	virtual void update(float dt);
	static LightGameScene * create(int param);

	LightGameScene() {};
	virtual ~LightGameScene() {};
private:
	bool b_win, b_already_win;
	int _level;

	void drawBlock(BlockInfo **map, Light *light);
	void createButtons();

	bool isTutoringLevel(int level);

	void tutorialLine(int situation);

	cocos2d::MenuItemImage *nextlevelButton;
};

#endif
