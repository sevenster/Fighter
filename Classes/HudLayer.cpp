#include "HudLayer.h"

HudLayer::HudLayer()
{
	CCSpriteFrameCache* cache =
		CCSpriteFrameCache::sharedSpriteFrameCache();
	cache->addSpriteFramesWithFile("UI.plist", "UI.png");
	
	m_Joystick = NULL;
	m_Joystick = new SneakyJoystick();
	m_Joystick->initWithRect(CCRectZero);
	m_Joystick->setAutoCenter(true);
	m_Joystick->setHasDeadzone(true);
	m_Joystick->setDeadRadius(10);
	SneakyJoystickSkinnedBase* jstickSkin = new SneakyJoystickSkinnedBase();
	jstickSkin->autorelease();
	jstickSkin->init();
	jstickSkin->setBackgroundSprite(CCSprite::createWithSpriteFrameName("JoyStick-base.png"));
	jstickSkin->setThumbSprite(CCSprite::createWithSpriteFrameName("JoyStick-thumb.png"));
	jstickSkin->setPosition(ccp(50, 50));
	jstickSkin->setJoystick(m_Joystick);
	this->addChild(jstickSkin);

	m_Button = new SneakyButton();
	m_Button->initWithRect(CCRectZero);
	m_Button->setIsToggleable(false);
	m_Button->setIsHoldable(true);
	SneakyButtonSkinnedBase* btn = new SneakyButtonSkinnedBase();
	btn->autorelease();
	btn->init();
	btn->setPosition(ccp(430, 50));
	btn->setDefaultSprite(CCSprite::createWithSpriteFrameName("button-default.png"));
	btn->setPressSprite(CCSprite::createWithSpriteFrameName("button-pressed.png"));
	btn->setActivatedSprite(CCSprite::createWithSpriteFrameName("button-activated.png"));
	btn->setButton(m_Button);
	this->addChild(btn);

	init();
}

bool HudLayer::init()
{
	CCLayer::init();
	return true;
}