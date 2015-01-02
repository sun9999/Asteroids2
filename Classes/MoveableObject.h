/*
 * MoveableObject.h
 *
 *  Created on: 12 Dec, 2014
 *      Author: sip
 */

#ifndef MOVEABLEOBJECT_H_
#define MOVEABLEOBJECT_H_

#define CREATE_FUNC2(__TYPE__) \
static __TYPE__* create(const char* filename) { \
    __TYPE__ *pRet = new __TYPE__(); \
    if (pRet && pRet->init(filename)) { \
        pRet->autorelease(); \
        return pRet; \
    } else { \
        delete pRet; \
        pRet = NULL; \
        return NULL; \
    } \
}

#include "cocos2d.h"
#include <cocoa/CCGeometry.h>


USING_NS_CC;

class MoveableObject : public CCSprite {
private:
	float mAngle;			//Rotation angle (degree)
	float mSpeed;			//movement/frame
	float mAcceleration;
public:
	virtual bool init()=0;

	virtual void updateDisplayedOpacity(GLubyte);

	virtual void setOpacity(GLubyte);

	float getAngle();

	void setAngle(float);

	float getAcceleration();

	void setAcceleration(float);

	float getSpeed();

	void setSpeed(float);
};



#endif /* MOVEABLEOBJECT_H_ */
