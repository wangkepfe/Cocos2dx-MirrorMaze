#ifndef __DOOR_TRIGER_H__
#define __DOOR_TRIGER_H__

#include "cocos2d.h"
#include "DefineAndEnum.h"
#include "Block.h"

class CDoorTriger : public Block
{
public:
	CREATE_FUNC(CDoorTriger);
	virtual bool init();
	virtual void update(float dt);
	void bindDoorSprite(cocos2d::Sprite *sprite);
private:
	cocos2d::Sprite *_doorSprite;
};

#endif