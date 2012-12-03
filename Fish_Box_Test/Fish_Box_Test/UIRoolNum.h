//
//  UIRoolNum.h
//  Fish_Box_Test
//
//  Created by xionglin on 12/3/12.
//
//

#ifndef __Fish_Box_Test__UIRoolNum__
#define __Fish_Box_Test__UIRoolNum__

#include <iostream>
#include "cocos2d.h"
#include "UINumber.h"

class UIRollNum : public cocos2d::CCSprite {
public:
	~UIRollNum();
	bool init();
    
	static UIRollNum* getOne();
    
	void rebuildEffect();
	void clearEffect();
	int getNumber();
	void setNumber(int num);
    
	CC_SYNTHESIZE_RETAIN(cocos2d::CCArray*, numArray, NumArray);
	CC_SYNTHESIZE(cocos2d::CCPoint, m_point, Point);
	CC_SYNTHESIZE(NumStyle, style, Style);
    
private:
	int m_nNumber;
	int m_maxCol;
	bool zeroFill;
    
};
#endif /* defined(__Fish_Box_Test__UIRoolNum__) */
