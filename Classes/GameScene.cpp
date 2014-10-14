#include "GameScene.h"

GameScene::GameScene()
{
	m_HudLayer = new HudLayer();
	this->addChild(m_HudLayer, 1);

	m_GameLayer = new GameLayer();
	this->addChild(m_GameLayer, 0);

	init();
	this->schedule(schedule_selector(GameScene::inputUpdate));
}

bool GameScene::init()
{
	CCScene::init();
	return true;
}

float attackInterval = -1.0f;
void GameScene::inputUpdate(float dt)
{
	CCPoint velocity = m_HudLayer->m_Joystick->getVelocity();
	if (velocity.x >= 0.4f || velocity.x <= -0.4f ||
		velocity.y >= 0.4f || velocity.y <= -0.4f)
	{
		m_GameLayer->m_Hero->walkWithDirection(velocity);
	}
	else if (m_GameLayer->m_Hero->m_ActionState == kActionStateWalk)
	{
		m_GameLayer->m_Hero->idle();
	}

	if (attackInterval <= 0.0f) {
		if (m_HudLayer->m_Button->getIsActive()) {
			m_GameLayer->m_Hero->attack();
			attackInterval = 0.5f;
		}
	} else {
		attackInterval -= dt;
	}
	return;
}