//
//  fish.cpp
//  Fish_Box_Test
//
//  Created by xionglin on 12/3/12.
//
//

#include "fish.h"
using namespace cocos2d;

Fish* Fish::spriteWithSpriteFrame(cocos2d::CCSpriteFrame *pSpriteFrame){
	Fish *pobSprite = new Fish();
	if (pobSprite && pobSprite->initWithSpriteFrame(pSpriteFrame))
	{
		pobSprite->autorelease();
		return pobSprite;
	}
	CC_SAFE_DELETE(pobSprite);
	return NULL;
}

Fish* Fish::spriteWithSpriteFrameName(const char *pszSpriteFrameName){
	CCSpriteFrame *pFrame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(pszSpriteFrameName);
    
	char msg[256] = {0};
	sprintf(msg, "Invalid spriteFrameName: %s", pszSpriteFrameName);
	CCAssert(pFrame != NULL, msg);
	return spriteWithSpriteFrame(pFrame);
}

bool Fish::randomCatch(int level){
	if(rand() % 10 >= level){
		isCatch = true;
	}else{
		isCatch = false;
	}
	return isCatch;
}

void Fish::addPath(){
	switch(rand() % 7){
		case 0:
			this->moveWithParabola(this, ccp(1200, 200), ccp(-500, 800), 0.0f, 20.0f, rand()%10+15);
			break;
		case 1:
			this->moveWithParabola(this, ccp(-200, 300), ccp(1300, 400), 180, 170, rand()%10+18);
			break;
		case 2:
			this->moveWithParabola(this, ccp(-200, 300), ccp(1000, -200), 190, 200, rand()%10+18);
			break;
		case 3:
			this->moveWithParabola(this, ccp(1300, 400), ccp(-200, 300), 10, 5, rand()%10+18);
			break;
		case 4:
			this->moveWithParabola(this, ccp(400, -1200), ccp(600, 1000), 90, 93, rand()%10+18);
			break;
		case 5:
			this->moveWithParabola(this, ccp(600, 1000), ccp(400, -200), -70, -80, rand()%10+18);
			break;
		case 6:
			this->moveWithParabola(this, ccp(1200, 2100), ccp(-200, 300), 30, -30, rand()%10+18);
			break;
	}
}

void Fish::moveWithParabola(cocos2d::CCSprite* mSprite, cocos2d::CCPoint startP, cocos2d::CCPoint endP, float startAngle, float endAngle, float time){
	float sx = startP.x;
	float sy = startP.y;
	float ex =endP.x+rand()%50;
	float ey =endP.y+rand()%150;
    
	float h = mSprite->getContentSize().height * 0.5f;
	CCPoint pos = CCPointMake(sx - 200 + rand()%400, sy -200 + rand() %400);
	mSprite->setPosition(pos);
	mSprite->setRotation(startAngle);
    
	ccBezierConfig bezier;
	bezier.controlPoint_1 = ccp(sx, sy);
	bezier.controlPoint_2 = ccp(sx+(ex-sx)*0.5, sy+(ey-sy)*0.5+rand()%300);
	bezier.endPosition = ccp(endP.x-30, endP.y+h);
	CCBezierTo* actionMove = CCBezierTo::actionWithDuration(time, bezier);
	CCRotateTo* actionRotate = CCRotateTo::actionWithDuration(time, endAngle);
	CCFiniteTimeAction* action = CCSpawn::actions(actionMove, actionRotate, NULL);
	CCFiniteTimeAction* sq = CCSequence::actions(action,CCCallFunc::actionWithTarget(this, callfunc_selector(Fish::removeSelf)), NULL);
	mSprite->runAction(sq);
}

void Fish::removeSelf(){
	this->removeFromParentAndCleanup(true);
}