#include "Block.h"
#include "CAudio.h"

USING_NS_CC;

bool Block::init()
{
	if (!cocos2d::Layer::init())
	{
		return false;
	}
	_sprite = nullptr;
	_state = Nostate;
	return true;
}

void Block::update(float dt)
{
	if (_state != _info->state)
	{
		_state = _info->state;
		Vec2 pos = _sprite->getPosition();
		bindSprite(Sprite::create(getFileNameByType(_info->type, _info->state)));
		_sprite->setPosition(pos);

		if (_state == Received)
			playSound("audio/re mi sol.mp3");
	}
}

void Block::bindSprite(cocos2d::Sprite * sprite)
{
	if(_sprite != nullptr)
		_sprite->removeFromParent();

	_sprite = sprite;
	switch (_info->direc)
	{
	case down:
		break;
	case left: _sprite->setRotation(90.f);
		break;
	case up:   _sprite->setRotation(180.f);
		break;
	case right:_sprite->setRotation(270.f);
		break;
	}
	this->addChild(_sprite);
}

void Block::setBlockInfo(BlockInfo *info)
{
	_info = info;
	if (isReceiver(_info->type) || _info->type == Register || _info->type == DoorTriger)
	{
		this->scheduleUpdate();
	}
	if (_info->type == FixedMirror || _info->type == Door || _info->type == DoorTriger);
	else
		rotateOnClick();
}

void Block::setChangeDetector(bool *change)
{
	changeHappen = change;
}

cocos2d::Sprite* Block::getSprite()
{
	return _sprite;
}

void Block::rotateOnClick()
{
	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);

	listener->onTouchBegan = [&](Touch* touch, Event* event)
	{
		if (!isRotating)
		{
			Vec2 p = touch->getLocation();
			Rect rect = _sprite->getBoundingBox();

			if (rect.containsPoint(p))
			{
				return true; // to indicate that we have consumed it.
			}
		}

		return false; // we did not consume this event, pass thru.
	};

	listener->onTouchEnded = [=](Touch* touch, Event* event)
	{
		switch (_info->direc)
		{
		case down: _info->direc = left; playSound("audio/do.mp3");
			break;
		case left: _info->direc = up; playSound("audio/re.mp3");
			break;
		case up:   _info->direc = right; playSound("audio/sol.mp3");
			break;
		case right:_info->direc = down; playSound("audio/dol.mp3");
			break;
		}
		isRotating = 1;
		_sprite->runAction(Sequence::create(RotateBy::create(0.2f, 90.f), CallFunc::create([=] {
			*changeHappen = 1;
			isRotating = 0;
		}), nullptr));
		
	};
	Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(listener, 30);
}