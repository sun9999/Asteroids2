//
//  Background.h
//

#ifndef BACKGROUND_H_
#define BACKGROUND_H_

#include "cocos2d.h"
#include "MoveableObject.h"

USING_NS_CC;

class Background : public MoveableObject {
private:
	int mRatio;
	CCSprite* createLeaf(const char*, CCPoint);
public:
    static Background* Create(const char*, float);
    bool init(const char*, float);
    virtual bool init();
    virtual void update(float);
};

#endif
