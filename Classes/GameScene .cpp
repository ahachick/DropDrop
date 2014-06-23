#include "GameScene.h"
#include "GameLayer.h"
#include "GestureLayer.h"

Scene* GameScene::createScene() {
	auto scene = Scene::createWithPhysics();
	scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
	//Vect gravity(0,0);
	//scene->getPhysicsWorld()->setGravity(gravity);
	auto gameLayer = GameLayer::create();
	gameLayer->setPhyWorld(scene->getPhysicsWorld());
	scene->addChild(gameLayer);
	scene->addChild(GestureLayer::create());
	return scene;
}

bool GameScene::init() {

	log("GameScene::init() called");
	if(Scene::init()) {
		//initUI();
		return true;
	}

	return false;
}
