#ifndef _ACTION_SPRITE_H_
#define _ACTION_SPRITE_H_

#include "cocos2d.h"
using namespace cocos2d;

#include "Defines.h"

class CActionSprite : public CCSprite
{
public:
	CActionSprite();
	virtual bool init();

	void idle();
	void attack();
	void hurtWithDamage(float dmg);
	void knockout();
	void walkWithDirection(CCPoint dir);

	virtual void update(float dt);

//protected:
	CCAction* m_IdleAction;
	CCAction* m_AttackAction;
	CCAction* m_WalkAction;
	CCAction* m_HurtAction;
	CCAction* m_KnockedOutAction;

	ActionState m_ActionState;

	float m_WalkSpeed;
	float m_HitPoints;
	float m_Damage;

	CCPoint m_Velocity;
	CCPoint m_DesirePosition;

	float m_CenterToSide;
	float m_CenterToBottom;

	BoundingBox m_HitBox;
	BoundingBox m_AttackBox;

	BoundingBox createBoundingBoxWithOrigin(CCPoint origin, CCSize size);

	void transformBoxes();
	void setPosition(const CCPoint& pos);
};
#endif