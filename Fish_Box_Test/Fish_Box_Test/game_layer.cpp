//
//  game_layer.cpp
//  Fish_Box_Test
//
//  Created by xionglin on 12/3/12.
//
//

#include "game_layer.h"
using namespace cocos2d;
GameLayer::~GameLayer(){
    //    CC_SAFE_RELEASE_NULL(running_fishs);
    //    CC_SAFE_RELEASE_NULL(cache_fishs);
    //    CC_SAFE_RELEASE_NULL(bullet_array);
    //    CC_SAFE_RELEASE_NULL(torpedo_node);
    //    CC_SAFE_RELEASE_NULL(state_base);
    //    CC_SAFE_RELEASE_NULL(coin_cache);
    //    CC_SAFE_RELEASE_NULL(gold_layer);
};


CCScene* GameLayer::scene(){
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    GameLayer *layer = GameLayer::create();
    
    if (layer->Init()) {
        // add layer as a child to scene
        scene->addChild(layer);
        
        // return the scene
        return scene;
    }
    
    return NULL;
}

bool GameLayer::Init(){
    //#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
    //    if(!BaseLayer::Init()){
    //        return false;
    //    }
    //#else
    //    if(!BaseLayer::Init(false, true, false)){
    //        return false;
    //    }
    //#endif
    this->setTouchEnabled(true);
    srand(time(NULL));
    energy = 0;
    maxEnergy = 1000;
    
    //running_fishs = new FishNodeArray();
    
    this->CreateBackImageNames();
    this->loadTexture();
    while(fishSheet->getChildren()->count() < MAX_ENEMY){
        this->addFish();
    }
    this->schedule(schedule_selector(GameLayer::updateGame), 0.05f);
    return true;
}

void GameLayer::CreateBackImageNames(){
//    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
//	CCSprite* bg = CCSprite::spriteWithFile("bj01.jpg");
//	bg->setPosition(ccp(winSize.width * 0.5f, winSize.height * 0.5f));
//	this->addChild(bg);
    CCSprite* back_img_name = CCSprite::create("480x320-1.png");
    back_img_name->setContentSize(CCSizeMake(480, 320));
    back_img_name->setPosition(ccp(240, 160));
    this->addChild(back_img_name);
    
//    CCSprite* energyBox = CCSprite::spriteWithFile("ui_2p_004.png");
//	energyBox->setPosition(ccp(520,30));
//	this->addChild(energyBox);
//    
//	energyPointer = CCSprite::spriteWithFile("ui_2p_005.png");
//	energyPointer->setPosition(ccp(520,30));
//	this->addChild(energyPointer);
//    
//	CCSprite* bgExp = CCSprite::spriteWithFile("ui_box_01.png");
//	bgExp->setPosition(ccp(500, 700));
//	this->addChild(bgExp);
//    
//	CCSprite* bgNum = CCSprite::spriteWithFile("ui_box_02.png");
//	bgNum->setPosition(ccp(440,90));
//	this->addChild(bgNum);
    
	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("cannon.plist");
	cannonSheet = CCSpriteBatchNode::batchNodeWithFile("cannon.png");
	this->addChild(cannonSheet);
    
	score1 = UIRollNum::getOne();
    score1->setNumber(10000);
	score1->setPosition(ccp(100, 17));
	this->addChild(score1, 100);
//
	gun = CCSprite::spriteWithSpriteFrameName("actor_cannon1_71.png");
	gun->setPosition(ccp(240, 50));
	cannonSheet->addChild(gun);
	floor = gun->getPosition().y;
}

void GameLayer::loadTexture(){
    
    
	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("fish.plist");
	fishSheet = CCSpriteBatchNode::batchNodeWithFile("fish.png");
	this->addChild(fishSheet);
    
    
	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("fish2.plist");
    fish2Sheet = CCSpriteBatchNode::batchNodeWithFile("fish2.png");
    this->addChild(fish2Sheet);
    //
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("fish3.plist");
    netSheet = CCSpriteBatchNode::batchNodeWithFile("fish3.png");
    this->addChild(netSheet);
    
}

void GameLayer::addFish(){
    int type = rand() % 9 + 1;
	char charBuffer[256] = {0};
	CCArray* fish01 = CCArray::array();
	for(int i = 1; i < 10; i++){
		memset(charBuffer, 0, sizeof(charBuffer));
		sprintf(charBuffer, "fish0%d_0%d.png", type, i);
		CCSpriteFrame* spriteFrame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(charBuffer);
		fish01->addObject(spriteFrame);
	}
    
	fish01_act = CCRepeatForever::actionWithAction(CCAnimate::actionWithAnimation(
                                                                                  CCAnimation::animationWithSpriteFrames(fish01, 0.2f)));
	Fish* fish = Fish::spriteWithSpriteFrameName(CCString::stringWithFormat("fish0%d_0%d.png", type, 1)->getCString());
	fish->setScale(1.2f);
	fish->setTag(type);
	fish->setIsCatch(false);
	fish->runAction(fish01_act);
	fish->addPath();
	fishSheet->addChild(fish);
}

