#ifndef _DEFINE_H_
#define _DEFINE_H_

#include "cocos2d.h"
using namespace cocos2d;

#define SCREENSIZE CCDirector::sharedDirector()->getWinSize()
#define SCREENCENTER cpp(SCREENSIZE.width/2, SCREENSIZE.height/2)

inline float GetMin(float a, float b)
{
	return a<b?a:b;
}

inline float GetMax(float a, float b)
{
	return a>b?a:b;
}

enum ActionState {
	kActionStateNone = 0,
	kActionStateIdle,
	kActionStateAttack,
	kActionStateWalk,
	kActionStateHurt,
	kActionStateKnockedOut,
};

typedef struct _BoundingBox
{
	CCRect actual;
	CCRect original;
} BoundingBox;

#define ACTION_SPRITE_TAG 100

#endif