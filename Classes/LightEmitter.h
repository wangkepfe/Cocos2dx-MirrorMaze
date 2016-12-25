#ifndef __LIGHT_EMITTER_H__
#define __LIGHT_EMITTER_H__

#include "Block.h"

class LightEmitter : public Block
{
public:
	CREATE_FUNC(LightEmitter);
	virtual bool init();
private:
};
#endif