void GameLayer::updateGame(float dt){
    CCObject* sprite;
	CCObject* net;
	CCScaleTo* scale0 = CCScaleTo::actionWithDuration(0.3f, 1.1f);
	CCScaleTo* scale1 = CCScaleTo::actionWithDuration(0.3f, 0.9f);
    
	CCARRAY_FOREACH(fishSheet->getChildren(), sprite){
		Fish* fish = (Fish*)sprite;
		if(fish->getIsCatch()){
			continue;
		}
        
		CCARRAY_FOREACH(fish2Sheet->getChildren(), net){
			Net* netx = (Net*)net;
			if(CCRect::CCRectContainsPoint(fish->boundingBox(), netx->getPosition())){
				if(!fish->randomCatch(fish->getTag())){
					netx->setIsCatching(false);
					break;
				}else{
					netx->setIsCatching(false);
					fish->setIsCatch(true);
					CCArray* fish01 = CCArray::array();
					for(int i = 1; i < 3; i++){
						fish01->addObject(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(
                                                                                                          CCString::stringWithFormat("fish0%d_catch_0%d.png",fish->getTag(),i)->getCString()));
					}
					CCRepeat* fish01_catch_act = CCRepeat::actionWithAction(CCAnimate::actionWithAnimation(CCAnimation::animationWithSpriteFrames(fish01, 0.2f)), 2);
					CCFiniteTimeAction*  fishSequence = CCSequence::actions(fish01_catch_act, CCCallFuncO::actionWithTarget(this, callfuncO_selector(GameLayer::afterCatch), fish), NULL);
					fish->stopAllActions();
					fish->runAction(fishSequence);
                    
					CCSprite* gold = CCSprite::spriteWithFile("+5.png");
					gold->setPosition(fish->getPosition());
                    
					CCFiniteTimeAction*  goldSequence = CCSequence::actions(scale0, scale1, scale0, scale1, CCCallFuncO::actionWithTarget(this, callfuncO_selector(GameLayer::afterShow), gold), NULL);
					gold->runAction(goldSequence);
					this->addChild(gold);
				}
			}
		}
        
        
	}

    CCARRAY_FOREACH(fish2Sheet->getChildren(), net){
		Net* netx = (Net*)net;
		if(netx->getIsCatching()){
			continue;
		}
        
		fish2Sheet->removeChild(netx, false);
        
		Net* tapnet = Net::spriteWithSpriteFrameName("net01.png");
		tapnet->setPosition(netx->getPosition());
	    CCFiniteTimeAction*  netSequence = CCSequence::actions(scale0, scale1, scale0, scale1, CCCallFuncO::actionWithTarget(this, callfuncO_selector(GameLayer::afterShowNet), tapnet), NULL);
		tapnet->runAction(netSequence);
		netSheet->addChild(tapnet);
        
		score1->setNumber(score1->getNumber() + 5);
	}
    
    
	while(fishSheet->getChildren()->count() < MAX_ENEMY){
		this->addFish();
	}
    
}

void GameLayer::ccTouchesBegan(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent){
	CCSetIterator iter = pTouches->begin();
	for(; iter != pTouches->end(); iter++){
		CCTouch* pTouch = (CCTouch*)*iter;
		CCPoint pos = CCDirector::sharedDirector()->convertToGL(pTouch->locationInView());
		if(pos.y < floor)
			return;
        
		gun->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("actor_cannon1_72.png"));
        
		float angle = (pos.y - gun->getPosition().y)/(pos.x - gun->getPosition().x);
		angle = atanf(angle)/M_PI*180;
		if(angle < 0){
			gun->setRotation(-(90 + angle));
		}else if(angle > 0){
			gun->setRotation(90 - angle);
		}
	}
}

void GameLayer::ccTouchesEnded(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent){
	CCSetIterator iter = pTouches->begin();
	for(; iter != pTouches->end(); iter++){
		CCTouch* pTouch = (CCTouch*)*iter;
		CCPoint pos = CCDirector::sharedDirector()->convertToGL(pTouch->locationInView());
        
		if(pos.y < floor)
			return;
        
		gun->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("actor_cannon1_71.png"));
        
//		score1->setNumber(score1->getNumber() - rand() % 20 - 2);
        
		Net* labelBoard = Net::spriteWithSpriteFrameName("bullet01.png");
		labelBoard->setPosition(ccp(240, 50));
		labelBoard->setIsCatching(true);
		CCMoveTo* move = CCMoveTo::actionWithDuration(1.0f, pos);
		CCFiniteTimeAction*  netSequence = CCSequence::actions(move, CCCallFuncO::actionWithTarget(this, callfuncO_selector(GameLayer::showNet), labelBoard), NULL);
        
		labelBoard->setRotation(gun->getRotation());
		labelBoard->runAction(netSequence);
		fish2Sheet->addChild(labelBoard);
        
		//this->updateEnergry(rand() % 20);
	}
}

void GameLayer::showNet(cocos2d::CCObject *pSender) {
    Net* sp = (Net*) pSender;
    fish2Sheet->removeChild(sp, false);
    
    sp->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("net01.png"));
    
	CCScaleTo* scale0 = CCScaleTo::actionWithDuration(0.3f, 1.1f);
	CCScaleTo* scale1 = CCScaleTo::actionWithDuration(0.3f, 0.9f);
    CCFiniteTimeAction* netSequence = CCSequence::actions(scale0, scale1, scale0, scale1, CCCallFuncO::actionWithTarget(this, callfuncO_selector(GameLayer::afterShowNet), sp), NULL);
    
	sp->runAction(netSequence);
	netSheet->addChild(sp);
}


void GameLayer::afterShowNet(cocos2d::CCObject* pSender){
	Net* sp = (Net*)pSender;
	netSheet->removeChild(sp, false);
}


void GameLayer::afterShow(cocos2d::CCObject* pSender){
	Net* sp = (Net*)pSender;
	this->removeChild(sp, false);
}

void GameLayer::afterCatch(cocos2d::CCObject* pSender){
	Net* sp = (Net*)pSender;
	fishSheet->removeChild(sp, false);
}

void GameLayer::updateEnergry(int en){
	energy += en;
	if(energy > maxEnergy){
		energy = maxEnergy;
	}
	float rotation = 180.0f * energy / maxEnergy;
	energyPointer->setRotation(rotation);
}




