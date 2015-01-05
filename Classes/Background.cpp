//
//  Background.cpp
//
#include "Background.h"

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

	addChild(createLeaf(filename, ccp(0,1)));
	addChild(createLeaf(filename, ccp(0,0)));
	addChild(createLeaf(filename, ccp(1,0)));
	CCSprite* leaf = createLeaf(filename, ccp(1,1));
	addChild(leaf);

	CCSize contentSize = leaf->getContentSize() * 2;
	setContentSize(contentSize);

	return true;
}



//void Background::UpdatePosition(CCPoint displacement) {

	//CCpoint current = getPosition();

	//current = current - displacement * mRatio;

	//use CCDirector to get the visible size


	//valid screen coordinate can only be visible size - content size/2 to content size/2

	//CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	//CCSize size = getContentSize();

	//calcuate the min x, y and max x,y

	//reposition if the current position reach the min x,y
	//reposition if the current position reach the max x,y


//}
