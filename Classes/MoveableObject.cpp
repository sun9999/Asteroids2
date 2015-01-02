/*
 * MoveableObject.cpp
 *
 *  Created on: 12 Dec, 2014
 *      Author: sip
 */

#include "MoveableObject.h"

USING_NS_CC;
using namespace std;

//	CCLOG("Moveable object coordinate x is: %f", getCoordinate().x);

float MoveableObject::getAngle() {
	return mAngle;
}

float MoveableObject::getSpeed() {
	return mSpeed;
}

float MoveableObject::getAcceleration() {
	return mAcceleration;
}

void MoveableObject::setAngle(float angle) {
	mAngle = angle;
}

void MoveableObject::setAcceleration(float acceleration) {
	mAcceleration = acceleration;
}

void MoveableObject::setSpeed(float speed) {
	mSpeed = speed;
}

void MoveableObject::updateDisplayedOpacity(GLubyte parentOpacity) {
    CCSprite::updateDisplayedOpacity(parentOpacity);
}

void MoveableObject::setOpacity(GLubyte opacity) {
    CCSprite::setOpacity(opacity);
}
