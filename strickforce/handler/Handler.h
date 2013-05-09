//
//  CKSneaky.h
//  Cocos2d_x_402_Plane
//
//  Created by Cike Adolf on 13-4-10.
//
//

#ifndef __Cocos2d_x_402_Plane__CKSneaky__
#define __Cocos2d_x_402_Plane__CKSneaky__

#include "SneakyJoystickSkinnedBase.h"
#include "SneakyButtonSkinnedBase.h"
using namespace cocos2d;

class CKSneaky : public cocos2d::CCLayer{
    
    SneakyJoystickSkinnedBase *joystickBase;
    SneakyJoystick *joystick;
    
    SneakyButtonSkinnedBase fireButtonBase,jumpButtonBase;
    SneakyButton *fire, *jump;
    
    float totalTime, nextFireTime;
    float totalTime1,nextFireTime1;
public:
    static cocos2d::CCScene * scene();
    bool init();
    void addJoystick();
    void addjumpFunction();
    void addAttackButton();
    CCPoint tilePosFromLocation(CCPoint location, CCTMXTiledMap *tileMap);
    void addButton(SneakyButtonSkinnedBase *buttonBase, SneakyButton *button, CCSprite * defaultSprite, CCSprite * pressSprite, CCSprite * activatedSprite, CCSprite * disabledSprite, CCPoint point);
    virtual void update(float dt);
    
    void handlerMoveVerticl();
    void handlerMoveUp();
    void handlerMoveDown();
    
    CREATE_FUNC(CKSneaky);


bool isUp;
};

#endif /* defined(__Cocos2d_x_402_Plane__CKSneaky__) */
