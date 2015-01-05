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

/**
 A Note around the vector angle:
 The angele stored here is the vector angle,
 it indicates the position that the vector pointing to;
 While the rotation angle indicates where the object facing.
 With the support of this angle, the object is possible to face north, but
 moving south. All the vector for my design are on default facing downward,
 hence, while the mAngle is zero degree, the vector is pointing south, rather than
 pointing north. Therefore, there is a 180 degree differences between the rotation angle and
 this vector angle.
 */

class MoveableObject : public CCSprite {
private:
	float mAngle;			//vector angle (degree)
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
