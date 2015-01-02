#include <vector>
#include <string>
#include "AppDelegate.h"
#include "AppMacros.h"
#include "GameStart.h"
#include "SimpleAudioEngine.h"
#include "GameUtil.h"

USING_NS_CC;
using namespace std;

AppDelegate::AppDelegate() {}

AppDelegate::~AppDelegate() {}

vector<string> AppDelegate::buildSearchPath(const CCSize& frameSize, CCDirector* pDirector) {
	vector<string> searchPath;

	// Select resource according to the frame's height.
	// If the resource size is different from design resolution size, you need to set contentScaleFactor.
	// We use the ratio of resource's height to the height of design resolution,
	// this can make sure that the resource's height could fit for the height of design resolution.

	// if the frame's height is larger than the height of medium resource size, select large resource.
	if (frameSize.height > mediumResource.size.height) {
		searchPath.push_back(largeResource.directory);
		pDirector->setContentScaleFactor(MIN(largeResource.size.height/designResolutionSize.height, largeResource.size.width/designResolutionSize.width));
	} else if (frameSize.height > smallResource.size.height) { // if the frame's height is larger than the height of small resource size, select medium resource.
		searchPath.push_back(mediumResource.directory);
		pDirector->setContentScaleFactor(MIN(mediumResource.size.height/designResolutionSize.height, mediumResource.size.width/designResolutionSize.width));
	} else { // if the frame's height is smaller than the height of medium resource size, select small resource.
		searchPath.push_back(smallResource.directory);

		pDirector->setContentScaleFactor(MIN(smallResource.size.height/designResolutionSize.height, smallResource.size.width/designResolutionSize.width));
	}

	return searchPath;
}

bool AppDelegate::applicationDidFinishLaunching() {
    srand(GameUtil::getTickCount());
    
    // initialize director
    CCDirector* pDirector = CCDirector::sharedDirector();
    CCEGLView* pEGLView = CCEGLView::sharedOpenGLView();

    pDirector->setOpenGLView(pEGLView);

    GameStart::prepareGameMusic("vtc/MozartSymphonyMoltoAllegro.mp3", 0.8);

    // Set the design resolution
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT) || (CC_TARGET_PLATFORM == CC_PLATFORM_WP8)
    pEGLView->setDesignResolutionSize(designResolutionSize.width, designResolutionSize.height, kResolutionShowAll);
#else
    pEGLView->setDesignResolutionSize(designResolutionSize.width, designResolutionSize.height, kResolutionNoBorder);
#endif

    vector<string> searchPath = buildSearchPath(pEGLView->getFrameSize(), pDirector);

    CCFileUtils::sharedFileUtils()->setSearchPaths(searchPath); // set searching path
    pDirector->setDisplayStats(true);							// turn on display FPS
    pDirector->setAnimationInterval(1.0 / 60);				    // set FPS. the default value is 1.0/60 if you don't call this
    pDirector->runWithScene(GameStart::scene());

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    CCDirector::sharedDirector()->stopAnimation();
    CocosDenshion::SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    CCDirector::sharedDirector()->startAnimation();
    CocosDenshion::SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
}
