#ifndef __C_MAP_H__
#define __C_MAP_H__

#include "cocos2d.h"
#include "DefineAndEnum.h"

class CMap
{
public:
	void setMap(int index);
	BlockInfo **getMap();
private:
	BlockInfo **map;
};
#endif