/*
 * Missle.cpp
 *
 *  Created on: 1 Jan, 2015
 *      Author: sip
 */

#include "Missle.h"
#include "GameUtil.h"

USING_NS_CC;

Missle* Missle::Create(const char* filename, const CCPoint pos, CCNode* target) {
    Missle *pRet = new Missle();
    if (pRet && pRet->init(filename, pos, target)) {
    	return pRet;
    } else {
    	delete pRet;
    	pRet = NULL;
    	return NULL;
    }
}

bool Missle::init() {
	return CCSprite::init();
}

bool Missle::init(const char* filename) {
	if (!Missle::init()) {return false;}

	initWithFile(filename);
	setAnchorPoint(ccp(0.5, 0.2));
	setTag(MISSILE);
	setSpeed(1.8);

	return true;
}

bool Missle::init(const char* filename, const CCPoint pos, CCNode* target) {
	if (!init(filename)) {return false;}

    setTarget(target);
	setPosition(pos);
    scheduleUpdate();
//	if (getTarget()!=NULL) {
//		setAngle(GameUtil::calcAngle(getTarget()->getPosition(), getPosition()));
//	}
//    schedule(schedule_selector(Missle::changeDirection), 0, 0, .5);

	return true;
}

void Missle::update(float delta) {
    if (getTarget()!=NULL) {
        
        float angle = GameUtil::calcAngle(getTarget()->getPosition(), getPosition());
        
        float maxAngle = getAngle()*1.03;
        float minAngle = getAngle()*.97;
        
        if (angle<minAngle) {
            angle = minAngle;
        } else if (angle>maxAngle) {
            angle = maxAngle;
        }
        
        setAngle(angle);
        setRotation(getAngle() -180);
    }

	setPosition(GameUtil::calcPositionAfterMovment(getPosition(), getAngle(), getSpeed()));
}

void Missle::changeDirection() {
}