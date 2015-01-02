#include "HelloWorldScene.h"
#include "MoveableObject.h"
#include "Asteroids.h"
#include "GameUtil.h"
#include "GameStart.h"
#include "Missle.h"
#include "Spaceship.h"

USING_NS_CC;

CCScene* HelloWorld::scene() {
    CCScene *scene = CCScene::create();
    scene->addChild(HelloWorld::create());

    return scene;
}

bool HelloWorld::init() {
    if ( !CCLayer::init() ) {
        return false;
    }
    
    setMissileCount(INITIAL_MISSILE_COUNT);
    setSpaceshipCount(INITIAL_SPACESHIP_COUNT);
    
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

    CCLog("HelloWorld::visibleSize w:%5.2f, h:%5.2f", visibleSize.width, visibleSize.height);
    CCLog("HelloWorld::origin x:%5.2f, y:%5.2f", origin.x, origin.y);

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

    CCMenuItemImage *pFireMissile = CCMenuItemImage::create(
									"vtc/missle.png", "vtc/missle.png",
									this, menu_selector(HelloWorld::fireMissileCallBack));
    pFireMissile->setScale(0.35);
    pFireMissile->setTag(GAME_MENU_OPTION);
    pFireMissile->setPosition(ccp(pPauseOrResume->getPositionX()-MENU_BORDER-pFireMissile->boundingBox().size.width, origin.y+MENU_BORDER));
    pFireMissile->setAnchorPoint(ccp(0, 0));

    CCMenu* pMenu = CCMenu::create(pCloseItem, pPauseOrResume, pFireMissile, NULL);
    pMenu->setPosition(CCPointZero);
    pMenu->setTag(GAME_MENU);
    addChild(pMenu, 1);

    setSpaceship(Spaceship::create("vtc/SHIP_A_01.png"));
    getSpaceship()->setPosition(ccp(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    getSpaceship()->setTag(SPACESHIP);
    addChild(getSpaceship(), 0);
    CCLog("spaceship h:%5.2f, w:%5.2f", getSpaceship()->boundingBox().size.height, getSpaceship()->boundingBox().size.width);

    for (int i=0; i<genIR(15, 20); i++) {
        getAsteroids()->addChild(Asteroids::create("vtc/rock.png"));
    }
    addChild(getAsteroids());
    
    addChild(getMissiles());
    
    schedule(schedule_selector(HelloWorld::addAsteroid), 2);
    schedule(schedule_selector(HelloWorld::updateGame));

    return true;
}

void HelloWorld::addAsteroid() {
    if (getAsteroids()->getChildren() && getAsteroids()->getChildren()->count() < MAX_ASTEROIDS) {
        for (int i=0; i<genIR(2, 5); i++) {
            getAsteroids()->addChild(Asteroids::create("vtc/rock.png"));
        }
    }
}

void HelloWorld::arrangeBuckets(float min_x, float max_x, float min_y, float max_y,
		const CCPoint& origin, const CCSize& visibleSize,
		CCArray* objBuckets[COLLISION_BUCKET_WIDTH][COLLISION_BUCKET_HEIGHT]) {
	CCObject* iterator = NULL;
    
	CCARRAY_FOREACH(getAsteroids()->getChildren(), iterator) {
		Asteroids* asteroid = dynamic_cast<Asteroids*>(iterator);
		float x = asteroid->getPositionX(), y = asteroid->getPositionY();

		if (x < min_x || x > max_x || y < min_y || y > max_y) { //check if asteroid outside the buffer zone and need to remove
            
            CCObject* iterator3 = NULL;
            CCARRAY_FOREACH(getMissiles()->getChildren(), iterator3) { //reset the missiles if it has the same target
                Missle* iterNode3 = dynamic_cast<Missle*>(iterator3);
                if (iterNode3->getTarget()==asteroid) {
                    iterNode3->setTarget(NULL);
                }
            }
            
			getAsteroids()->removeChild(asteroid);
            CC_SAFE_RELEASE_NULL(asteroid);
		} else if (x >= origin.x-20 && x <= origin.x + visibleSize.width+20
				&& y >= origin.y-20 && y <= origin.y + visibleSize.height+20) { //check if the asteroid is visible on screen //TODO add buffer
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
        float x=missile->getPositionX(), y=missile->getPositionY();
        
		if (x < min_x || x > max_x || y < min_y || y > max_y) { //check if missile outside the buffer zone and need to remove
            getMissiles()->removeChild(missile);
            CC_SAFE_RELEASE_NULL(missile);
        } else if (x >= origin.x-20 && x <= origin.x + visibleSize.width+20
                  && y >= origin.y-20 && y <= origin.y + visibleSize.height+20) { //check if the missile is visible on screen //TODO add buffer
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
}

void HelloWorld::updateGame(float delta) {
	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
    CCArray* objBuckets[COLLISION_BUCKET_WIDTH][COLLISION_BUCKET_HEIGHT] = {NULL};

    float min_x = origin.x - SCREEN_BUFFER;
    float max_x = origin.x + visibleSize.width + SCREEN_BUFFER;
    float min_y = origin.y - SCREEN_BUFFER;
    float max_y = origin.y + visibleSize.height + SCREEN_BUFFER;
    
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
                        if (iterNode2->getTag()!=ASTEROID && iterNode2->getTag()!=ASTEROID) {continue;}
                        float r1 = iterNode->boundingBox().size.width/2;
                        float r2 = iterNode2->boundingBox().size.width/2;
                        float x1 = iterNode->getPositionX(), y1=iterNode->getPositionY();
                        float x2 = iterNode2->getPositionX(), y2=iterNode2->getPositionY();
                        
                        if ((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2) < (r1+r2)*(r1+r2)) {
                            //collision
                            
                            
                            CCObject* iterator3 = NULL;
                            CCARRAY_FOREACH(getMissiles()->getChildren(), iterator3) { //reset the missiles if it has the same target
                                Missle* iterNode3 = dynamic_cast<Missle*>(iterator3);
                                if (iterNode==iterNode3) {continue;}
                                if (iterNode3->getTarget()==iterNode2) {
                                    iterNode3->setTarget(NULL);
                                }
                            }
                            
                            objBuckets[w][h]->removeObject(iterNode);
                            objBuckets[w][h]->removeObject(iterNode2);
                            getMissiles()->removeChild(iterNode);
                            getAsteroids()->removeChild(iterNode2);
                            
                            CC_SAFE_RELEASE_NULL(iterNode);
                            CC_SAFE_RELEASE_NULL(iterNode2);
                            
                            
                            //TODO show expo effect...
                            break;
                        }
                    }
                }
			}
    	}
    }
    
//    CCObject* iterator = NULL;
//    CCARRAY_FOREACH(getMissiles()->getChildren(), iterator) {
//        Missle* iterNode = dynamic_cast<Missle*>(iterator);
//        if (iterNode->getTarget()!=NULL) {
//            iterNode->setAngle(GameUtil::calcAngle(iterNode->getTarget()->getPosition(), iterNode->getPosition()));
//            iterNode->setRotation(iterNode->getAngle() -180);
    
//            iterNode->setRotation(iterNode->getPosition().cross(iterNode->getTarget()->getPosition()));
//            iterNode->setAngle(iterNode->getRotation()+180);
            
//            CCLog("missle angle:%5.2f, rotation:%5.2f", iterNode->getAngle(), iterNode->getRotation());
//            CCLog("cross:%5.2f", iterNode->getPosition().cross(iterNode->getTarget()->getPosition()));
//        }
//        iterNode->setPosition(GameUtil::calcPositionAfterMovment(iterNode->getPosition(), iterNode->getAngle(), iterNode->getSpeed()));
//    }

    
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
        float x = asteroid->getPositionX(), y = asteroid->getPositionY();
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
    
    Missle* pMissile = Missle::Create("vtc/MISSILE.png", missilePos, pTarget);
    pMissile->setAngle(getSpaceship()->getAngle());
//    pMissile->schedule(schedule_selector(Missle::changeDirection), 0, 0, 5);
    getMissiles()->addChild(pMissile);
    setMissileCount(getMissileCount()-1);
}
