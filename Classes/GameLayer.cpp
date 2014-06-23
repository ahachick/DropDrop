#include "GameLayer.h"
#include "Obstacle.h"
#include "GameScene.h"

static float s_vec = 1.0f;

static Point basePoint(200.0f, 114.0f + 20.f);

bool GameLayer::init() {
	if(!Layer::init()){

		return false;
	}

	initUI();
	return true;
}

void GameLayer::initUI() {

	m_fVect = INIT_VECT;
	m_horizon = 114.0f;

	auto director = Director::getInstance();
	Size size = director->getVisibleSize();
	Point origin = director->getVisibleOrigin();

	//init backgroud
	m_bgSprite1 = Sprite::create("Drop_BG1.png");
	m_bgSprite2 = Sprite::create("Drop_BG2.png");
	m_bgSprite1->setPosition(Point(size.width / 2, size.height / 2));
	m_bgSprite2->setPosition(Point(size.width / 2 + size.width, size.height / 2));
	this->addChild(m_bgSprite1, -1);
	this->addChild(m_bgSprite2, -1);

	//add touch event listener
	auto touchEvent = EventListenerTouchOneByOne::create();
	touchEvent->onTouchBegan = CC_CALLBACK_2(GameLayer::onTouchBegan,this);
	touchEvent->onTouchMoved = CC_CALLBACK_2(GameLayer::onTouchMoved,this);
	touchEvent->onTouchEnded = CC_CALLBACK_2(GameLayer::onTouchEnded,this);
	_eventDispatcher->addEventListenerWithFixedPriority(touchEvent, 1);
	
	

	//Add Label
	auto timeLabel = Label::create("Time", "Arial", 30);
	timeLabel->setPosition(size.width / 2, size.height/2 + 100.0f);
	this->addChild(timeLabel);

	//Add Menu
	auto item1 = MenuItemFont::create("Item Font Test", [&](Ref* sender)
                                      { Director::getInstance()->replaceScene(GameScene::create());}
                                      );
    item1->setFontSize(40);
    item1->setFontName("Marker Felt");

	auto item6 = MenuItemToggle::createWithCallback([&](Ref*){ }, MenuItemFont::create("On"),    MenuItemFont::create("Off"), NULL);
    MenuItemFont::setFontName("Marker Felt");
    MenuItemFont::setFontSize(40);
	//item6->setPosition(Point(size.width / 2, s));


	auto menu = Menu::create(item1,item6, NULL);
    //menu->setPosition(Point(0, 0));
	menu->alignItemsVertically();
	this->addChild(menu);
	scheduleUpdate();

	//init role and mass	
	m_role = Drop::create();
	m_role->setPosition(basePoint);
	auto body = PhysicsBody::createCircle(m_role->getContentSize().width/2);
	//body->setGravityEnable(false);
	m_role->setPhysicsBody(body);
	this->addChild(m_role, 100);
	
	auto edgeNode = Node::create();
	auto edgeBody = PhysicsBody::createEdgeBox(size);
	edgeNode->setPosition(size.width / 2, size.height / 2);
	edgeNode->setPhysicsBody(edgeBody);
	this->addChild(edgeNode);

	joint = nullptr;

	initObstacles();

	 // Åö×²¼ì²â»Øµ÷
    /*auto contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = CC_CALLBACK_2(GameLayer::onContactBegin, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);*/
}

void GameLayer::update(float delta){

	auto director = Director::getInstance();
	Size size = director->getVisibleSize();
	
	//update obstacles
	auto iter = m_vectObstacles.begin();

	while(iter != m_vectObstacles.end()){
		auto target = dynamic_cast<Sprite*>(*iter);
		target->setPositionX(target->getPositionX() - s_vec);
		iter++;
	}
	
	auto begin = m_vectObstacles.front();

	if(begin->getPositionX() < -(begin->getContentSize().width)){
		m_vectObstacles.erase(m_vectObstacles.begin());
		removeChild(begin);
		auto back = m_vectObstacles.back();
		auto newSprite = Obstacle::createWithType(Obstacle::ObstacleType::Base);
		//newSprite->setAnchorPoint(Point(0,0));
		makeSpriteWithPhysics(newSprite);
		newSprite->setPosition(back->getPositionX() + back->getContentSize().width, newSprite->getContentSize().height /2);
		m_vectObstacles.pushBack(newSprite);
		addChild(newSprite);
	}
	//update trap
	auto iter2 = m_vectTraps.begin();

	while(iter2 != m_vectTraps.end()) {
		auto target = dynamic_cast<Sprite*>(*iter2);
		target->setPositionX(target->getPositionX() - s_vec);
		iter2++;
	}
	
	updateJump(delta);

}


