#ifndef __DROP_DROP_H
#define __DROP_DROP_H

#include "cocos2d.h"

USING_NS_CC;

static const float T_BASE = 1.0f;				//T:time cycle of base jumping
static const float T_CLOUD = T_BASE + 3.0f;		//T:time cycle of 'Cloud-Form' jumping
static const float T_WATER = T_BASE;			//T:time cycle of 'Water-Form' Sbase jumping
static const float T_ICE = T_BASE - 0.5f;		//T:time cycle of 'Ice-Form' jumping

class Drop : public Sprite{

public:

	enum class DropForm{
		Cloud, Water, Ice,
		Other// unused, just for Guard
	};

	enum class DropStatus {
		Move, Floating, DoubleFloating
	};

	CREATE_FUNC(Drop);
	CC_SYNTHESIZE(float, m_baseline, Baseline);
	CC_SYNTHESIZE(float, m_jumpHeight, JumpHeight);
	CC_SYNTHESIZE(float, m_tCycle, TCycle);
	CC_SYNTHESIZE(DropForm, m_dropForm, DropForm);
	CC_SYNTHESIZE(DropStatus, m_dropStatus, DropStatus);
	CC_SYNTHESIZE(bool, m_bBlockState, BlockState);

	virtual bool init() override;

	void onTouchBeganCallback();
	void onTouchMovedCallback();
	void onTouchEndedCallback();

	void doJump();
	void updateJump(float);
	void jumpEnd();
	float getYDelta();

	void collisionDetect();
	
	void transformToCloud();
	void transformToWater();
	void transformToIce();

	void update(float delta);

	Point getDetectPointer();
	Point getFoothold();

private:
	float m_elapsedTime;
	//float m_jumpHeight;
	//float m_tCycle;
	Point m_startPoint;
};

#endif