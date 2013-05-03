//
//  Person.h
//  横版格斗
//
//  Created by 03 iphone on 13-4-11.
//  Copyright (c) 2013年 __MyCompanyName__. All rights reserved.
//

#ifndef _____Person_h
#define _____Person_h


#include "cocos2d.h"
using namespace cocos2d;

typedef enum Directions
{
    
    faceToRight = 0,
    faceToLeft  = 1
    
}Directions;

class Person :public CCSprite
{    
public:
//    Person(void);
//    virtual ~Person(void);
    virtual bool init();
    static Person *create(const char *str) ;
    
    void stayInScreen();
    virtual void update(float dt);
    Directions getDirection();
    void setDirect(Directions direct);
    
    void runAtTheDic();
    void runOrbit();
    void changeDirecion();
    
private:
    Directions faceDirect;
    
    
    
};

#endif
