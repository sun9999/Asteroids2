#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "Asteroids.h"
#include "Spaceship.h"
#include "Missle.h"
#include "MoveableObject.h"
#include "EncryptedInt.h"
#include <vector>

USING_NS_CC;
using namespace std;

class HelloWorld : public CCLayer {
private:
	EncryptedInt mScore;
    EncryptedInt mMissileCount;
    EncryptedInt mSpaceshipCount;
    CCNode* mAsteroids;
    CCNode* mBullets;
    CCNode* mMissiles;
    CCNode* mBackgrounds;
    Spaceship* mSpaceship;

    CCLabelTTF* mScoreLabel;
    CCLabelTTF* mSpaceshipCountLabel;
    CCLabelTTF* mMissileCountLabel;
    
	void arrangeBuckets(float min_x, float max_x, float min_y, float max_y,
			const CCPoint& origin, const CCSize& visibleSize,
			CCArray* objBuckets[COLLISION_BUCKET_WIDTH][COLLISION_BUCKET_HEIGHT]);
    
    Asteroids* getClosestAsteroid(CCPoint);

    CCParticleExplosion* createExplosion(const char*, CCPoint, float, float);
    
    float calcAngleWithRandomFactor(const CCPoint&, const CCPoint&);

    const char* scoreText();
    const char* lifeText();
    const char* missileText();
	void resetMissiles(Asteroids* asteroid);

public:
    static CCScene* scene();
    
    virtual bool init();
    
    void fireBullet();
    
    void addAsteroid();

    void updateGame(float);

    void menuCloseCallback(CCObject*);
    
    void playOrResumeCallback(CCObject*);
    
    void fireMissileCallBack(CCObject*);

    CREATE_FUNC(HelloWorld);
    
    CCLabelTTF* getScoreLabel() {
        return mScoreLabel;
    }
    
    void setScoreLabel(CCLabelTTF* label) {
        mScoreLabel = label;
    }
    
    CCLabelTTF* getSpaceshipCountLabel() {
        return mSpaceshipCountLabel;
    }
    
    void setSpaceshipCountLabel(CCLabelTTF* label) {
        mSpaceshipCountLabel = label;
    }
    
    CCLabelTTF* getMissileCountLabel() {
        return mMissileCountLabel;
    }
    
    void setMissileCountLabel(CCLabelTTF* label) {
        mMissileCountLabel = label;
    }

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
        if (mBullets==NULL) {
            mBullets= CCNode::create();
        }
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

	EncryptedInt getMissileCount() {
		return mMissileCount;
	}

	void setMissileCount(int missileCount) {
		mMissileCount = missileCount;
	}

	EncryptedInt getSpaceshipCount() {
		return mSpaceshipCount;
	}

	void setSpaceshipCount(int spaceshipCount) {
		mSpaceshipCount = spaceshipCount;
	}

	EncryptedInt getScore() {
		return mScore;
	}

	void setScore(int score) {
		mScore = score;
	}

	CCNode* getBackgrounds() {
        if (mBackgrounds==NULL) {
            mBackgrounds = CCNode::create();
        }
		return mBackgrounds;
	}

	void setBackgrounds(CCNode* backgrounds) {
		mBackgrounds = backgrounds;
	}
    
    void ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent);

    void ccTouchesEnded( CCSet* pTouches, CCEvent* pEvent);
};

#endif // __HELLOWORLD_SCENE_H__
