/*
 * Bullet.cpp
 *
 *  Created on: 4 Jan, 2015
 *      Author: sip
 */

#include "Bullet.h"
#include "cocos2d.h"
#include "MoveableObject.h"
#include "GameUtil.h"

//#include <cmath>

USING_NS_CC;

Bullet* Bullet::create(const char* filename, const CCPoint pos, float angle) {
	Bullet *pRet = new Bullet();
    if (pRet && pRet->init(filename, pos, angle)) {
    	return pRet;
    } else {
    	delete pRet;
    	pRet = NULL;
    	return NULL;
    }
}

bool Bullet::init() {
	return CCSprite::init();
}

bool Bullet::init(const char* filename) {
	if (!init()) {return false;}

	initWithFile(filename);
	setAnchorPoint(ccp(0.5, 0.95));
    setScale(1);
	setTag(BULLET);
	setSpeed(BULLET_SPEED);

	return true;
}

bool Bullet::init(const char* filename, const CCPoint pos, float angle) {
	if (!init(filename)) {return false;}

	setAngle(angle);
    setRotation(getAngle()-180);
	setPosition(pos);
	retain();
	scheduleUpdate();
    
//    CCLog("Bullet angle:%5.2f, rotation:%5.2f", getAngle(), getRotation());

	return true;
}

void Bullet::update(float delta) {
	setPosition(GameUtil::calcPositionAfterMovment(getPosition(), getAngle(), getSpeed()));
}
