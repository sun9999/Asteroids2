/*
 * Spaceship.cpp
 *
 *  Created on: 2 Jan, 2015
 *      Author: sip
 */

#include "cocos2d.h"
#include "Spaceship.h"
#include "GameUtil.h"

USING_NS_CC;

bool Spaceship::init() {
    return CCSprite::init();
}

CCAnimation* Spaceship::createAnimation() {
	CCAnimation* pAnimation = CCAnimation::create();
	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("PlayerShip.plist");
	char buf[64];
	for (int i = 0; i < 6; i++) {
		sprintf(buf, "SHIP_A_%02d.png", i + 1);
		pAnimation->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(buf));
	}
	pAnimation->setDelayPerUnit(1.0f / 24);
	return pAnimation;
}

bool Spaceship::init(const char* filename) {
    if (!Spaceship::init()) {return false;}
    
    initWithFile(filename);
    setAngle(180);
    setRotation(getAngle()-180);
    setAnchorPoint(ccp(0.5, 0.5));
    runAction(CCRepeatForever::create((CCAnimate::create(createAnimation()))));


    return true;
}

