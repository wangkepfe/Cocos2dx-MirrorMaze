#ifndef __BLOCK_H__
#define __BLOCK_H__

#include "cocos2d.h"
#include "DefineAndEnum.h"

class Block : public cocos2d::Layer
{
public:
	CREATE_FUNC(Block);
	virtual bool init();
	virtual void update(float dt);

	void bindSprite(cocos2d::Sprite *sprite);
	void setBlockInfo(BlockInfo *info);
	void setChangeDetector(bool *change);
	cocos2d::Sprite* getSprite();
protected:
	BlockInfo *_info;
	BlockState _state;

	cocos2d::Sprite *_sprite;
	void rotateOnClick();

	bool *changeHappen;
	bool isRotating;
};
#endif