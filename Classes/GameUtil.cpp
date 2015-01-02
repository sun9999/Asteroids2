/*
 * GameUtil.cpp
 *
 *  Created on: 28 Dec, 2014
 *      Author: sip
 */

#include "GameUtil.h"
#include <sys/time.h>
#include <stdlib.h>
#include <cmath>
#include "ccMacros.h"


GameUtil::GameUtil() {}

GameUtil::~GameUtil() {}

unsigned long GameUtil::getTickCount() {
	struct timeval current;
	gettimeofday(&current, NULL);
	return current.tv_sec * 1000 + current.tv_usec / 1000;
}

int GameUtil::getRandNumber(int from, int to) {
	if (from>to) {return -1;}

	return from + (rand() % (to-from+1));
}

long GameUtil::getRandNumber(long from, long to) {
	if (from>to) {return -1;}

	return from + (rand() % (to-from+1));
}

float GameUtil::getRandNumber(float from, float to) {
	if (from>to) {return -1;}
    
    float random = ((float) rand()) / (float) RAND_MAX;
    return (random*(to - from)) + from;
}

double GameUtil::getRandNumber(double from, double to) {
	if (from>to) {return -1;}

	double random = ((double) rand()) / (double) RAND_MAX;
    return (random*(to - from)) + from;
}

CCPoint GameUtil::genRandCCP(CCPoint pos, CCSize size, float buffer) {
	float x = pos.x;
	float y = pos.y;
	float w = size.width;
	float h = size.height;

	switch(genIR(0, 3)) {
	case 0: //Above
		CCLog("Above");
		return ccp(genFR(x, x+w), genFR(y+h, y+h+buffer));
	case 1: //Right hand side
		CCLog("Right");
		return ccp(genFR(x+w, x+w+buffer), genFR(y, y+h));
	case 2: //Below
		CCLog("Below");
		return ccp(genFR(x, x+w), genFR(y-buffer, y));
	case 3: //Left hand side
		CCLog("Left");
		return ccp(genFR(x-buffer, x), genFR(y, y+h));
	default:
		return ccp(x, y);
	}
}

float GameUtil::calcAngle(CCPoint targetPos, CCPoint objPos) {
	/* Determine the quadrant, the order is Q1, Q4, Q3, Q2, this is not a mistake.
	 * The order is different with the mathematical model because
	 * we determine the angle using the y-axis clockwise in the cocos2dx model.
	 */
    float angle;
    
	if (objPos.x>=targetPos.x && objPos.y>=targetPos.y) {
		//p2 is located at right-upper side of p1 (Q1)
		angle = atan(abs((objPos.x-targetPos.x)/(objPos.y-targetPos.y))) * RADIAN;
	} else if (objPos.x>=targetPos.x && objPos.y<targetPos.y) {
		//p2 is located at right-lower side of p1 (Q4)
		angle = atan(abs((objPos.y-targetPos.y)/(objPos.x-targetPos.x))) * RADIAN + 90;
	} else if (objPos.x<targetPos.x && objPos.y<targetPos.y) {
		//p2 is located at left-lower side of p1 (Q3)
		angle = atan(abs((objPos.x-targetPos.x)/(objPos.y-targetPos.y))) * RADIAN + 180;
	} else if (objPos.x<targetPos.x && objPos.y>=targetPos.y) {
		//p2 is locate at left-upper side of p1 (Q2)
		angle = atan(abs((objPos.y-targetPos.y)/(objPos.x-targetPos.x))) * RADIAN + 270;
	}
    
    CCLog("p1 location x:%5.2f, y:%5.2f", targetPos.x, targetPos.y);
	CCLog("p2 location x:%5.2f, y:%5.2f", objPos.x, objPos.y);
    CCLog("Angle: %5.2f", angle);
    
    if (angle<0 || angle>360) {
        CCLOGWARN("CCPoint1 x:%5.2f y:%5.2f, CCPoint2 x:%5.2f y:%5.2f, Angle: %5.2f", targetPos.x, targetPos.y, objPos.x, objPos.y, angle);
    }
    
    return angle;
}

CCPoint GameUtil::calcPositionAfterMovment(CCPoint oldPos, float angle, float distance) {
	if (angle>=0 && angle<=90) { //Q1
		float x = oldPos.x-(sin(angle*PI/180)*distance);
		float y = oldPos.y-(cos(angle*PI/180)*distance);
		return ccp(x, y);
	} else if (angle>90 && angle<=180) { //Q4
		angle -= 90;
		float x = oldPos.x-(cos(angle*PI/180)*distance);
		float y = oldPos.y+(sin(angle*PI/180)*distance);
		return ccp(x, y);
	} else if (angle>180 && angle<=270) { //Q3
		angle -= 180;
		float x = oldPos.x+(sin(angle*PI/180)*distance);
		float y = oldPos.y+(cos(angle*PI/180)*distance);
		return ccp(x, y);
	} else if (angle>270 && angle<=360) { //Q2
		angle -= 270;
		float x = oldPos.x+(cos(angle*PI/180)*distance);
		float y = oldPos.y-(sin(angle*PI/180)*distance);
		return ccp(x, y);
	}
    
    CCLOGWARN("CCPoint x:%5.2f, y:%5.2f, Angle: %5.2f, Distance: %5.2f", oldPos.x, oldPos.y, angle, distance);
    
    return ccp(0, 0);
}
