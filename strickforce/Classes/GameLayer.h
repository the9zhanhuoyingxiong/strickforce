//
//  HelloWorldScene.h
//  strickforce
//
//  Created by 03 iphone on 13-5-1.
//  Copyright __MyCompanyName__ 2013年. All rights reserved.
//
#ifndef __HELLO_WORLD_H__
#define __HELLO_WORLD_H__

// When you import this file, you import all the cocos2d classes
#include "cocos2d.h"
#include "Box2D.h"
#include "Amok_Jebat.h"
#include "fireLayer.h"
#include "GLES-Render.h"
#include "tags.h"



#define scaleBackground 0.5f


class PhysicsSprite : public cocos2d::CCSprite
{
public:
    PhysicsSprite();
    void setPhysicsBody(b2Body * body);
    virtual bool isDirty(void);
    virtual cocos2d::CCAffineTransform nodeToParentTransform(void);
private:
    b2Body* m_pBody;    // strong ref
};

class GameLayer : public cocos2d::CCLayer {
public:
    ~GameLayer();
    GameLayer();
    GameLayer(const char *tmxName,const char *plistName);
    
    static cocos2d::CCScene* scene(stageTag tag);
    static GameLayer * sharedGameLayer();
    
    void initPhysics();
    void addNewSpriteAtPosition(cocos2d::CCPoint p);

    virtual void draw();
    virtual void ccTouchesBegan(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);
    virtual void ccTouchesMoved(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);
    virtual void ccTouchesEnded(cocos2d::CCSet *touches, cocos2d::CCEvent* event);
    void menuCloseCallback(CCObject* pSender);
    void update(float dt);
    void addGroundEdge(const char *plistName);
    void initPlayer();
    
    
    Amok_Jebat *aplayer;
    
private:
    GLESDebugDraw *m_debugDraw;
    b2World * world;
    cocos2d::CCTexture2D* m_pSpriteTexture; 
    
    cocos2d::CCPoint  touchstartPoint;
    cocos2d::CCPoint  touchendPoint;
    
    cocos2d::CCPoint  topPoint;
    cocos2d::CCPoint  bottonPoint;
    

};

#endif // __HELLO_WORLD_H__
