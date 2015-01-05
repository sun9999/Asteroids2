/*
 * Asteroids.cpp
 *
 *  Created on: 28 Dec, 2014
 *      Author: sip
 */

#include "Asteroids.h"
#include "GameUtil.h"

USING_NS_CC;

Asteroids* Asteroids::create(const char* filename, const CCPoint pos, float angle) {
	Asteroids *pRet = new Asteroids();
    if (pRet && pRet->init(filename, pos, angle)) {
    	return pRet;
    } else {
    	delete pRet;
    	pRet = NULL;
    	return NULL;
    }
}

bool Asteroids::init() {
	return CCNode::init();
}

bool Asteroids::init(const char* filename) {
	if ( !CCNode::init() ) {return false;}

    initWithFile(filename);
	setAnchorPoint(ccp(0.5, 0.5));
    setScale(genRandAsteroidSize());
    setSpeed(genFR(0.1, 0.6));
    setTag(ASTEROID);
    runAction(CCRepeatForever::create(CCRotateBy::create(genRandAsteroidSRDuration(), genRandAsteroidSRAngle())));
    retain();
    scheduleUpdate();

//    CCSize pRockSize = this->boundingBox().size;
//    CCLog("h:%5.2f, w:%5.2f", pRockSize.height, pRockSize.width);
//    CCLog("x:%5.2f, y:%5.2f", getPositionX(), getPositionY());
//    CCLog("angle:%5.2f", getAngle());

	return true;
}

bool Asteroids::init(const char* filename, const CCPoint pos, float angle) {
	if (!init(filename)) {return false;}

	setAngle(angle);
	setPosition(pos);

	return true;
}

void Asteroids::update(float delta) {
	setPosition(GameUtil::calcPositionAfterMovment(getPosition(), getAngle(), getSpeed()));
}
