//
//  game_layer.h
//  Fish_Box_Test
//
//  Created by xionglin on 12/3/12.
//
//

#ifndef __Fish_Box_Test__game_layer__
#define __Fish_Box_Test__game_layer__

#include <iostream>
#include "cocos2d.h"
#include "fish.h"
#include "net.h"
#include "UIRoolNum.h"

#define WINHEIGHT 768
#define WINWIDHT 1024
#define MAX_ENEMY 15
#define MOVESPEED 5

#define KProgressTag 100

class GameLayer: public cocos2d::CCLayer {
public:
    virtual ~GameLayer();
    static cocos2d::CCScene* scene();
    CREATE_FUNC(GameLayer);
    
    //add background image
    void CreateBackImageNames();
    void ccTouchesBegan(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);
    void ccTouchesEnded(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);
    
	void loadTexture();
    void addFish();
    void updateGame(float dt);
    
    
private:
    bool Init();
    cocos2d::CCSpriteBatchNode* netSheet;
	cocos2d::CCSpriteBatchNode* fishSheet;
	cocos2d::CCSpriteBatchNode* fish2Sheet;
	cocos2d::CCSpriteBatchNode* cannonSheet;
    cocos2d::CCAction* fish01_act;
    
    int energy;
	int maxEnergy;
    void updateEnergry(int en);
    
    cocos2d::CCSprite* gun;
    cocos2d::CCSprite* energyPointer;
    float floor;
    
    UIRollNum *score1;
    
    void showNet(cocos2d::CCObject* pSender);
    void afterShowNet(cocos2d::CCObject* pSender);
    void afterCatch(cocos2d::CCObject* pSender);
	void afterShow(cocos2d::CCObject* pSender);
};

#endif /* defined(__Fish_Box_Test__game_layer__) */
