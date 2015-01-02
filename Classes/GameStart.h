/*
 * GameScene.h
 *
 *  Created on: 21 Dec, 2014
 *      Author: Sunny Ho, Ip
 */

#ifndef GAMESTART_H_
#define GAMESTART_H_

#include "cocos2d.h"
#include "GameUtil.h"

USING_NS_CC;

class GameStart : public CCLayer {
private:
    int gameStatus;
    CCLabelTTF* createGameStartLabel(const char*, const char*, int, const CCSize, const CCPoint);
    CCMenu* createGameMenu(const CCSize, const CCPoint);
public:
    GameStart();
    ~GameStart();

	CREATE_FUNC(GameStart);

	static CCScene* scene();

    static void prepareGameMusic(const char*, float);

	void menuCloseCallback(CCObject*);

	virtual bool init();

	virtual void onEnter();

	virtual void ccTouchesBegan (CCSet *, CCEvent *);

	virtual void ccTouchesEnded( CCSet*, CCEvent*);
    
    void startGame() {
        gameStatus = GAME_STARTED;
    }
    
    void endGame() {
        gameStatus = GAME_OVER;
    }
    
    int getGameStatus() {
        return gameStatus;
    }

//	virtual void update(float delta);
};

#endif /* GAMESTART_H_ */
