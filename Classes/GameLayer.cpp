#include "GameLayer.h"
#include "Defines.h"
#include "CActionSprite.h"
#include "GameScene.h"

GameLayer::GameLayer()
{
	initTileMap();

	CCSpriteFrameCache* cache = 
		CCSpriteFrameCache::sharedSpriteFrameCache();
	cache->addSpriteFramesWithFile("pd_sprites.plist", "pd_sprites.png");

	CCTexture2D *texture = CCTextureCache::sharedTextureCache()->textureForKey("pd_sprites.png");
	m_Actors = CCSpriteBatchNode::createWithTexture(texture);
	m_Actors->getTexture()->setAliasTexParameters();
	this->addChild(m_Actors, 5);

	init();
}

bool GameLayer::init()
{
	CCLayer::init();
	initHero();
	this->scheduleUpdate();
	return true;
}

void GameLayer::initTileMap()
{
	mTileMap = CCTMXTiledMap::create("pd_tilemap.tmx");
	CCObject* itemLayer;
	CCARRAY_FOREACH(mTileMap->getChildren(), itemLayer)
	{
		CCTMXLayer* tmxLayer = dynamic_cast<CCTMXLayer*>(itemLayer);
		tmxLayer->getTexture()->setAliasTexParameters();
	}
	this->addChild(mTileMap, -6);
}

void GameLayer::initHero()
{
	m_Hero = new Hero();
	this->addChild(m_Hero);
	m_Hero->setPosition(CCPoint(100, 100));
}

void GameLayer::update(float dt)
{
	CCLayer::update(dt);
	updatePosition(dt);
	return;
}

void GameLayer::updatePosition(float dt)
{
	float posX = GetMin(mTileMap->getMapSize().width * mTileMap->getTileSize().width - m_Hero->m_CenterToSide, 
		GetMax(m_Hero->m_CenterToSide, m_Hero->m_DesirePosition.x));
	float posY = GetMin(3 * mTileMap->getTileSize().height + m_Hero->m_CenterToBottom, 
		GetMax(m_Hero->m_CenterToBottom, m_Hero->m_DesirePosition.y));

	//std::cout << mHero->mDesiredPosition.x << std::endl;
	m_Hero->setPosition(ccp(posX, posY));

	this->setViewPointCenter(m_Hero->getPosition());
}

void GameLayer::setViewPointCenter(CCPoint pos)
{
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();

	int x = GetMax(pos.x, winSize.width/2);
	int y = GetMax(pos.y, winSize.height/2);

	x = GetMin(x, (mTileMap->getMapSize().width * mTileMap->getTileSize().width - winSize.width/2));
	y = GetMin(y, (mTileMap->getMapSize().height * mTileMap->getTileSize().height - winSize.height/2));

	CCPoint actualPos = ccp(x, y);
	CCPoint centerOfView = ccp(winSize.width/2, winSize.height/2);
	CCPoint viewPoint = ccpSub(centerOfView, actualPos);

	this->setPosition(viewPoint);
}

