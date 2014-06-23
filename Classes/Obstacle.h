#ifndef __DROP_OBSTACLE_H__
#define __DROP_OBSTACLE_H__

#include "cocos2d.h"

USING_NS_CC;


class Obstacle : public Sprite {
public :

	enum class ObstacleType
	{
		Base = 1, Hole, Pillar, Sand
	};
	static Sprite* createWithType(ObstacleType);
	virtual bool init();

protected:
	ObstacleType m_type;

};

class BaseItem : public Obstacle {
public:
	CREATE_FUNC(BaseItem);
	virtual bool init() override;

};

class HoleItem : public Obstacle {
	public:
	CREATE_FUNC(HoleItem);
	virtual bool init() override;

};

class SandItem : public Obstacle {
	public:
	CREATE_FUNC(SandItem);
	virtual bool init() override;

};

class PillarItem : public Obstacle {
	public:
	CREATE_FUNC(PillarItem);
	virtual bool init() override;

};

#endif