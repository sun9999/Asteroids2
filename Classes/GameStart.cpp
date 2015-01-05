/*
 * GameScene.cpp
 *
 *  Created on: 21 Dec, 2014
 *      Author: Sunny Ho, Ip
 */

#include "GameStart.h"
#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include "GameUtil.h"
#include "Background.h"

USING_NS_CC;
using namespace std;

GameStart::GameStart() {
	gameStatus = GAME_INTRO_SCREEN;
}

GameStart::~GameStart() {}

CCLabelTTF* GameStart::createGameStartLabel(const char* labelText, const char* font,
                                            int fontSize, const CCSize visibleSize, const CCPoint origin) {
    

	CCLabelTTF* pLabel = CCLabelTTF::create(labelText, font, fontSize);
	pLabel->setPosition(ccp(origin.x + visibleSize.width/2, origin.y + pLabel->getContentSize().height));
	return pLabel;
}

CCMenu* GameStart::createGameMenu(const CCSize visibleSize, const CCPoint origin) {
	CCMenuItemImage *pCloseItem = CCMenuItemImage::create(
	                                        "vtc/CloseNormal.png", "vtc/CloseSelected.png",
	                                        this, menu_selector(GameStart::menuCloseCallback));
	pCloseItem->setPosition(ccp(origin.x + visibleSize.width - pCloseItem->getContentSize().width/2, origin.y + pCloseItem->getContentSize().height/2));

	CCMenu* pMenu = CCMenu::create(pCloseItem, NULL);
	pMenu->setPosition(CCPointZero);

	return pMenu;
}

CCScene* GameStart::scene() {
    CCScene *scene = CCScene::create();
    scene->addChild(GameStart::create());
    
    return scene;
}

bool GameStart::init() {
    if (!CCLayer::init()) {return false;}

	return true;
}

void GameStart::prepareGameMusic(const char* musicfilePath, float volume) {
	CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadBackgroundMusic(musicfilePath);
	CocosDenshion::SimpleAudioEngine::sharedEngine()->setEffectsVolume(volume);
}

void GameStart::menuCloseCallback(CCObject* pSender) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT) || (CC_TARGET_PLATFORM == CC_PLATFORM_WP8)
	CCMessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
#else
    CCDirector::sharedDirector()->end();
	#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
		exit(0);
	#endif
#endif
}

void GameStart::onEnter() {
	CCLayer::onEnter();
    
	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
	CCLOG("Game Status is: %d", this->gameStatus);
    
	CCAction* action = CCSequence::create(CCScaleBy::create(1, 3), CCFadeOut::create(2), NULL);
	CCSprite* pCocos2dxLogo = CCSprite::create("vtc/HelloWorld.png");
	pCocos2dxLogo->setPosition(ccp(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
	pCocos2dxLogo->runAction(action);
    
    CCAction* action2 = CCSequence::create(CCDelayTime::create(3), CCShow::create(), CCFadeIn::create(3), NULL);
    CCSprite* gameBanner = CCSprite::create("vtc/TITLE.png");
    gameBanner->setPosition(ccp(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    gameBanner->setVisible(false);
    gameBanner->runAction(action2);
    
    CCAction* action3 = CCRepeatForever::create(CCSequence::create(CCDelayTime::create(3), CCShow::create(), CCBlink::create(3, 5), NULL));
    CCLabelTTF* label = createGameStartLabel("Touch the screen to start the game", "Maker Felt", 12, visibleSize, origin);
    label->setVisible(false);
    label->runAction(action3);
    
    CCNode* bkg = CCNode::create();
    Background* bkg1 = Background::create("vtc/background_1.png", 3);
    Background* bkg2 = Background::create("vtc/background_2.png", 3.3);
    bkg->addChild(bkg1);
    bkg->addChild(bkg2);
    

	this->addChild(pCocos2dxLogo, 1);
    this->addChild(gameBanner, 1);
	this->addChild(createGameMenu(visibleSize, origin), 1);
	this->addChild(label, 1);
    addChild(bkg, 0);
    
    bkg1->scheduleUpdate();
    bkg2->scheduleUpdate();

    this->setTouchEnabled(true);

    CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic("vtc/MozartSymphonyMoltoAllegro.mp3", true);
}

void GameStart::ccTouchesBegan (CCSet *pTouches, CCEvent *pEvent) {
	startGame();
	CCDirector::sharedDirector()->replaceScene(HelloWorld::scene());

	CCLOG("Game Status is: %d", this->gameStatus);
    
	CCLayer::ccTouchesBegan(pTouches, pEvent);
}

void GameStart::ccTouchesEnded( CCSet* pTouches, CCEvent* pEvent) {
	CCLayer::ccTouchesEnded(pTouches, pEvent);
}

//void GameScene::update(float delta) {
//
//}
