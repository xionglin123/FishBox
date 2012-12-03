//
//  fish.h
//  Fish_Box_Test
//
//  Created by xionglin on 12/3/12.
//
//

#ifndef __Fish_Box_Test__fish__
#define __Fish_Box_Test__fish__

#include "cocos2d.h"

typedef enum
{
	FishNoraml = 0,
	FishGold,
	FishShark
} FishType;

class Fish : public cocos2d::CCSprite {
public:
    
	static Fish* spriteWithSpriteFrame(cocos2d::CCSpriteFrame *pSpriteFrame);
	static Fish* spriteWithSpriteFrameName(const char *pszSpriteFrameName);
    
	bool randomCatch(int level);
	void addPath();
	void moveWithParabola(cocos2d::CCSprite* mSprite, cocos2d::CCPoint startP, cocos2d::CCPoint endP,
                          float startAngle, float endAngle, float time);
    
    
	CC_SYNTHESIZE(bool, isCatch, IsCatch);
    
private:
	FishType type;
	cocos2d::CCAction* path;
    
	void removeSelf();
    
};

#endif /* defined(__Fish_Box_Test__fish__) */
