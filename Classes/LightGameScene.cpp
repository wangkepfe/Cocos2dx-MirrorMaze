#include "LightGameScene.h"
#include "Block.h"
#include "ThemeScene.h"
#include "DefineAndEnum.h"
#include "CDoorTriger.h"
#include "LevelSelectScene.h"

USING_NS_CC;

Scene* LightGameScene::createScene(int param)
{
    auto scene = LightGameScene::create(param);
    return scene;
}

bool LightGameScene::init(int param)
{
    if ( !Scene::init() )
    {
        return false;
    }

	_level = param;
	b_win = false;
	b_already_win = false;

	auto cMap = new CMap;
	cMap->setMap(_level);
	auto map = cMap->getMap();

	auto light = Light::create();
	light->setMap(map);
	light->p_win = &b_win;
	addChild(light);

	drawBlock(map, light);

	createButtons();
	tutorialLine(0);

	this->scheduleUpdate();
    return true;
}

void LightGameScene::update(float dt)
{
	if (!b_already_win && b_win)
	{
		b_already_win = true;
		tutorialLine(1);
		std::string levelStr = CCUserDefault::sharedUserDefault()->getStringForKey("level");
		levelStr.at(_level) = '1';
		CCUserDefault::sharedUserDefault()->setStringForKey("level", levelStr);
		nextlevelButton->setEnabled(1);
		playSound("audio/do mi sol dol.mp3");
	}
}

