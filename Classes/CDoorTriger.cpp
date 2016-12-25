#include "CDoorTriger.h"

USING_NS_CC;

bool CDoorTriger::init()
{
	if (!cocos2d::Layer::init())
	{
		return false;
	}
	_sprite = nullptr;
	_state = Nostate;
	return true;
}

void CDoorTriger::update(float dt)
{
	if (_state != _info->state)
	{
		_state = _info->state;
		Vec2 pos = _sprite->getPosition();
		bindSprite(Sprite::create(getFileNameByType(_info->type, _info->state)));
		_sprite->setPosition(pos);

		if (_state == Receiving)
		{
			switch (_info->direc)
			{
			case down: _doorSprite->runAction(MoveTo::create(0.2f, pos + Vec2(GRID_SIZE, 0)));
				break;
			case left: _doorSprite->runAction(MoveTo::create(0.2f, pos - Vec2(0, GRID_SIZE)));
				break;
			case up:   _doorSprite->runAction(MoveTo::create(0.2f, pos - Vec2(GRID_SIZE, 0)));
				break;
			case right:_doorSprite->runAction(MoveTo::create(0.2f, pos + Vec2(0, GRID_SIZE)));
				break;
			default:
				break;
			}
		}
		else if (_state == Received)
		{
			_doorSprite->runAction(MoveTo::create(0.2f, pos));
		}
	}
}

void CDoorTriger::bindDoorSprite(cocos2d::Sprite *sprite)
{
	_doorSprite = sprite;
	switch (_info->direc)
	{
	case down:
		break;
	case left: _doorSprite->setRotation(90.f);
		break;
	case up:   _doorSprite->setRotation(180.f);
		break;
	case right:_doorSprite->setRotation(270.f);
		break;
	}
	_doorSprite->setPosition(_sprite->getPosition());
	this->addChild(_doorSprite);
}
