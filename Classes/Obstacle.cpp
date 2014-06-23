#include "Obstacle.h"

Sprite* Obstacle::createWithType(Obstacle::ObstacleType type) {

	Sprite * obstacleItem;

	switch(type) {

	default:
		break;
	case Obstacle::ObstacleType::Base:
		obstacleItem = Sprite::create("base.png");
		break;
	case Obstacle::ObstacleType::Hole:
		obstacleItem = Sprite::create("hole.png");
		break;
	case Obstacle::ObstacleType::Pillar:
		obstacleItem = Sprite::create("pillar.png");
		break;
	case Obstacle::ObstacleType::Sand:
		obstacleItem = Sprite::create("sand.png");
		break;
	}

	//auto body = PhysicsBody::createEdgeBox(obstacleItem->getContentSize());
	//obstacleItem->setPhysicsBody(body);

	return obstacleItem;
}

bool BaseItem::init(){

	if(!Sprite::init())
		return false;
	m_type = ObstacleType::Base;

	return initWithFile("base.png");
}

bool HoleItem::init(){

	if(!Sprite::init())
		return false;
	m_type = ObstacleType::Hole;
	return initWithFile("hole.png");
}

bool PillarItem::init(){

	if(!Sprite::init())
		return false;
	m_type = ObstacleType::Pillar;
	return initWithFile("pillar.png");
}

bool SandItem::init(){

	if(!Sprite::init())
		return false;
	m_type = ObstacleType::Sand;
	return initWithFile("sand.png");
}