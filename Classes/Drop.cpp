#include "Drop.h"

static Drop* s_instance = nullptr;

const float MIN_SLIDING_LENGTH = 40.0f;
const float MAX_SLIDING_MILLIS  = 250;

const static int WATER_ANIMATION = 1;
const static int ICE_ANIMATION = 2;
const static int CLOUD_ANIMATION = 3;

static int s_currAnimation = 0;


bool Drop::init() {
	//transformToWater();
	if(!this->initWithFile("ToWaterBtn.png")){
		return false;
	}

	//m_currAction = nullptr;
	m_dropForm = DropForm::Other;
	m_dropStatus = DropStatus::Move;
	s_currAnimation = 0;
	transformToWater();
	scheduleUpdate();


	m_jumpHeight = 80;
	
	return true;
}

void Drop::onTouchBeganCallback(){
	log("Callback:Touch began!");

	 
	//doJump();

	/*if(DropStatus::DoubleFloating == m_dropStatus)
		return;

	if(nullptr != m_currAction)
			stopAction(m_currAction);
		
	m_currAction = Sequence::create(MoveBy::create(0.25f, Point(0, 60)),
		MoveTo::create(0.25f, Point(this->getPositionX(), getBaseline())),
		CallFunc::create(this, callfunc_selector(Drop::jumpEnd)), NULL);
	runAction(m_currAction);
	if(DropStatus::Floating == m_dropStatus){	
		m_dropStatus = DropStatus::DoubleFloating;
		log("Is Double-Floating");
	}else{
		m_dropStatus = DropStatus::Floating;
		log("Is Floating");
	}*/

}
void Drop::doJump() {
	if(m_dropStatus == DropStatus::DoubleFloating) {
		return;
	}

	if((m_dropStatus == DropStatus::Move)
		||(m_dropForm == DropForm::Water)){
		m_elapsedTime = 0.0f;
		m_startPoint = getPosition();
		m_dropStatus = (m_dropStatus == DropStatus::Move) ?
			DropStatus::Floating : DropStatus::DoubleFloating;
	}
}
void Drop::update(float delta) {
	
	//updateJump(delta);
}

void Drop::updateJump(float delta) {
	if(DropStatus::Move != m_dropStatus) {
		m_elapsedTime += delta;
		log("Y Delat: %f", getYDelta());
		setPositionY(m_startPoint.y + getYDelta());
		//detect the collision and do some reactions
		collisionDetect();
		
	}
}

void Drop::collisionDetect() {
	if(getPositionY() <= -getContentSize().height){
		//if(getPositionY() - getBaseline() <= 0){
			setPositionY(getBaseline());
			m_dropStatus = DropStatus::Move;
			if(DropForm::Cloud == m_dropForm)
				m_tCycle = T_CLOUD;
		}

		if(getPositionX() < 0 ){
			setPositionX(100.0f);
		}
}


float Drop::getYDelta() {

	float ratio = m_elapsedTime / m_tCycle;
	return m_jumpHeight *  4 * ratio * (1 - ratio);
}

void Drop::jumpEnd() {

	log("Call jumpEnd");
	m_dropStatus = DropStatus::Move;
	log("Call:Is moving");

}
void Drop::onTouchMovedCallback(){
	//log("Callback:Touch moved!");
}
void Drop::onTouchEndedCallback(){
	//log("Callback:Touch ended!");
	if((DropStatus::Floating == m_dropStatus)
			&& (DropForm::Cloud == m_dropForm)
			&& (m_tCycle > T_BASE)) {
		float ratio = m_elapsedTime / T_CLOUD;
		//ratio = (ratio < 0.5) ? (1 - ratio) : ratio;
		m_elapsedTime = ratio * T_BASE;
		m_tCycle = T_BASE;
	}
	
}

void Drop::transformToWater() {
	if(DropForm::Water == m_dropForm)
		return;
	
	log("To water!");
	m_dropForm = DropForm::Water;
	m_tCycle = T_WATER;

	stopActionByTag(s_currAnimation);

	auto waterVects = Vector<SpriteFrame*>();
	
	waterVects.pushBack(SpriteFrame::create("ToWaterBtn.png", Rect(0,0, 40,40)));
	
	auto animation = Animation::createWithSpriteFrames(waterVects, 1.0f);
	auto animate = Animate::create(animation);
	auto forever = RepeatForever::create(Animate::create(animation));
	forever->setTag(WATER_ANIMATION);
	s_currAnimation = WATER_ANIMATION;
	runAction(forever);
}

void Drop::transformToCloud() {

	if(DropForm::Cloud == m_dropForm)
		return;
	
	log("To cloud!");
	m_dropForm = DropForm::Cloud;
	m_tCycle = T_CLOUD;
	stopActionByTag(s_currAnimation);

	auto waterVects = Vector<SpriteFrame*>();
	
	waterVects.pushBack(SpriteFrame::create("ToCloudBtn.png", Rect(0,0, 40,40)));
	
	auto animation = Animation::createWithSpriteFrames(waterVects, 1.0f);
	auto forever = RepeatForever::create(Animate::create(animation));
	forever->setTag(CLOUD_ANIMATION);
	s_currAnimation = CLOUD_ANIMATION;
	runAction(forever);
}

void Drop::transformToIce() {

	if(DropForm::Ice == m_dropForm)
		return;
	log("To water!");
	m_dropForm = DropForm::Ice;
	m_tCycle = T_ICE;
	stopActionByTag(s_currAnimation);

	auto waterVects = Vector<SpriteFrame*>();
	
	waterVects.pushBack(SpriteFrame::create("ToIceBtn.png", Rect(0,0, 40,40)));
	
	auto animation = Animation::createWithSpriteFrames(waterVects, 1.0f);
	auto forever = RepeatForever::create(Animate::create(animation));
	forever->setTag(ICE_ANIMATION);
	s_currAnimation = ICE_ANIMATION;
	runAction(forever);
}

Point Drop::getDetectPointer() {

	Size contentSize = getContentSize();
	Point preAnchor = getAnchorPoint();
	setAnchorPoint(Point(0,0));
	Point pos = getPosition();
	Point dp(pos.x + contentSize.width, pos.y + contentSize.height / 2);
	setAnchorPoint(preAnchor);//restore the previous state
	return dp;
}

Point Drop::getFoothold() {
	Point preAnchor = getAnchorPoint();
	setAnchorPoint(Point(0.5,0));
	Point foothold = getPosition();
	setAnchorPoint(preAnchor);//restore the previous state
	return foothold;
}


