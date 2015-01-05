/*
 * GameUtil.h
 *
 *  Created on: 28 Dec, 2014
 *      Author: sip
 */

#ifndef GAMEUTIL_H_
#define GAMEUTIL_H_

#define INITIAL_SPACESHIP_COUNT 5
#define INITIAL_MISSILE_COUNT 99
#define MENU_BORDER 5
#define RADIAN 57.29577951308233 //1 rad = 180/pi
#define PI 3.141592653589793
#define COLLISION_BUCKET_WIDTH 5
#define COLLISION_BUCKET_HEIGHT 3
#define RESISTANCE_FACTOR 0.9
#define MAX_ASTEROIDS 25
#define SCREEN_BUFFER 100

#define MISSILE_SPEED 1.8
#define BULLET_SPEED 2
//#define MAX_MISSLE_ANGLE 3

#define genIR(_FROM_, _TO_) GameUtil::getRandNumber((int)_FROM_, (int)_TO_)
#define genLR(_FROM_, _TO_) GameUtil::getRandNumber((long)_FROM_, (long)_TO_)
#define genFR(_FROM_, _TO_) GameUtil::getRandNumber((float)_FROM_, (float)_TO_)
#define genDR(_FROM_, _TO_) GameUtil::getRandNumber((double)_FROM_, (double)_TO_)

#include "cocos2d.h"

USING_NS_CC;
using namespace std;

enum {
	GAME_INTRO_SCREEN,
	GAME_STARTED,
	GAME_OVER
};

enum ObjectTag {
    GAME_MENU,
    GAME_MENU_OPTION,
    LABEL,
    SPACESHIP,
    ASTEROID,
    MISSILE,
    BULLET
};

class GameUtil {
private:

public:
	GameUtil();
	~GameUtil();

    static unsigned long getTickCount();

	static int getRandNumber(int, int);
	static long getRandNumber(long, long);
	static float getRandNumber(float, float);
	static double getRandNumber(double, double);

	static CCPoint genRandCCP(CCPoint, CCSize, float buffer);

	static float calcAngle(CCPoint, CCPoint);

	static CCPoint calcPositionAfterMovment(CCPoint, float, float);
};

#endif /* GAMEUTIL_H_ */
