#ifndef _HERO_H_
#define _HERO_H_

#include "CActionSprite.h"

class Hero : public CActionSprite
{
public:
	Hero();
	bool init();
};

#endif