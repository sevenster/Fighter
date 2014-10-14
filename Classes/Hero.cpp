#include "Hero.h"

Hero::Hero()
{
	CCSpriteFrameCache* cache = CCSpriteFrameCache::sharedSpriteFrameCache();
	CCSprite::createWithSpriteFrameName("hero_idle_00.png");
	this->retain();

	char str[64]={0};
	CCArray* animFrames = new CCArray(10);

	//IdleAction
	for (int i=0; i<6; ++i)
	{
		sprintf(str, "hero_idle_%02d.png", i);
		CCSpriteFrame* frame = cache->spriteFrameByName(str);
		animFrames->addObject(frame);
	}

	CCAnimation* idleAnimation = CCAnimation::createWithSpriteFrames(animFrames,1.0f/12.0f);
	m_IdleAction = CCRepeatForever::create(CCAnimate::create(idleAnimation));
	m_IdleAction->retain();
	animFrames->removeAllObjects();

	//Attack
	for(int i=0; i<3; ++i)
	{
		sprintf(str, "hero_attack_00_%02d.png", i);
		CCSpriteFrame* frame = cache->spriteFrameByName(str);
		animFrames->addObject(frame);
	}
	CCAnimation* attackAnimation = CCAnimation::createWithSpriteFrames(animFrames, 1.0f/24.0f);
	m_AttackAction = CCSequence::create(
		CCAnimate::create(attackAnimation),
		CCCallFunc::create(this, callfunc_selector(Hero::idle)), NULL);
	m_AttackAction->retain();
	animFrames->removeAllObjects();
	
	//Walk
	for(int i=0; i<8; ++i)
	{
		sprintf(str, "hero_walk_%02d.png", i);
		CCSpriteFrame* frame = cache->spriteFrameByName(str);
		animFrames->addObject(frame);
	}
	CCAnimation* walk = CCAnimation::createWithSpriteFrames(animFrames,1.0f/12.0f);
	m_WalkAction = CCRepeatForever::create(CCAnimate::create(walk));
	m_WalkAction->retain();
	animFrames->removeAllObjects();

	//Hurt
	for(int i=0; i<3; ++i)
	{
		sprintf(str, "hero_hurt_%02d.png", i);
		CCSpriteFrame* frame = cache->spriteFrameByName(str);
		animFrames->addObject(frame);
	}
	CCAnimation* hurt = CCAnimation::createWithSpriteFrames(animFrames,1.0f/12.0f);
	m_HurtAction = CCSequence::create(
		CCAnimate::create(hurt),
		CCCallFunc::create(this, callfunc_selector(Hero::idle)), NULL);
	m_HurtAction->retain();
	animFrames->removeAllObjects();

	//Knocked Out
	for(int i=0; i<5; ++i)
	{
		sprintf(str, "hero_knockout_%02d.png", i);
		CCSpriteFrame* frame = cache->spriteFrameByName(str);
		animFrames->addObject(frame);
	}
	CCAnimation* knock = CCAnimation::createWithSpriteFrames(animFrames,1.0f/12.0f);
	m_KnockedOutAction = CCSequence::create(
		CCAnimate::create(knock),
		CCBlink::create(2.0f, 10.0f), NULL);
	m_KnockedOutAction->retain();
	animFrames->removeAllObjects();
	
	m_CenterToBottom = 39.0f;
	m_CenterToSide = 29.0f;
	m_HitPoints = 100.0f;
	m_Damage = 20.0f;
	m_WalkSpeed = 80.0f;

	m_HitBox = createBoundingBoxWithOrigin(
		ccp(-m_CenterToSide, -m_CenterToBottom),
		CCSizeMake(m_CenterToSide*2, m_CenterToBottom*2));

	m_AttackBox = createBoundingBoxWithOrigin(
		ccp(m_CenterToSide, -10), CCSizeMake(20, 20));

	this->scheduleUpdate();

	init();
}

bool Hero::init()
{
	CActionSprite::init();
	this->idle();
	return true;
}