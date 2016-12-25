#include "LevelSelectScene.h"
#include "LightGameScene.h"

USING_NS_CC;

cocos2d::Scene * LevelSelectScene::createScene()
{
	return LevelSelectScene::create();
}

bool LevelSelectScene::init()
{
	if (!Scene::init())
	{
		return false;
	}

	Size s = Director::getInstance()->getVisibleSize();
	float h = s.height;
	float w = s.width;

	int i, j;
	std::string a;
	TTFConfig ttfConfig("fonts/arial.ttf", 50);

	int highestLevel = 0;
	std::string levelStr = CCUserDefault::sharedUserDefault()->getStringForKey("level");

	for (i = levelStr.size() - 1; i >= 0; i--) //find highest level in order to calcu how many levels to draw
	{
		if (levelStr.at(i) == '1')
		{
			highestLevel = i;
			break;
		}
	}

	if (highestLevel == 2 ||
		highestLevel == 14 ||
		highestLevel == 28 ||
		highestLevel == 35 ||
		highestLevel == 46 ||
		highestLevel == 59)
	{
		highestLevel += 10;
	}


	auto menu = Menu::create();
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu);

	for (i = 0; i <= highestLevel / 10; i++) // draw levels
	{
		Vec2 labelPos(w * 0.1f, h - h * 0.14f * (i + 1));
		a = "LEVEL " + std::to_string(i);
		auto label = Label::createWithTTF(ttfConfig, a);
		label->setPosition(labelPos);
		this->addChild(label);

		for (j = 1; j <= 9; j++)
		{
			if ((i == 0 && j <= 2) || //all the levels(including tutorial)
				(i == 1 && j <= 4) ||
				(i == 2 && j <= 8) ||
				(i == 3 && j <= 5) ||
				(i == 4 && j <= 6) ||
				(i == 5 && j <= 9))
			{
				Vec2 imagePos = labelPos + Vec2(w * 0.03 + w * 0.1f * j, 0);
				if (levelStr.at(i * 10 + j) == '1')
				{
					auto menuItem = MenuItemImage::create("image/level2.png", "image/level2.png", [=](Ref *ref)
					{
						auto scene = LightGameScene::createScene(i * 10 + j);
						Director::getInstance()->replaceScene(TransitionSlideInB::create(1.f, scene));
					});
					menuItem->setPosition(imagePos);
					menu->addChild(menuItem);
				}
				else
				{
					auto menuItem = MenuItemImage::create("image/level1.png", "image/level1.png", [=](Ref *ref)
					{
						auto scene = LightGameScene::createScene(i * 10 + j);
						Director::getInstance()->replaceScene(TransitionSlideInB::create(1.f, scene));
					});
					menuItem->setPosition(imagePos);
					menu->addChild(menuItem);
				}
				a = std::to_string(j);
				auto label = Label::createWithTTF(ttfConfig, a);
				label->setPosition(imagePos);
				this->addChild(label);
			}
		}
	}

	return true;
}
