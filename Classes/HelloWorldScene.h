#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "Asteroids.h"
#include "Spaceship.h"
#include "Missle.h"
#include "MoveableObject.h"
#include <vector>

USING_NS_CC;
using namespace std;

class HelloWorld : public CCLayer {
private:
	int mScore; //TODO use EncryptedInt
    int mMissileCount; //TODO
    int mSpaceshipCount; //TODO
    CCNode* mAsteroids;
    CCNode* mBullets;
    CCNode* mMissiles;
    Spaceship* mSpaceship;

	void arrangeBuckets(float min_x, float max_x, float min_y, float max_y,
			const CCPoint& origin, const CCSize& visibleSize,
			CCArray* objBuckets[COLLISION_BUCKET_WIDTH][COLLISION_BUCKET_HEIGHT]);
    
    Asteroids* getClosestAsteroid(CCPoint);
public:
    static CCScene* scene();
    
    virtual bool init();
    
    void addAsteroid();

    void updateGame(float);

    void menuCloseCallback(CCObject*);
    
    void playOrResumeCallback(CCObject*);
    
    void fireMissileCallBack(CCObject*);

    CREATE_FUNC(HelloWorld);

	Spaceship* getSpaceship() {
		return mSpaceship;
	}

	void setSpaceship(Spaceship* spaceship) {
		mSpaceship = spaceship;
	}

	CCNode* getAsteroids() {
        if (mAsteroids==NULL) {
            mAsteroids = CCNode::create();
        }
		return mAsteroids;
	}

	void setAsteroids(CCNode* asteroids) {
		mAsteroids = asteroids;
	}

	CCNode* getBullets() {
		return mBullets;
	}

	void setBullets(CCNode* bullets) {
		mBullets = bullets;
	}

	CCNode* getMissiles() {
        if (mMissiles==NULL) {
            mMissiles = CCNode::create();
        }
		return mMissiles;
	}

	void setMissiles(CCNode* missiles) {
		mMissiles = missiles;
	}

	int getMissileCount() {
		return mMissileCount;
	}

	void setMissileCount(int missileCount) {
		mMissileCount = missileCount;
	}

	int getSpaceshipCount() {
		return mSpaceshipCount;
	}

	void setSpaceshipCount(int spaceshipCount) {
		mSpaceshipCount = spaceshipCount;
	}

	int getScore() {
		return mScore;
	}

	void setScore(int score) {
		mScore = score;
	}
};

#endif // __HELLOWORLD_SCENE_H__
