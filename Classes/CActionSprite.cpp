#include "CActionSprite.h"

CActionSprite::CActionSprite()
{
	CCSprite::initWithSpriteFrameName("hero_idle_00.png");
	init();
}

bool CActionSprite::init()
{
	this->setTag(ACTION_SPRITE_TAG);
	CCSprite::init();

	m_HitBox.actual = CCRectZero;
	m_HitBox.original = CCRectZero;
	m_AttackBox.actual = CCRectZero;
	m_AttackBox.original = CCRectZero;

	return true;
}

void CActionSprite::idle()
{
	if(m_ActionState != kActionStateIdle)
	{
		this->stopAllActions();
		this->runAction(m_IdleAction);
		m_ActionState = kActionStateIdle;
		m_Velocity = CCPointZero;
	}
}

void CActionSprite::attack()
{
	if(m_ActionState == kActionStateIdle ||
		m_ActionState == kActionStateAttack ||
		m_ActionState == kActionStateWalk)
	{
		this->stopAllActions();
		this->runAction(m_AttackAction);
		m_ActionState = kActionStateAttack;
	}
}

void CActionSprite::hurtWithDamage(float dmg)
{
	if(m_ActionState != kActionStateKnockedOut)
	{
		this->stopAllActions();
		this->runAction(m_HurtAction);
		m_ActionState = kActionStateHurt;
		m_HitPoints -= dmg;

		if(m_HitPoints <= 0.0f)
			this->knockout();
	}
}

void CActionSprite::knockout()
{
	this->stopAllActions();
	this->runAction(m_KnockedOutAction);
	m_HitPoints = 0.0f;
	m_ActionState = kActionStateKnockedOut;
}

void CActionSprite::walkWithDirection(CCPoint dir)
{
	if(m_ActionState == kActionStateIdle)
	{
		this->stopAllActions();
		this->runAction(m_WalkAction);
		m_ActionState = kActionStateWalk;
	}
	if(m_ActionState == kActionStateWalk)
	{
		m_Velocity = ccp(dir.x * m_WalkSpeed, dir.y * m_WalkSpeed);
	}
	if(m_Velocity.x >=0)
		this->setFlipX(false);
	else
		this->setFlipX(true);
}


void CActionSprite::update(float dt)
{
	
	if(m_ActionState == kActionStateWalk)
	{
		m_DesirePosition = ccpAdd(this->getPosition(), ccpMult(m_Velocity, dt));
	}
	CCSprite::update(dt);
}

BoundingBox CActionSprite::createBoundingBoxWithOrigin(CCPoint orgin, CCSize size)
{
	BoundingBox box;
	box.original.origin = orgin;
	box.original.size = size;
	box.actual.origin = ccpAdd(this->getPosition(),
		ccp(orgin.x, orgin.y));
	box.actual.size = size;

	return box;
}

void CActionSprite::transformBoxes()
{
	float xfac = this->isFlipX()?-1:1;
	float xfac2 = this->isFlipX()?1:0;
	float yfac = this->isFlipY()?-1:1;
	float yfac2 = this->isFlipY()?1:0;

	m_HitBox.actual.origin = ccpAdd(this->getPosition(),
		ccp(m_HitBox.original.origin.x*xfac - m_HitBox.original.size.width*xfac2,
		m_HitBox.original.origin.y*yfac - m_HitBox.original.size.height*yfac2));

	m_HitBox.actual.size = CCSizeMake(
		m_HitBox.original.size.width,
		m_HitBox.original.size.height);

	m_AttackBox.actual.origin = ccpAdd(this->getPosition(),
		ccp(m_AttackBox.original.origin.x*xfac - m_AttackBox.original.size.width*xfac2,
			m_AttackBox.original.origin.y*yfac - m_AttackBox.original.size.height*yfac2));

	m_AttackBox.actual.size = CCSizeMake(
		m_AttackBox.original.size.width,
		m_AttackBox.original.size.height);
}

void CActionSprite::setPosition(const CCPoint& pos)
{
	CCSprite::setPosition(pos);
	this->transformBoxes();
}