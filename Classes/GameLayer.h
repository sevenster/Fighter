#ifndef _GAME_LAYER_H_
#define _GAME_LAYER_H_

#include "cocos2d.h"
using namespace cocos2d;

#include "Hero.h"

class GameLayer : public CCLayer
{
public:
	GameLayer();
	bool init();

	CCTMXTiledMap* mTileMap;

	void initTileMap();
	void initHero();
	Hero* m_Hero;
	
	CCSpriteBatchNode* m_Actors;


	void update(float dt);
	void updatePosition(float dt);

	void setViewPointCenter(CCPoint pos);

};

#endif