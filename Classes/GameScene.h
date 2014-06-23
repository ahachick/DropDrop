#ifndef __DROP_GAME_SCENE_H__
#define __DROP_GAME_SCENE_H__

#include "cocos2d.h"

USING_NS_CC;

class GameScene: public Scene {

public:
	//CREATE_FUNC(GameScene);

	static Scene* createScene();
	virtual bool init();
	void initUI();
	
};


#endif __DROP_GAME_SCENE_H