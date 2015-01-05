//
//  Background.cpp
//
#include "Background.h"
#include "GameUtil.h"

USING_NS_CC;

Background* Background::create(const char *filename, float ratio) {
    Background *pRet = new Background();
    if (pRet && pRet->init(filename, ratio)) {
    	return pRet;
    } else {
    	delete pRet;
    	pRet = NULL;
    	return NULL;
    }
}

bool Background::init() {
    return CCNode::init();
}

void Background::update(float delta) {
    update(ccp(getPositionX()+1, getPositionY()));
}

void Background::update(CCPoint displacement) {
	CCPoint current = getPosition();
    
    CCLog("1 X:%5.2f, Y:%5.2f", current.x, current.y);

	current = current - displacement * mRatio;

	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	CCSize worldSize = getContentSize();
    
	float minX = visibleSize.width - worldSize.width/2;
    float maxX = worldSize.width/2;
    float minY = visibleSize.height - worldSize.height/2;
    float maxY = worldSize.height/2;
    
    CCLog("maxX: %5.2f", maxX);
    CCLog("maxY: %5.2f", maxY);
    
    while (current.x > maxX) {current.x -= maxX;}
    while (current.y > maxY) {current.y -= maxY;}
    while (current.x < minX) {current.x += maxX;}
    while (current.y < minY) {current.y += maxY;}
    
    CCLog("2 X:%5.2f, Y:%5.2f", current.x, current.y);

    setPosition(current);
}

CCSprite* Background::createLeaf(const char* filename, CCPoint anchorPoint) {
	CCSprite* leaf;
	leaf = CCSprite::create(filename);
	leaf->setAnchorPoint(anchorPoint);
	return leaf;
}

bool Background:: init(const char* filename, float ratio) {
	if (!CCNode::init()) {return false;}

	mRatio = ratio;

    setTag(BACKGROUND);
    addChild(createLeaf(filename, ccp(0,0)), 0);
	addChild(createLeaf(filename, ccp(0,1)), 0);
	addChild(createLeaf(filename, ccp(1,0)), 0);
	CCSprite* leaf = createLeaf(filename, ccp(1,1));
	addChild(leaf, 0);

	CCSize contentSize = leaf->getContentSize() * 2;
	setContentSize(contentSize);

	return true;
}
