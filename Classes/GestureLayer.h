#ifndef __DROP_GESTURELAYER_H__
#define __DROP_GESTURELAYER_H__

#include "cocos2d.h"

USING_NS_CC;

class GestureLayer :public Layer {

public:
	CREATE_FUNC(GestureLayer);
	virtual bool init();

	virtual bool onTouchBegan(Touch* touch, Event *unused) override;
	virtual void onTouchMoved(Touch* touch, Event *unused) override;
	virtual void onTouchEnded(Touch* touch, Event *unused) override;

	void onWaterButtonPressed(Ref* sender);
	void onIceButtonPressed(Ref* sender);
	void onCloudButtonPressed(Ref* sender);

	void onSlidingToRight();

private:
	Point m_prevPoint;
	float m_prevTime;

};

#endif