LightGameScene * LightGameScene::create(int param)
{
	LightGameScene *pRet = new(std::nothrow) LightGameScene();
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

void LightGameScene::drawBlock(BlockInfo **map, Light *light)
{
	Size s = Director::getInstance()->getVisibleSize();
	int i, j;
	float x, y;

	for (i = 0; i < MAP_LENGTH; i++)
	{
		for (j = 0; j < MAP_HEIGHT; j++)
		{
			if (map[i][j].type != Nothing)
			{
				x = (i + 0.5f) * GRID_SIZE;
				y = s.height - ((j + 0.5f) * GRID_SIZE);

				if (map[i][j].type == DoorTriger)
				{
					auto doorTriger = CDoorTriger::create();
					doorTriger->setBlockInfo(&map[i][j]);
					const std::string fileName(getFileNameByType(map[i][j].type, map[i][j].state));
					doorTriger->bindSprite(Sprite::create(fileName));
					doorTriger->getSprite()->setPosition(x, y);
					const std::string fileName2(getFileNameByType(Door, Nostate));
					doorTriger->bindDoorSprite(Sprite::create(fileName2));	
					addChild(doorTriger);
				}
				else
				{
					auto block = Block::create();
					block->setBlockInfo(&map[i][j]);
					block->setChangeDetector(&light->_changeHappen);
					const std::string fileName(getFileNameByType(map[i][j].type, map[i][j].state));
					block->bindSprite(Sprite::create(fileName));
					block->getSprite()->setPosition(x, y);
					addChild(block);
				}
			}
		}
	}
}

void LightGameScene::createButtons()
{
	Size s = Director::getInstance()->getVisibleSize();

	auto select = MenuItemImage::create("image/ui1.png", "image/ui1_2.png", [=](Ref* ref) {
		this->unscheduleUpdate();
		Director::getInstance()->getEventDispatcher()->removeAllEventListeners();
		auto scene = LevelSelectScene::createScene();
		Director::getInstance()->replaceScene(TransitionSlideInT::create(1.f, scene));
	});
	auto restart = MenuItemImage::create("image/ui2.png", "image/ui2_2.png", [=](Ref* ref) {
		this->unscheduleUpdate();
		Director::getInstance()->getEventDispatcher()->removeAllEventListeners();
		auto scene = LightGameScene::createScene(_level);
		Director::getInstance()->replaceScene(TransitionSlideInT::create(1.f, scene));
	});
	nextlevelButton = MenuItemImage::create("image/ui3.png", "image/ui3_2.png","image/ui3_disable.png", [=](Ref* ref) {
		if (b_win)
		{
			//change scene		
			this->unscheduleUpdate();
			Director::getInstance()->getEventDispatcher()->removeAllEventListeners();

			if (isTutoringLevel(_level))
			{
				_level++;
				if (_level == 3) _level = 11;
				else if (_level == 15) _level = 21;
				else if (_level == 29) _level = 31;

				auto scene = LightGameScene::createScene(_level);
				Director::getInstance()->replaceScene(TransitionSlideInR::create(1.f, scene));				
			}
			else
			{
				_level++;
				if (_level == 3) _level = 11;
				else if (_level == 15) _level = 21;
				else if (_level == 29) _level = 31;

				_level += 1000;
				auto scene = ThemeScene::createScene(_level);
				Director::getInstance()->replaceScene(TransitionSlideInT::create(1.f, scene));
			}
			playSound("audio/do mi sol dol.mp3");
		}
	});

	nextlevelButton->setEnabled(0);

	select->setPosition(-60, 0);
	restart->setPosition(0, 0);
	nextlevelButton->setPosition(60, 0);

	auto buttons = Menu::create(select, restart, nextlevelButton, nullptr);
	buttons->setPosition(s.width * 0.8f, s.height * 0.2f);
	this->addChild(buttons);
}

bool LightGameScene::isTutoringLevel(int level)
{
	if (level == 1 ||
		level == 2 ||
		level == 13 ||
		level == 14 ||
		level == 25 ||
		level == 26 ||
		level == 27 ||
		level == 28)
		return true;

	return false;
}

void LightGameScene::tutorialLine(int situation)
{
	Size s = Director::getInstance()->getVisibleSize();
	float h = s.height;
	float w = s.width;
	Vec2 pos1(w * 0.75, h * 0.75);
	Vec2 pos2(w * 0.75, h * 0.33);
	TTFConfig ttfConfig("fonts/arial.ttf", 30);
	if (situation == 0)
	{
		if (_level == 1)
		{
			auto label = Label::createWithTTF(ttfConfig, "Try click the block");
			label->setPosition(pos1);
			this->addChild(label);
		}
		else if (_level == 2)
		{
			auto label = Label::createWithTTF(ttfConfig, "Mirror reflects light");
			label->setPosition(pos1);
			this->addChild(label);
		}
		else if (_level == 13)
		{
			auto label = Label::createWithTTF(ttfConfig, "                  Light can be dyed\nLight receiver only accepts light with right color");
			label->setPosition(w * 0.7, h * 0.45);
			this->addChild(label);
		}
		else if (_level == 14)
		{
			auto label = Label::createWithTTF(ttfConfig, "Color Formula");
			label->setPosition(pos1 + Vec2(0, h * 0.08));
			this->addChild(label);

			pos1 += Vec2(w * 0.05, 0);
			label = Label::createWithTTF(ttfConfig, "              +          =              ");
			label->setPosition(pos1);
			this->addChild(label);

			label = Label::createWithTTF(ttfConfig, "Yellow                              ");
			label->setPosition(pos1);
			label->setColor(Color3B::YELLOW);
			this->addChild(label);

			label = Label::createWithTTF(ttfConfig, "                  Red                  ");
			label->setPosition(pos1);
			label->setColor(Color3B::RED);
			this->addChild(label);

			label = Label::createWithTTF(ttfConfig, "                              Orange");
			label->setPosition(pos1);
			label->setColor(Color3B::ORANGE);
			this->addChild(label);

			Vec2 pos3 = pos1 - Vec2(0, h * 0.08);

			label = Label::createWithTTF(ttfConfig, "              +            =            ");
			label->setPosition(pos3);
			this->addChild(label);

			label = Label::createWithTTF(ttfConfig, "Yellow                              ");
			label->setPosition(pos3);
			label->setColor(Color3B::YELLOW);
			this->addChild(label);

			label = Label::createWithTTF(ttfConfig, "                  Blue                ");
			label->setPosition(pos3);
			label->setColor(Color3B::BLUE);
			this->addChild(label);

			label = Label::createWithTTF(ttfConfig, "                                Green");
			label->setPosition(pos3);
			label->setColor(Color3B::GREEN);
			this->addChild(label);

			Vec2 pos4 = pos3 - Vec2(0, h * 0.08);

			label = Label::createWithTTF(ttfConfig, "        +            =              ");
			label->setPosition(pos4);
			this->addChild(label);

			label = Label::createWithTTF(ttfConfig, "Red                                ");
			label->setPosition(pos4);
			label->setColor(Color3B::RED);
			this->addChild(label);

			label = Label::createWithTTF(ttfConfig, "            Blue                  ");
			label->setPosition(pos4);
			label->setColor(Color3B::BLUE);
			this->addChild(label);

			label = Label::createWithTTF(ttfConfig, "                          Purple");
			label->setPosition(pos4);
			label->setColor(Color3B::MAGENTA);
			this->addChild(label);
		}
		else if (_level == 21)
		{
			pos1 += Vec2(w * 0.05, 0);
			auto label = Label::createWithTTF(ttfConfig, "              +          =              ");
			label->setPosition(pos1);
			this->addChild(label);

			label = Label::createWithTTF(ttfConfig, "Yellow                              ");
			label->setPosition(pos1);
			label->setColor(Color3B::YELLOW);
			this->addChild(label);

			label = Label::createWithTTF(ttfConfig, "                  Red                  ");
			label->setPosition(pos1);
			label->setColor(Color3B::RED);
			this->addChild(label);

			label = Label::createWithTTF(ttfConfig, "                              Orange");
			label->setPosition(pos1);
			label->setColor(Color3B::ORANGE);
			this->addChild(label);
		}
		else if (_level == 22)
		{
			auto label = Label::createWithTTF(ttfConfig, "Some mirrors are\ntwo-side reflective");
			label->setPosition(pos1);
			this->addChild(label);
		}
		else if (_level == 23)
		{
			auto label = Label::createWithTTF(ttfConfig, "    Question  :");
			label->setPosition(pos1 + Vec2(0, h * 0.08));
			this->addChild(label);

			pos1 += Vec2(w * 0.05, 0);
			label = Label::createWithTTF(ttfConfig, "              +            =    ");
			label->setPosition(pos1);
			this->addChild(label);

			label = Label::createWithTTF(ttfConfig, "Yellow                      ");
			label->setPosition(pos1);
			label->setColor(Color3B::YELLOW);
			this->addChild(label);

			label = Label::createWithTTF(ttfConfig, "                  Blue        ");
			label->setPosition(pos1);
			label->setColor(Color3B::BLUE);
			this->addChild(label);

			label = Label::createWithTTF(ttfConfig, "                                ?");
			label->setPosition(pos1);
			label->setColor(Color3B::GREEN);
			this->addChild(label);
		}
		else if (_level == 24)
		{
			auto label = Label::createWithTTF(ttfConfig, "Color Hint");
			label->setPosition(pos1 + Vec2(0, h * 0.08));
			this->addChild(label);

			pos1 += Vec2(w * 0.05, 0);
			label = Label::createWithTTF(ttfConfig, "    +      =    ");
			label->setPosition(pos1);
			this->addChild(label);

			label = Label::createWithTTF(ttfConfig, "Y                ");
			label->setPosition(pos1);
			label->setColor(Color3B::YELLOW);
			this->addChild(label);

			label = Label::createWithTTF(ttfConfig, "        R        ");
			label->setPosition(pos1);
			label->setColor(Color3B::RED);
			this->addChild(label);

			label = Label::createWithTTF(ttfConfig, "                O");
			label->setPosition(pos1);
			label->setColor(Color3B::ORANGE);
			this->addChild(label);

			Vec2 pos3 = pos1 - Vec2(0, h * 0.08);

			label = Label::createWithTTF(ttfConfig, "    +      =    ");
			label->setPosition(pos3);
			this->addChild(label);

			label = Label::createWithTTF(ttfConfig, "Y                ");
			label->setPosition(pos3);
			label->setColor(Color3B::YELLOW);
			this->addChild(label);

			label = Label::createWithTTF(ttfConfig, "        B        ");
			label->setPosition(pos3);
			label->setColor(Color3B::BLUE);
			this->addChild(label);

			label = Label::createWithTTF(ttfConfig, "                G");
			label->setPosition(pos3);
			label->setColor(Color3B::GREEN);
			this->addChild(label);
		}
		else if (_level == 25)
		{
			auto label = Label::createWithTTF(ttfConfig, "     This triangle mirror divides light\nEach sublight has the half brightness");
			label->setPosition(pos1);
			this->addChild(label);
		}
		else if (_level == 26)
		{
			auto label = Label::createWithTTF(ttfConfig, "This light register stores light\n\nIts output color can be changed\nby receiving different color light");
			label->setPosition(pos1 - Vec2(0, h * 0.05));
			this->addChild(label);
		}
		else if (_level == 27)
		{
			auto label = Label::createWithTTF(ttfConfig, "Sometimes it is surprising");
			label->setPosition(pos1);
			this->addChild(label);
		}
		else if (_level == 28)
		{
			auto label = Label::createWithTTF(ttfConfig, "This door with triger will open\nwhen the triger receives light");
			label->setPosition(pos1);
			this->addChild(label);
		}
	}
	else if (situation == 1)
	{
		if (_level == 1)
		{
			auto label = Label::createWithTTF(ttfConfig, "        Good job!\nClick yellow triangle to next level");
			label->setPosition(pos2);
			this->addChild(label);
		}
		else if (_level == 2)
		{
			auto label = Label::createWithTTF(ttfConfig, "          Good job!");
			label->setPosition(pos2);
			this->addChild(label);
		}
	}
}