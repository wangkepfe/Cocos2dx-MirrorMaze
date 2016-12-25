#include "LightEmitter.h"

bool LightEmitter::init()
{
	if (!cocos2d::Layer::init())
	{	
		return false;
	}
	rotateOnClick();
	return true;
}
