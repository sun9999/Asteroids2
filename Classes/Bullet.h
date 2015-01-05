/*
 * Bullet.h
 *
 *  Created on: 4 Jan, 2015
 *      Author: sip
 */

#ifndef BULLET_H_
#define BULLET_H_

#include "GameUtil.h"
#include "cocos2d.h"
#include "MoveableObject.h"

USING_NS_CC;

class Bullet: public MoveableObject {
private:
public:
	CREATE_FUNC2(Bullet)
	static Bullet* create(const char*, const CCPoint, float);

	bool init(const char*);

	bool init(const char*, const CCPoint, float);

	virtual bool init();

	virtual void update(float);
};



#endif /* BULLET_H_ */
