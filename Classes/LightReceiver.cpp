#include "LightReceiver.h"

bool LightReceiver::init()
{
	if (!cocos2d::Layer::init())
	{	
		return false;
	}
	rotateOnClick();
	return true;
}
