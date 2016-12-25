#include "ThemeScene.h"
#include "LightGameScene.h"

USING_NS_CC;
using namespace experimental;

cocos2d::Scene * ThemeScene::createScene(int param)
{
	return ThemeScene::create(param);
}

bool ThemeScene::init(int param)
{
	if (!Scene::init())
	{
		return false;
	}

	std::string levelStr;
	bool bReset = 0;

	if (bReset)
	{
		for (int i = 0; i < 60; i++)
			levelStr.push_back('0');
		CCUserDefault::sharedUserDefault()->setStringForKey("level", levelStr);
	}
	else
		levelStr = CCUserDefault::sharedUserDefault()->getStringForKey("level");

	Size s = Director::getInstance()->getVisibleSize();
	bool lightShow = false;

	if (param > 1000)
	{
		param -= 1000;
		lightShow = true;
		auto sprite = Sprite::create("image/theme2.png");
		sprite->setPosition(s.width * 0.5f, s.height * 0.5f);
		addChild(sprite);	
	}
	else // first start the game
	{
		auto sprite = Sprite::create("image/theme.png");
		sprite->setPosition(s.width * 0.5f, s.height * 0.5f);
		addChild(sprite);

		playSound("audio/Julys Night.mp3", true, 0.5f);
	}

	char fileName[40];
	Sprite * lastWindow = nullptr;
	int level;
	for (level = 0; level < levelStr.size(); level++)
	{
		if (levelStr.at(level) == '1' &&
			((level>=11 && level<=12) || // all the windows (excluding tutorial)
				(level >= 21 && level <= 24) || 
				(level >= 31 && level <= 35) || 
				(level >= 41 && level <= 46) || 
				(level >= 51 && level <= 59)))
		{
			sprintf(fileName, "image/window%d.png", level);
			auto sprite = Sprite::create(fileName);
			sprite->setPosition(s.width * 0.5f, s.height * 0.5f);
			addChild(sprite);
			lastWindow = sprite;
			if (level >= param)
				lightShow = false;
		}
	}

	if (lightShow)
	{
		lastWindow->setOpacity(0);
		lastWindow->runAction(FadeIn::create(2.f));
	}
	
	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);
	listener->onTouchBegan = [&](Touch* touch, Event* event)
	{	
		return true;
	};

	listener->onTouchEnded = [=](Touch* touch, Event* event)
	{
		Director::getInstance()->getEventDispatcher()->removeAllEventListeners();
		auto scene = LightGameScene::createScene(param);
		Director::getInstance()->replaceScene(TransitionSlideInB::create(1.f, scene));
		playSound("audio/do mi sol dol.mp3");
	};
	Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(listener, 30);

	return true;
}

ThemeScene * ThemeScene::create(int param)
{
	ThemeScene *pRet = new(std::nothrow) ThemeScene();
	if (pRet && pRet->init(param))
	{
		pRet->autorelease();
		return pRet;
	}
	else
	{
		delete pRet;
		pRet = nullptr;
		return nullptr;
	}
}
