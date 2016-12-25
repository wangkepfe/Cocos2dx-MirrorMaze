#ifndef __MIRRORS_H__
#define __MIRRORS_H__

#include "Block.h"

class Mirror1 : public Block
{
public:
	CREATE_FUNC(Mirror1);
	virtual bool init();
};

#endif