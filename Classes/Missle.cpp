/*
 * Missle.cpp
 *
 *  Created on: 1 Jan, 2015
 *      Author: sip
 */

#include "Missle.h"
#include "GameUtil.h"
#include <cmath>

USING_NS_CC;

Missle* Missle::create(const char* filename, const CCPoint pos, CCNode* target) {
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
	setSpeed(MISSILE_SPEED);

	return true;
}

bool Missle::init(const char* filename, const CCPoint pos, CCNode* target) {
	if (!init(filename)) {return false;}

    setTarget(target);
	setPosition(pos);
    scheduleUpdate();

	return true;
}

void Missle::update(float delta) {
    if (getTarget()!=NULL) {
        
//        float objectRleatedAngle = GameUtil::calcAngle(getTarget()->getParent()->convertToWorldSpace(getTarget()->getPosition()), getParent()->convertToWorldSpace(getPosition()));
        
//        CCLog("x:%5.2f, y:%5.2f", getTarget()->getPositionX(), getTarget()->getPositionY());
//        CCLog("objectRleatedAngle: %5.2f, missile angle: %5.2f", objectRleatedAngle, getAngle());
//        
//        float angleDifferences = getAngle()-objectRleatedAngle-180;
//        
//        float turningAngle=180;
//        
//        if (angleDifferences<0) { //turn left
//            turningAngle = (abs(angleDifferences)>MAX_MISSLE_ANGLE) ? getAngle()+MAX_MISSLE_ANGLE : getAngle()+angleDifferences;
//            //            turningAngle = (angleDifferences>MAX_MISSLE_ANGLE) ? MAX_MISSLE_ANGLE : angleDifferences;
//            if (turningAngle>360) {
//                turningAngle =0;
//            }
//        } else { //turn right
//            turningAngle = (abs(angleDifferences)>MAX_MISSLE_ANGLE) ? getAngle()-MAX_MISSLE_ANGLE : getAngle()-angleDifferences;
//            if (turningAngle<0) {
//                turningAngle=360;
//            }
//        }
//        
//        setAngle(turningAngle);
//        setRotation(getAngle() -180);


        float angle = GameUtil::calcAngle(getTarget()->getParent()->convertToWorldSpace(getTarget()->getPosition()), getPosition());
        
        float maxAngle = getAngle()*1.03;
        float minAngle = getAngle()*0.97;
        
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
