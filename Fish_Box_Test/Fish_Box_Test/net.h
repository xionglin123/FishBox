//
//  net.h
//  Fish_Box_Test
//
//  Created by xionglin on 12/3/12.
//
//

#ifndef Fish_Box_Test_net_h
#define Fish_Box_Test_net_h

#include "cocos2d.h"

class Net : public cocos2d::CCSprite {
public:
	static Net* spriteWithSpriteFrame(cocos2d::CCSpriteFrame *pSpriteFrame){
		Net *pobSprite = new Net();
		if (pobSprite && pobSprite->initWithSpriteFrame(pSpriteFrame))
		{
			pobSprite->autorelease();
			return pobSprite;
		}
		CC_SAFE_DELETE(pobSprite);
		return NULL;
	}
    
	static Net* spriteWithSpriteFrameName(const char *pszSpriteFrameName){
		cocos2d::CCSpriteFrame *pFrame = cocos2d::CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(pszSpriteFrameName);
        
		char msg[256] = {0};
		sprintf(msg, "Invalid spriteFrameName: %s", pszSpriteFrameName);
		CCAssert(pFrame != NULL, msg);
		return spriteWithSpriteFrame(pFrame);
	}
    
	CC_SYNTHESIZE(bool, isCatching, IsCatching);
};

#endif
