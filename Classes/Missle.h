/*
 * Missle.h
 *
 *  Created on: 1 Jan, 2015
 *      Author: sip
 */

#ifndef MISSLE_H_
#define MISSLE_H_

#include "GameUtil.h"
#include "cocos2d.h"
#include "MoveableObject.h"

USING_NS_CC;

class Missle: public MoveableObject {
private:
	CCNode* mTarget;
public:
    static Missle* Create(const char*, const CCPoint, CCNode*);

	bool init(const char*);

	bool init(const char*, const CCPoint, CCNode*);

	virtual bool init();

	virtual void update(float);
    
    void changeDirection();
    

    CCNode* getTarget() const {
		return mTarget;
	}

	void setTarget(CCNode* target) {
        mTarget = target;
	}
};



#endif /* MISSLE_H_ */
