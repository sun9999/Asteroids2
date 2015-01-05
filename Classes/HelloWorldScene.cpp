#include "HelloWorldScene.h"
#include "MoveableObject.h"
#include "Asteroids.h"
#include "GameUtil.h"
#include "GameStart.h"
#include "Missle.h"
#include "Spaceship.h"
#include "EncryptedInt.h"
#include "AppMacros.h"
#include "Bullet.h"
#include "SimpleAudioEngine.h"
#include "Background.h"
#include <iostream>
#include <string>

USING_NS_CC;

CCScene* HelloWorld::scene() {
    CCScene *scene = CCScene::create();
    scene->addChild(HelloWorld::create());

    return scene;
}

const char* HelloWorld::lifeText() {
    stringstream lifeStream;
    lifeStream << "x " << getSpaceshipCount().decrypt();
    return lifeStream.str().c_str();
}

const char* HelloWorld::missileText() {
    stringstream missileStream;
    missileStream << "x " << getMissileCount().decrypt();
    return missileStream.str().c_str();
}


const char* HelloWorld::scoreText() {
    stringstream scoreStream;
    scoreStream << "Score: " << getScore().decrypt();

    return scoreStream.str().c_str();
}

bool HelloWorld::init() {
    if ( !CCLayer::init() ) {
        return false;
    }

    setMissileCount(INITIAL_MISSILE_COUNT);
    setSpaceshipCount(INITIAL_SPACESHIP_COUNT);
    
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
    CCPoint central = ccp(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y);
    
    CCSprite* lifeCountLabel = CCSprite::create("vtc/SHIP_A_01.png");
    lifeCountLabel->setAnchorPoint(ccp(0,0));
    lifeCountLabel->setTag(LABEL);
    lifeCountLabel->setScale(0.4);
    lifeCountLabel->setPosition(ccp(origin.x, origin.y+ visibleSize.height - lifeCountLabel->boundingBox().size.height));
    lifeCountLabel->setZOrder(99);
    addChild(lifeCountLabel);
    
    CCSprite* missileCountLabel = CCSprite::create("vtc/MISSILE.png");
    missileCountLabel->setAnchorPoint(ccp(0,0));
    missileCountLabel->setTag(LABEL);
    missileCountLabel->setScale(0.6);
    missileCountLabel->setPosition(ccp(origin.x+lifeCountLabel->boundingBox().size.width/2, origin.y+ visibleSize.height - lifeCountLabel->boundingBox().size.height + 5 - missileCountLabel->boundingBox().size.height));
    missileCountLabel->setZOrder(99);
    addChild(missileCountLabel);

    
    CCLabelTTF* pScoreLabel = CCLabelTTF::create("", "Arial", TITLE_FONT_SIZE);
    pScoreLabel->setTag(LABEL);
    pScoreLabel->setString(scoreText());
    pScoreLabel->setPosition(ccp(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - pScoreLabel->boundingBox().size.height));
    setScoreLabel(pScoreLabel);
    pScoreLabel->setZOrder(99);
    addChild(getScoreLabel());
    

    CCLabelTTF* lifeCountTxtLabel = CCLabelTTF::create("", "Arial", NORMAL_FONT_SIZE);
    lifeCountTxtLabel->setAnchorPoint(ccp(0, 0));
    lifeCountTxtLabel->setString(lifeText());
    lifeCountTxtLabel->setTag(LABEL);
    lifeCountTxtLabel->setPosition(ccp(lifeCountLabel->getPositionX()+5+lifeCountLabel->boundingBox().size.width, lifeCountLabel->getPositionY()+lifeCountLabel->boundingBox().size.width/2));
    lifeCountTxtLabel->setZOrder(99);
    setSpaceshipCountLabel(lifeCountTxtLabel);
    addChild(getSpaceshipCountLabel());
    
    CCLabelTTF* missileCountTxtLabel = CCLabelTTF::create("", "Arial", NORMAL_FONT_SIZE);
    missileCountTxtLabel->setAnchorPoint(ccp(0,0));
    missileCountTxtLabel->setString(missileText());
    missileCountTxtLabel->setTag(LABEL);
    missileCountTxtLabel->setPosition(ccp(lifeCountTxtLabel->getPositionX(), missileCountLabel->getPositionY() + missileCountLabel->boundingBox().size.width/2));
    missileCountTxtLabel->setZOrder(99);
    setMissileCountLabel(missileCountTxtLabel);
    addChild(getMissileCountLabel());


    CCMenuItemImage *pCloseItem = CCMenuItemImage::create(
                                        "vtc/power.png", "vtc/power.png",
                                        this, menu_selector(HelloWorld::menuCloseCallback));
    pCloseItem->setTag(GAME_MENU_OPTION);
    pCloseItem->setScale(0.35);
	pCloseItem->setPosition(ccp(origin.x + visibleSize.width - pCloseItem->boundingBox().size.width - MENU_BORDER, origin.y+MENU_BORDER));
    pCloseItem->setAnchorPoint(ccp(0, 0));

	CCMenuItemImage *pPauseOrResume = CCMenuItemImage::create(
										"vtc/hourglass.png", "vtc/hourglass.png",
										this, menu_selector(HelloWorld::playOrResumeCallback));
	pPauseOrResume->setScale(0.35);
    pPauseOrResume->setTag(GAME_MENU_OPTION);
	pPauseOrResume->setPosition(ccp(pCloseItem->getPositionX()-MENU_BORDER-pPauseOrResume->boundingBox().size.width, origin.y+MENU_BORDER));
    pPauseOrResume->setAnchorPoint(ccp(0, 0));

    CCMenuItemImage *pFireMissile = CCMenuItemImage::create("vtc/missle.png", "vtc/missle.png",
									this, menu_selector(HelloWorld::fireMissileCallBack));
    pFireMissile->setScale(0.35);
    pFireMissile->setTag(GAME_MENU_OPTION);
    pFireMissile->setPosition(ccp(pPauseOrResume->getPositionX()-MENU_BORDER-pFireMissile->boundingBox().size.width, origin.y+MENU_BORDER));
    pFireMissile->setAnchorPoint(ccp(0, 0));

    CCMenu* pMenu = CCMenu::create(pCloseItem, pPauseOrResume, pFireMissile, NULL);
    pMenu->setPosition(CCPointZero);
    pMenu->setTag(GAME_MENU);
    addChild(pMenu, 2);

    setSpaceship(Spaceship::create("vtc/SHIP_A_01.png"));
    getSpaceship()->setPosition(ccp(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    getSpaceship()->setTag(SPACESHIP);
    
    addChild(getSpaceship(), 1);
    CCLog("spaceship h:%5.2f, w:%5.2f", getSpaceship()->boundingBox().size.height, getSpaceship()->boundingBox().size.width);

    for (int i=0; i<genIR(15, 20); i++) {
    	CCPoint pos = getAsteroids()->convertToNodeSpace(GameUtil::genRandCCP(origin, visibleSize, SCREEN_BUFFER));
        getAsteroids()->addChild(Asteroids::create("vtc/rock.png", pos, calcAngleWithRandomFactor(central, pos)));
    }
    
    
    Background* bkg1 = Background::create("vtc/background_1.png", 3);
    Background* bkg2 = Background::create("vtc/background_2.png", 3.3);
    getBackgrounds()->addChild(bkg1, 0);
    getBackgrounds()->addChild(bkg2, 0);
    
    addChild(getAsteroids(), 1);
    addChild(getBullets(), 1);
    addChild(getMissiles(), 1);
    addChild(getBackgrounds(), 0);
    
    schedule(schedule_selector(HelloWorld::fireBullet), 1);  //automatically fire bullet for every second
    schedule(schedule_selector(HelloWorld::addAsteroid), 2); //automatically add asteroid for every 2 second
    schedule(schedule_selector(HelloWorld::updateGame));
    
    setTouchEnabled(true);

    return true;
}

void HelloWorld::fireBullet() {
	CCPoint pos = GameUtil::calcPositionAfterMovment(getSpaceship()->getPosition(), getSpaceship()->getAngle(), getSpaceship()->boundingBox().size.height/2);
    
    Bullet* bullet = Bullet::create("vtc/BULLET.png", getBullets()->convertToNodeSpace(pos), getSpaceship()->getAngle());
    getBullets()->addChild(bullet);
}

float HelloWorld::calcAngleWithRandomFactor(const CCPoint& central, const CCPoint& asteroidPos) {
	float angle = GameUtil::calcAngle(central, asteroidPos) * genFR(0.66, 1.33);
	if (angle < 0) {
		angle = 0;
	} else if (angle > 360) {
		angle = 360;
	}

	return angle;
}

void HelloWorld::addAsteroid() {
	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
	CCPoint central = ccp(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y);

    if (getAsteroids()->getChildren() && getAsteroids()->getChildren()->count() < MAX_ASTEROIDS) {
        for (int i=0; i<genIR(2, 5); i++) {
        	CCPoint pos = getAsteroids()->convertToNodeSpace(GameUtil::genRandCCP(origin, visibleSize, SCREEN_BUFFER));
            getAsteroids()->addChild(Asteroids::create("vtc/rock.png", pos, calcAngleWithRandomFactor(central, pos)));
        }
    }
}

void HelloWorld::resetMissiles(Asteroids* asteroid) {
	//check if asteroid outside the buffer zone and need to remove
	CCObject* iterator3 = NULL;
	CCARRAY_FOREACH(getMissiles()->getChildren(), iterator3) { //reset the missiles if it has the same target
		Missle* iterNode3 = dynamic_cast<Missle*>(iterator3);
		if (iterNode3->getTarget() == asteroid) {
			iterNode3->setTarget(NULL);
		}
	}
}

void HelloWorld::arrangeBuckets(float min_x, float max_x, float min_y, float max_y,
		const CCPoint& origin, const CCSize& visibleSize,
		CCArray* objBuckets[COLLISION_BUCKET_WIDTH][COLLISION_BUCKET_HEIGHT]) {
	CCObject* iterator = NULL;
    
    CCLog("asteroid children count: %d", getAsteroids()->getChildrenCount());
	CCARRAY_FOREACH(getAsteroids()->getChildren(), iterator) {
        if (iterator==NULL) {continue;}
		Asteroids* asteroid = dynamic_cast<Asteroids*>(iterator);
        if (asteroid==NULL) {continue;}
		float x = getAsteroids()->convertToWorldSpace(asteroid->getPosition()).x;
		float y = getAsteroids()->convertToWorldSpace(asteroid->getPosition()).y;
//		float x = asteroid->getPositionX(), y = asteroid->getPositionY();

		if (x < min_x || x > max_x || y < min_y || y > max_y) { //check if asteroid outside the buffer zone and need to remove
            resetMissiles(asteroid);
			getAsteroids()->removeChild(asteroid);
            CC_SAFE_RELEASE_NULL(asteroid);
		} else if (x >= origin.x-20 && x <= origin.x + visibleSize.width+20
				&& y >= origin.y-20 && y <= origin.y + visibleSize.height+20) { //check if the asteroid is visible on screen + buffer
			int w = (x - origin.x-20) / ((visibleSize.width+20*2) / COLLISION_BUCKET_WIDTH);
			int h = (y - origin.y-20) / ((visibleSize.height+20*2) / COLLISION_BUCKET_HEIGHT);
			if (w <= COLLISION_BUCKET_WIDTH && h <= COLLISION_BUCKET_HEIGHT) { //double check the w and h to avoid the index outbound problem
				if (objBuckets[w][h]==NULL) { //if the bucket is empty, create an array for it
					objBuckets[w][h] = CCArray::create();
				}
				objBuckets[w][h]->addObject(asteroid);
			}
		}
	}
    
    CCARRAY_FOREACH(getMissiles()->getChildren(), iterator) {
        Missle* missile = dynamic_cast<Missle*>(iterator);
        float x = getMissiles()->convertToWorldSpace(missile->getPosition()).x;
        float y = getMissiles()->convertToWorldSpace(missile->getPosition()).y;
//        float x=missile->getPositionX(), y=missile->getPositionY();
        
		if (x < min_x || x > max_x || y < min_y || y > max_y) { //check if missile outside the buffer zone and need to remove
            getMissiles()->removeChild(missile);
            CC_SAFE_RELEASE_NULL(missile);
        } else if (x >= origin.x-20 && x <= origin.x + visibleSize.width+20
                  && y >= origin.y-20 && y <= origin.y + visibleSize.height+20) { //check if the missile is visible on screen + buffer
            int w = (x - origin.x-20) / ((visibleSize.width+20*2) / COLLISION_BUCKET_WIDTH);
			int h = (y - origin.y-20) / ((visibleSize.height+20*2) / COLLISION_BUCKET_HEIGHT);
			if (w <= COLLISION_BUCKET_WIDTH && h <= COLLISION_BUCKET_HEIGHT) { //double check the w and h to avoid the index outbound problem
				if (objBuckets[w][h]==NULL) { //if the bucket is empty, create an array for it
					objBuckets[w][h] = CCArray::create();
				}
				objBuckets[w][h]->addObject(missile);
			}
        }
    }
    
    CCARRAY_FOREACH(getBullets()->getChildren(), iterator) {
        Bullet* bullet = dynamic_cast<Bullet*>(iterator);
        float x=getBullets()->convertToWorldSpace(bullet->getPosition()).x;
        float y=getBullets()->convertToWorldSpace(bullet->getPosition()).y;
//        float x=bullet->getPositionX(), y=bullet->getPositionY();
        
		if (x < min_x || x > max_x || y < min_y || y > max_y) { //check if bullet outside the buffer zone and need to remove
            getBullets()->removeChild(bullet);
            CC_SAFE_RELEASE_NULL(bullet);
        } else if (x >= origin.x-20 && x <= origin.x + visibleSize.width+20
                   && y >= origin.y-20 && y <= origin.y + visibleSize.height+20) { //check if the bullet is visible on screen + buffer
            int w = (x - origin.x-20) / ((visibleSize.width+20*2) / COLLISION_BUCKET_WIDTH);
			int h = (y - origin.y-20) / ((visibleSize.height+20*2) / COLLISION_BUCKET_HEIGHT);
			if (w <= COLLISION_BUCKET_WIDTH && h <= COLLISION_BUCKET_HEIGHT) { //double check the w and h to avoid the index out-bound problem
				if (objBuckets[w][h]==NULL) { //if the bucket is empty, create an array for it
					objBuckets[w][h] = CCArray::create();
				}
				objBuckets[w][h]->addObject(bullet);
			}
        }
    }

}

CCParticleExplosion* HelloWorld::createExplosion(const char* image, CCPoint pos, float startSize, float endSize) {
	CCParticleExplosion* pExplosion = CCParticleExplosion::create();
	pExplosion->retain();
	pExplosion->setTexture(CCTextureCache::sharedTextureCache()->addImage(image));
	pExplosion->setAutoRemoveOnFinish(true);
	pExplosion->setPosition(pos);
	pExplosion->setStartSize(startSize);
	pExplosion->setEndSize(endSize);

	return pExplosion;
}

void HelloWorld::updateGame(float delta) {
    
    if (getSpaceship()->isThrust()) {
        
    } else {
    }
    
	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
    CCArray* objBuckets[COLLISION_BUCKET_WIDTH][COLLISION_BUCKET_HEIGHT] = {NULL};

    float min_x = origin.x - SCREEN_BUFFER;
    float max_x = origin.x + visibleSize.width + SCREEN_BUFFER;
    float min_y = origin.y - SCREEN_BUFFER;
    float max_y = origin.y + visibleSize.height + SCREEN_BUFFER;
    
    
//    getAsteroids()->setPosition(getAsteroids()->getPositionX()+.5, getAsteroids()->getPositionY()); //TODO

    //TODO check the collision between the spaceship and the asteroids
//    int sW = (getSpaceship()->getPositionX()-origin.x)/(visibleSize.width/COLLISION_BUCKET_WIDTH);
//    int sH = (getSpaceship()->getPositionY()-origin.y)/(visibleSize.height/COLLISION_BUCKET_HEIGHT);
//    CCLog("bucket index w:%d h:%d", sW, sH);

	arrangeBuckets(min_x, max_x, min_y, max_y, origin, visibleSize, objBuckets);
    

    for (int w=0; w<COLLISION_BUCKET_WIDTH; w++) {
    	for (int h=0; h<COLLISION_BUCKET_HEIGHT; h++) {
    		if (objBuckets[w][h]==NULL || objBuckets[w][h]->count()<=1) {continue;}
			//more than one object within the bucket
//			CCLog("bucket[%d][%d]: %d", w, h, objBuckets[w][h]->count());
			CCObject* iterator = NULL;
            
			CCARRAY_FOREACH(objBuckets[w][h], iterator) {
				CCNode* iterNode = dynamic_cast<CCNode*>(iterator);
				if (iterNode->getTag()==MISSILE) {
                    CCObject* iterator2 = NULL;
                    CCARRAY_FOREACH(objBuckets[w][h], iterator2) {
                        CCNode* iterNode2 = dynamic_cast<CCNode*>(iterator2);
                        if (iterNode==iterNode2) {continue;}
                        if (iterNode2->getTag()!=ASTEROID) {continue;}
                        float r1 = iterNode->boundingBox().size.width/2;
                        float r2 = iterNode2->boundingBox().size.width/2;
                        float x1 = getMissiles()->convertToWorldSpace(iterNode->getPosition()).x, y1=getMissiles()->convertToWorldSpace(iterNode->getPosition()).y;
                        float x2 = getAsteroids()->convertToWorldSpace(iterNode2->getPosition()).x, y2=getAsteroids()->convertToWorldSpace(iterNode2->getPosition()).y;
                        
                        if ((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2) < (r1+r2)*(r1+r2)) {
                            //collision
                        	resetMissiles(dynamic_cast<Asteroids*> (iterNode2));
                            CCParticleExplosion* pExplosion =createExplosion("vtc/rock_break.png", iterNode->getPosition(), 0.2, 0.5);

                            objBuckets[w][h]->removeObject(iterNode);
                            objBuckets[w][h]->removeObject(iterNode2);
                            getMissiles()->removeChild(iterNode);
                            getAsteroids()->removeChild(iterNode2);

                            CC_SAFE_RELEASE_NULL(iterNode);
                            CC_SAFE_RELEASE_NULL(iterNode2);
                            
                            CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("vtc/explosion_medium.mp3");
                            addChild(pExplosion);
                            
                            setScore(getScore().decrypt()+100);
                            getScoreLabel()->setString(scoreText());
                            break;
                        }
                    }
                } else if (iterNode->getTag()==BULLET) {
                	CCObject* iterator2 = NULL;
					CCARRAY_FOREACH(objBuckets[w][h], iterator2) {
						CCNode* iterNode2 = dynamic_cast<CCNode*>(iterator2);
						if (iterNode==iterNode2) {continue;}
						if (iterNode2->getTag()!=ASTEROID) {continue;}
                        float r1 = iterNode->boundingBox().size.width/2;
						float r2 = iterNode2->boundingBox().size.width/2;
                        float x1 = getBullets()->convertToWorldSpace(iterNode->getPosition()).x, y1=getBullets()->convertToWorldSpace(iterNode->getPosition()).y;
                        float x2 = getAsteroids()->convertToWorldSpace(iterNode2->getPosition()).x, y2=getAsteroids()->convertToWorldSpace(iterNode2->getPosition()).y;

						if ((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2) < (r1+r2)*(r1+r2)) {
							if (iterNode2->getScale()>=MIN_SIZE && iterNode2->getScale()<ASTEROID_CLASS_1) {
								CCParticleExplosion* pExplosion =createExplosion("vtc/rock_break.png", iterNode->getPosition(), 0.1, 0.2);
								addChild(pExplosion);
								CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("vtc/explosion_medium.mp3");
								setScore(getScore().decrypt()+100);
								getScoreLabel()->setString(scoreText());
							} else {
								//break down the rock
								Asteroids* asteroid = dynamic_cast<Asteroids*>(iterNode2);
								
								float angle1 = asteroid->getAngle() - ASTEROID_BREAK_ANGLE;
								float angle2 = asteroid->getAngle() + ASTEROID_BREAK_ANGLE;

								angle1 = (angle1<0) ? angle1+360: angle1;
								angle2 = (angle2>360) ? angle2-360: angle2;

								Asteroids* asteroid1 = Asteroids::create("vtc/rock.png");
								asteroid1->setScale(asteroid->getScale()/2);
								asteroid1->setAngle(angle1);
								asteroid1->setSpeed(asteroid->getSpeed());
                                asteroid1->setPosition(asteroid->getPosition());

								Asteroids* asteroid2 = Asteroids::create("vtc/rock.png");
								asteroid2->setScale(asteroid->getScale()/2);
								asteroid2->setAngle(angle2);
								asteroid2->setSpeed(asteroid->getSpeed());
                                asteroid2->setPosition(asteroid->getPosition());
                                
                                getAsteroids()->addChild(asteroid1);
                                getAsteroids()->addChild(asteroid2);

								CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("vtc/explosion_small.mp3");

							}
							resetMissiles(dynamic_cast<Asteroids*> (iterNode2));
							objBuckets[w][h]->removeObject(iterNode);
							objBuckets[w][h]->removeObject(iterNode2);
							getBullets()->removeChild(iterNode);
							getAsteroids()->removeChild(iterNode2);
							CC_SAFE_RELEASE_NULL(iterNode);
							CC_SAFE_RELEASE_NULL(iterNode2);
                            break;
						}
					}
                }
			}
    	}
    }
    
}

void HelloWorld::menuCloseCallback(CCObject* pSender) {
    if (CCDirector::sharedDirector()->isPaused()) {
        CCDirector::sharedDirector()->resume();
    }
    CCDirector::sharedDirector()->replaceScene(GameStart::scene());
}

void HelloWorld::playOrResumeCallback(CCObject* pSender) {
    CCMenuItemImage* pPauseOrResume = dynamic_cast<CCMenuItemImage*>(pSender);
    
    if (CCDirector::sharedDirector()->isPaused()) {
        CCDirector::sharedDirector()->resume();
        pPauseOrResume->setNormalImage(CCSprite::create("vtc/hourglass.png"));
    } else {
        CCDirector::sharedDirector()->pause();
        pPauseOrResume->setNormalImage(CCSprite::create("vtc/play.png"));
    }
}

Asteroids* HelloWorld::getClosestAsteroid(CCPoint pos) {//get the asteroid that closest to the ship, it might behind the ship, not the one in the front
    if (getAsteroids()==NULL || getAsteroids()->getChildrenCount()==0) {return NULL;}
    
    CCObject* iterator = NULL;
    Asteroids* closestAsteroid = NULL;
    float shortestDist;
    
	CCARRAY_FOREACH(getAsteroids()->getChildren(), iterator) {
		Asteroids* asteroid = dynamic_cast<Asteroids*>(iterator);
		float x = getAsteroids()->convertToWorldSpace(asteroid->getPosition()).x;
		float y = getAsteroids()->convertToWorldSpace(asteroid->getPosition()).y;

        float dist = sqrtf((x-pos.x)*(x-pos.x) + (y-pos.y)*(y-pos.y)) - getSpaceship()->boundingBox().size.width/2 - asteroid->boundingBox().size.width/2;
        
        if (dist<shortestDist || closestAsteroid==NULL) {
            closestAsteroid = asteroid;
            shortestDist = dist;
        }
    }
    
    return closestAsteroid;
}

void HelloWorld::fireMissileCallBack(CCObject* pSender) {
    if (CCDirector::sharedDirector()->isPaused()) {return;}
    if (getMissileCount()<=0) {return;}
    
    CCPoint missilePos = GameUtil::calcPositionAfterMovment(getSpaceship()->getPosition(), getSpaceship()->getAngle(), getSpaceship()->boundingBox().size.height/2);
    
    Asteroids* pTarget=getClosestAsteroid(getSpaceship()->getPosition()); //get the asteroid that closest to the ship, it might behind the ship, not the one in the front
    
//    CCLog("pTarget x:%5.2f y:%5.2f", pTarget->getPositionX(), pTarget->getPositionY());
    
    Missle* pMissile = Missle::create("vtc/MISSILE.png", getMissiles()->convertToNodeSpace(missilePos), pTarget);
    pMissile->setAngle(getSpaceship()->getAngle());
    getMissiles()->addChild(pMissile);
    setMissileCount(((int) getMissileCount())-1);
    getMissileCountLabel()->setString(missileText());
}


void HelloWorld::ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent) {
    getSpaceship()->setThrust(true);
    
//    CCSetIterator it = pTouches->begin();
//    CCTouch* pTouch = (CCTouch*)(*it);
    
    CCLayer::ccTouchesBegan(pTouches, pEvent);
}

void HelloWorld::ccTouchesEnded( CCSet* pTouches, CCEvent* pEvent) {
    getSpaceship()->setThrust(false);
    
    CCLayer::ccTouchesEnded(pTouches, pEvent);
}

void HelloWorld::setAngle(float angle) {
	mAngle = angle;
}

float HelloWorld::getAngle() {
	return mAngle;
}
