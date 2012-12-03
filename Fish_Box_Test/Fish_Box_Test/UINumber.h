//
//  UINumber.h
//  Fish_Box_Test
//
//  Created by xionglin on 12/3/12.
//
//

#ifndef __Fish_Box_Test__UINumber__
#define __Fish_Box_Test__UINumber__

#include <iostream>
#include "cocos2d.h"

#define NUM_HEIGHT 20
#define NUM_WIDTH  20

typedef enum{
	NumStyleNormal,
	NumStyleSameTime,
} NumStyle;

class UINumber : public cocos2d::CCSprite {
public:
	~UINumber();
	static UINumber* numberWithStyle(NumStyle style);
    
	bool init();
	bool initWithStyle(NumStyle style);
    
	void setNumber(int num);
	void onRollDown(float dt);
	void onRollUp(float dt);
	void setup();
    
	CC_SYNTHESIZE_RETAIN(cocos2d::CCTexture2D*, m_texture, M_Texture);
    
private:
	NumStyle m_style;
	int m_num;
	int m_nPosCur;
	int m_nPosEnd;
	int m_nMoveLen;
};
#endif /* defined(__Fish_Box_Test__UINumber__) */
