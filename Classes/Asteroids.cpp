/*
 * Asteroids.cpp
 *
 *  Created on: 28 Dec, 2014
 *      Author: sip
 */

#include "Asteroids.h"
#include "GameUtil.h"

USING_NS_CC;

bool Asteroids::init() {
	return CCNode::init();
}

float Asteroids::calcAngleWithRandomFactor(const CCPoint& central) {
	float angle = GameUtil::calcAngle(central, getPosition()) * genFR(0.66, 1.33);
	if (angle < 0) {
		angle = 0;
	} else if (angle > 360) {
		angle = 360;
	}

	return angle;
}

bool Asteroids::init(const char* filename) {
	if ( !CCNode::init() ) {return false;}

	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
	CCPoint central = ccp(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y);

    initWithFile(filename);
	setAnchorPoint(ccp(0.5, 0.5));
	setPosition(GameUtil::genRandCCP(origin, visibleSize, SCREEN_BUFFER));
	setAngle(calcAngleWithRandomFactor(central));
    setScale(genRandAsteroidSize());
    setSpeed(genFR(0.1, 0.6));
    setTag(ASTEROID);
    runAction(CCRepeatForever::create(CCRotateBy::create(genRandAsteroidSRDuration(), genRandAsteroidSRAngle())));
    retain();
    scheduleUpdate();
    
    CCSize pRockSize = this->boundingBox().size;
    CCLog("h:%5.2f, w:%5.2f", pRockSize.height, pRockSize.width);
    CCLog("x:%5.2f, y:%5.2f", getPositionX(), getPositionY());
    CCLog("angle:%5.2f", getAngle());

	return true;
}

void Asteroids::update(float delta) {
	setPosition(GameUtil::calcPositionAfterMovment(getPosition(), getAngle(), getSpeed()));
}
