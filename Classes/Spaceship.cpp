/*
 * Spaceship.cpp
 *
 *  Created on: 2 Jan, 2015
 *      Author: sip
 */

#include "Spaceship.h"
#include "GameUtil.h"

USING_NS_CC;

bool Spaceship::init() {
    return CCSprite::init();
}

bool Spaceship::init(const char* filename) {
    if (!Spaceship::init()) {return false;}
    
    initWithFile(filename);
    setAngle(180);
    setAnchorPoint(ccp(0.5, 0.5));
    
    return true;
}

