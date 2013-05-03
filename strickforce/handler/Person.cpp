//
//  Person.cpp
//  横版格斗
//
//  Created by 03 iphone on 13-4-11.
//  Copyright (c) 2013年 __MyCompanyName__. All rights reserved.
//

//
//  Enemies.cpp
//  蜘蛛
//
//  Created by 03 iphone on 13-4-2.
//  Copyright (c) 2013年 __MyCompanyName__. All rights reserved.
//

#include "Person.h"
#include "SimpleAudioEngine.h"
 
using namespace CocosDenshion;


#define NumberOfonePic 10

typedef enum PersonFlag
{
    
}PersonFlag;


bool Person::init()
{
    
    if ( !CCSprite::init() )
    {
        return false;
    }
    
    this->scheduleUpdate();
    faceDirect = faceToRight;
    return true;
    
}

void Person::runOrbit()
{
      
}

void Person::runAtTheDic()
{
}

Directions Person::getDirection()
{
    return faceDirect;
}

void Person::setDirect(Directions direct)
{
    faceDirect = direct;
}

void Person::update(float dt)
{
    this->stayInScreen();
}

void Person::stayInScreen()
{
//    CCSize wSize = CCDirector::sharedDirector()->getWinSize();
//    CCSize Psize = this->getContentSize();
//    CCPoint point= this->getPosition();
//    if (point.x <= Psize.width/9)
//    {
//        this->setPositionX(Psize.width/9);
//    }
//    else if (point.x >= wSize.width - Psize.width/9)
//    {
//        this->setPositionX(wSize.width - Psize.width/9);
//    }

}

void Person::changeDirecion()
{
    if (faceDirect == faceToLeft)
    {
        faceDirect = faceToRight;
    }
    else if (faceDirect == faceToRight)
    {
        faceDirect = faceToLeft;
    }
}


Person * Person::create(const char *str)
{
    return (Person *)create(str);
}





