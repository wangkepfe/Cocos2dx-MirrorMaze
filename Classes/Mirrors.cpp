#include "Mirrors.h"

bool Mirror1::init()
{
	if (!cocos2d::Layer::init())
	{
		return false;
	}
	rotateOnClick();
	return true;
}
