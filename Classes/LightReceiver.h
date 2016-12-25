#ifndef __LIGHT_RECEIVER_H__
#define __LIGHT_RECEIVER_H__

#include "Block.h"

class LightReceiver : public Block
{
public:
	CREATE_FUNC(LightReceiver);
	virtual bool init();
private:
};
#endif