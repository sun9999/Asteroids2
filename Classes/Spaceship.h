/*
 * Spaceship.h
 *
 *  Created on: 2 Jan, 2015
 *      Author: sip
 */

#ifndef SPACESHIP_H_
#define SPACESHIP_H_

#include "GameUtil.h"
#include "cocos2d.h"
#include "MoveableObject.h"

USING_NS_CC;

class Spaceship: public MoveableObject {
public:
    CREATE_FUNC2(Spaceship)
    
    virtual bool init();
    
    virtual bool init(const char*);
};



#endif /* SPACESHIP_H_ */
