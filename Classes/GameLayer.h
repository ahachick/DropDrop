#ifndef __DROP_GAME_LAYER_H
#define __DROP_GAME_LAYER_H

#include "cocos2d.h"
#include "Drop.h"

USING_NS_CC;

#define INIT_VECT 2.0f

class GameLayer:public Layer {

public :
	CREATE_FUNC(GameLayer);
	virtual bool init();
	void initUI();
	void update(float);
	virtual bool onTouchBegan(Touch*, Event*);
	virtual void onTouchMoved(Touch*, Event*);
	virtual void onTouchEnded(Touch*, Event*);

	void initObstacles();
	void addGlobalEdgePhysicsNode();
	bool onContactBegin(EventCustom *event, const PhysicsContact& contact);
	void setPhyWorld(PhysicsWorld* world){m_world = world;}
	void makeSpriteWithPhysics(Sprite*);


	void doJump();
	void updateJump(float);
	void beforeJump();
	void jumpEnd();
	float computeYDelta();


	CC_SYNTHESIZE(float, m_horizon, Horizon);
private :
	Vector<Sprite*> m_vectObstacles;
	Vector<Sprite*> m_vectTraps;
	Sprite* m_bgSprite1;
	Sprite* m_bgSprite2;
	Drop* m_role;

	Point m_startPoint;//the point where the role start to jump
	float m_elapsedTime;
	float m_fVect;
	PhysicsJointPin* joint;
    PhysicsWorld* m_world;
};

#endif