#include "GestureLayer.h"
#include "Drop.h"
#include "RadioMenu.h"

const float MIN_SLIDING_LENGTH = 40.0f;
const float MAX_SLIDING_MILLIS  = 250;


bool GestureLayer::init() {

	if(!Layer::init())
		return false;

	auto toWaterItem =	MenuItemImage::create("ToWaterBtn.png", "BePressedBtn.png", this,
												 menu_selector(GestureLayer::onWaterButtonPressed));
	auto toIceItem =	MenuItemImage::create("ToIceBtn.png", "BePressedBtn.png",this,
												 menu_selector(GestureLayer::onIceButtonPressed));
	auto toCloudItem =	MenuItemImage::create("ToCloudBtn.png", "BePressedBtn.png", this, 
												 menu_selector(GestureLayer::onCloudButtonPressed));

	


	//toWaterItem->setAnchorPoint(Point(0.5, 0.5));
	toWaterItem->setPosition(25, 25);
	//toIceItem->setAnchorPoint(Point(0.5, 0));
	toIceItem->setPosition(65, 25);
	//toCloudItem->setAnchorPoint(Point(0.5, 0));
	toCloudItem->setPosition(105, 25);

	auto ratioMenu = RadioMenu::create(toWaterItem, toIceItem, toCloudItem, NULL);
	ratioMenu->setAnchorPoint(Point(0,0));
	ratioMenu->setPosition(0,0);
	ratioMenu->setSelectedItem_(toWaterItem);
	toWaterItem->selected();
	this->addChild(ratioMenu);

	auto touchEvent = EventListenerTouchOneByOne::create();
	touchEvent->onTouchBegan = CC_CALLBACK_2(GestureLayer::onTouchBegan, this);
	touchEvent->onTouchMoved = CC_CALLBACK_2(GestureLayer::onTouchMoved, this);
	touchEvent->onTouchEnded = CC_CALLBACK_2(GestureLayer::onTouchEnded, this);
	_eventDispatcher->addEventListenerWithFixedPriority(touchEvent, 1);

	return true;
}

bool GestureLayer::onTouchBegan(Touch* touch, Event* unused) {
	
	m_prevPoint = touch->getLocation();
	m_prevTime = clock();

	//Drop::getInstance()->onTouchBeganCallback();
	return true;
}

void GestureLayer::onTouchMoved(Touch* touch, Event* unused){
	//log("Touch moved!");
}
void GestureLayer::onTouchEnded(Touch* touch, Event* unused) {
	

	//do not limit the angle of sliding, just judging the diff between two points
	Point currPoint = touch->getLocation();
	float currTime = clock();

	float diffLength = currPoint.x - m_prevPoint.x;
	float diffTime = currTime - m_prevTime;

	//log("The length of sliding: %f" , diffLength);
	//log("The timediff of sliding:%f", diffTime);
	if(diffLength > 0 && diffLength > MIN_SLIDING_LENGTH
			&& diffTime < MAX_SLIDING_MILLIS) {
		//callback
		//onSlidingToRight();
	}else {
		//Drop::getInstance()->onTouchEndedCallback();
	}

	//log("Touch ended!");
	//auto actionTo = JumpTo::create(2, m_role->getPosition(), 20, 1);
	//m_role->runAction(actionTo);
	//Point pos = touch->getLocation();
	////if(!removeOldSpriteAtTouchPoint(pos))
	//if(!letJump(pos))
	//	addNewSpriteAtTouchPoint(pos); 

}

void GestureLayer::onSlidingToRight(){
	log("Sliding Right!");
	//Drop::getInstance()->onSlidingToRight();
}


void GestureLayer::onWaterButtonPressed(Ref* sender) {
	//Drop::getInstance()->transformToWater();
}
void GestureLayer::onIceButtonPressed(Ref* sender) {
	//Drop::getInstance()->transformToIce();
}
void GestureLayer::onCloudButtonPressed(Ref* sender) {
	//Drop::getInstance()->transformToCloud();
}