/*
 * Asteroids.h
 *
 *  Created on: 28 Dec, 2014
 *      Author: Sunny Ho, Ip
 */

#ifndef ASTEROIDS_H_
#define ASTEROIDS_H_

#define MIN_SIZE 0.1
#define MAX_SIZE 0.3

#define MIN_SELF_ROTATION_DURATION 0.4
#define MAX_SELF_ROTATION_DURATION 1.0

#define MIN_SELF_ROTATION_ANGLE 0.0
#define MAX_SELF_ROTATION_ANGLE 90.0

#define MIN_SPEED 1
#define MAX_SPEED 10

#include "GameUtil.h"
#include "cocos2d.h"
#include "MoveableObject.h"

#define genRandAsteroidSize()		genFR(MIN_SIZE, MAX_SIZE)
#define genRandAsteroidSRDuration()	genFR(MIN_SELF_ROTATION_DURATION, MAX_SELF_ROTATION_DURATION)
#define genRandAsteroidSRAngle()	genFR(MIN_SELF_ROTATION_ANGLE, MAX_SELF_ROTATION_ANGLE)

USING_NS_CC;

class Asteroids : public MoveableObject {
private:
	float mSize;
	float mSelfRotateDuration;
	float mSelfRotateAngle;
	float calcAngleWithRandomFactor(const CCPoint& central);
public:
	CREATE_FUNC2(Asteroids);
    
    bool init(const char*);

	virtual bool init();
    
	virtual void update(float);
};


#endif /* ASTEROIDS_H_ */