void GameLayer::makeSpriteWithPhysics(Sprite* target) {
	auto body = PhysicsBody::createBox(target->getContentSize());
	body->setDynamic(false);
	target->setPhysicsBody(body);
	
}


bool GameLayer::onContactBegin(EventCustom *event, const PhysicsContact& contact) {
	log("Collision!");
	return true;
}

void GameLayer::initObstacles() {
	int i;
	for(i = 0; i < 15; i++) {
		auto item = Obstacle::createWithType(Obstacle::ObstacleType::Base);
		
		//item->setAnchorPoint(Point(0, 0));
		item->setPosition(Point(i * 40 + 20, item->getContentSize().height /2));
		makeSpriteWithPhysics(item);
		this->addChild(item);
		m_vectObstacles.pushBack(item);
	}
	for(; i < 30; i++) {
		auto item = Obstacle::createWithType(Obstacle::ObstacleType::Hole);
		//item->setAnchorPoint(Point(0, 0));
		item->setPosition(Point(i * 40 + 20, item->getContentSize().height /2));
		this->addChild(item);
		m_vectObstacles.pushBack(item);
	}

	int j = 0;
	for(; j < 60; j+=15) {
		auto item = Obstacle::createWithType(Obstacle::ObstacleType::Pillar);
		
		//item->setAnchorPoint(Point(0, 0));
		float horizon = getHorizon();
		makeSpriteWithPhysics(item);
		item->setPosition(Point(j *40 +20, horizon + item->getContentSize().height / 2));
		
		m_vectTraps.pushBack(item);
		this->addChild(item);
	}
}

void GameLayer::beforeJump() {
	m_role->getPhysicsBody()->setGravityEnable(false);
	//m_role->getPhysicsBody()->setDynamic(false);
}

void GameLayer::jumpEnd() {
	
	m_role->getPhysicsBody()->setGravityEnable(true);
	//m_role->getPhysicsBody()->setDynamic(true);
}

bool GameLayer::onTouchBegan(Touch* touch, Event* event) {
	//doJump();
	auto jump = Sequence::create(CallFunc::create(this, callfunc_selector(GameLayer::beforeJump)),
								 EaseQuadraticActionIn::create(MoveBy::create(0.5f, Point(0, 60))),
								 CallFunc::create(this, callfunc_selector(GameLayer::jumpEnd)),
								 NULL);
	m_role->runAction(jump);

	return true;
} 
void GameLayer::onTouchMoved(Touch* touch, Event* event) {

}
void GameLayer::onTouchEnded(Touch*, Event*) {
	
}

void GameLayer::doJump() {
	if(m_role->getDropStatus() == Drop::DropStatus::DoubleFloating) {
		return;
	}

	if((m_role->getDropStatus() == Drop::DropStatus::Move)
		||(m_role->getDropForm() == Drop::DropForm::Water)){
		m_elapsedTime = 0.0f;
		m_startPoint = m_role->getPosition();

		m_role->setDropStatus((m_role->getDropStatus() == Drop::DropStatus::Move) ?
			Drop::DropStatus::Floating : Drop::DropStatus::DoubleFloating);
		

	}
}

void GameLayer::updateJump(float dt) {
	if(Drop::DropStatus::Move != m_role->getDropStatus()) {
		m_elapsedTime += dt;
		log("Y Delat: %f", computeYDelta());
		//detect the collision and do some reactions
		//collisionDetect();
		

	}
}



float GameLayer::computeYDelta() {
	float ratio = m_elapsedTime / m_role->getTCycle();
	return m_role->getJumpHeight() *  4 * ratio * (1 - ratio);
}