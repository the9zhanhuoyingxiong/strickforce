//
//  HelloWorldScene.cpp
//  strickforce
//
//  Created by 03 iphone on 13-5-1.
//  Copyright __MyCompanyName__ 2013年. All rights reserved.
//
#include "GameLayer.h"
#include "SimpleAudioEngine.h"
#include "Handler.h"
#include "Amok_Jebat.h"
#include "fireLayer.h"

using namespace cocos2d;
using namespace CocosDenshion;

GameLayer * bGameLayer = NULL;

#define PTM_RATIO 32

enum {
    kTagParentNode = 1,
    kTagHandler,
    kTagBackground
};

PhysicsSprite::PhysicsSprite()
: m_pBody(NULL)
{

}

void PhysicsSprite::setPhysicsBody(b2Body * body)
{
    m_pBody = body;
}

// this method will only get called if the sprite is batched.
// return YES if the physics values (angles, position ) changed
// If you return NO, then nodeToParentTransform won't be called.
bool PhysicsSprite::isDirty(void)
{
    return true;
}

// returns the transform matrix according the Chipmunk Body values
CCAffineTransform PhysicsSprite::nodeToParentTransform(void)
{
    b2Vec2 pos  = m_pBody->GetPosition();

    float x = pos.x * PTM_RATIO;
    float y = pos.y * PTM_RATIO;

    if ( isIgnoreAnchorPointForPosition() ) {
        x += m_tAnchorPointInPoints.x;
        y += m_tAnchorPointInPoints.y;
    }

    // Make matrix
    float radians = m_pBody->GetAngle();
    float c = cosf(radians);
    float s = sinf(radians);
    
    if(! m_tAnchorPointInPoints.equals(CCPointZero) )//     ! CCPoint::CCPointEqualToPoint(m_tAnchorPointInPoints, CCPointZero) )
    {
        x += c*-m_tAnchorPointInPoints.x + -s*-m_tAnchorPointInPoints.y;
        y += s*-m_tAnchorPointInPoints.x + c*-m_tAnchorPointInPoints.y;
    }

    // Rot, Translate Matrix
    m_tTransform = CCAffineTransformMake( c,  s,
        -s,    c,
        x,    y );

    return m_tTransform;
}
GameLayer * GameLayer::sharedGameLayer()
{
    return bGameLayer;
}

GameLayer::GameLayer()
{
    setTouchEnabled( true );
    setAccelerometerEnabled( true );
    bGameLayer = this;
    CCTMXTiledMap *map = CCTMXTiledMap::create("fifth.tmx");
    CCSize mSize = map->getContentSize();
    this->addChild(map,-10,kTagBackground);
    map->setPosition(ccp(-mSize.width/3,-mSize.height/3));
    CCLOG("mSize  %f %f    ",-mSize.width/3,-mSize.height/3);
//    map->setVisible(false);
    
    CKSneaky *stick = CKSneaky::create();
    this->addChild(stick,10,kTagHandler);
    this->setPosition(CCPointZero);


    initPhysics();
    initPlayer();
    scheduleUpdate();
}




GameLayer::~GameLayer()
{
    delete world;
    world = NULL;
    
    delete m_debugDraw;
}

void GameLayer::initPlayer()
{
    aplayer = Amok_Jebat::create(Amok_stand);
    aplayer->retain();
    addChild(aplayer);    
    
    b2BodyDef playerBodyDef;
    playerBodyDef.type = b2_dynamicBody;
    playerBodyDef.position.Set(100.f/PTM_RATIO, 180.f/PTM_RATIO);
    

    b2Body* playerBody = world->CreateBody(&playerBodyDef);
    
    

    b2PolygonShape playerShape ;
    playerShape.SetAsBox(0.5f  ,0.4f);//pSize.height/12/PTM_RATIO);
    playerBody->SetFixedRotation(true);
    
    b2FixtureDef fixtureDef ;
    fixtureDef.shape = &playerShape;
    fixtureDef.density = 0.0f;
    
    playerBody->CreateFixture(&fixtureDef);
    
    
    playerBody->SetUserData(aplayer);
    aplayer->amokBody = playerBody;
    
}


void GameLayer::initPhysics()
{

    CCSize s = CCDirector::sharedDirector()->getWinSize();

    b2Vec2 gravity;
    gravity.Set(0.0f, -10.0f);
    world = new b2World(gravity);

    // Do we want to let bodies sleep?
    world->SetAllowSleeping(true);

    world->SetContinuousPhysics(true);

     m_debugDraw = new GLESDebugDraw( PTM_RATIO );
     world->SetDebugDraw(m_debugDraw);

    uint32 flags = 0;
    flags += b2Draw::e_shapeBit;
    
    //        flags += b2Draw::e_jointBit;
    //        flags += b2Draw::e_aabbBit;
    //        flags += b2Draw::e_pairBit;
    //        flags += b2Draw::e_centerOfMassBit;
    m_debugDraw->SetFlags(flags);
//    CCDelayTime

    addGroundEdge();
        
   }

void GameLayer::draw()
{
    // IMPORTANT:    // This is only for debug purposes    // It is recommend to disable it    //
//    CCLOG("draw");
    CCLayer::draw();

    ccGLEnableVertexAttribs( kCCVertexAttribFlag_Position );

    kmGLPushMatrix();

    world->DrawDebugData();

    kmGLPopMatrix();
    
   
}

void GameLayer::addGroundEdge()
{
    CCDictionary * lineDic = CCDictionary::createWithContentsOfFile("fivestage471.plist");
    lineDic->retain();
    CCTMXTiledMap *map = (CCTMXTiledMap *)getChildByTag(kTagBackground);
    CCPoint mPos = map->getPosition();
    CCLOG("%f %f",mPos.x,mPos.y);
    
    for (int i = 0; i < lineDic->count(); i++)
    {
        CCDictionary *line = (CCDictionary *) lineDic->objectForKey(CCString::createWithFormat("%d",i)->getCString());//9   14
        int x     = ((CCString *) line->objectForKey("x"))->intValue();
        int y     = ((CCString *) line->objectForKey("y"))->intValue();
        
        //CCString *string = CCString::create("-1");
        CCLOG("%s",((CCString *) line->objectForKey("height"))->getCString());
        
        float width = ((CCString *) line->objectForKey("width")) ->floatValue();
        float height= ((CCString *) line->objectForKey("height"))->floatValue();
//        CCLOG(" %d  %d %d %f %f ",i , x, y, width, height);
        
        CCPoint p = CCPoint(x, y);
        CCPoint odd = CCPoint(width,-height);   //(100,0);//
//        ccDrawLine(p, ccpAdd(p, odd));
        b2BodyDef groundBodyDef;
//        groundBodyDef.position.Set(0, 0);
        
        
        b2Body* groundBody = world->CreateBody(&groundBodyDef);
        b2EdgeShape groundBox;
        
        CCPoint FromLinePos = ccpAdd(p, mPos);
        CCPoint ToLinePos = ccpAdd(ccpAdd(p, odd), mPos);        
//        CCLOG("FromLinePos %f %f %f %f",FromLinePos.x,FromLinePos.y,ToLinePos.x,ToLinePos.y);
        
        groundBox.Set(b2Vec2(FromLinePos.x/PTM_RATIO,FromLinePos.y/PTM_RATIO), b2Vec2(ToLinePos.x/PTM_RATIO,ToLinePos.y/PTM_RATIO));
        groundBody->CreateFixture(&groundBox,1);
        
        
    }


}

void GameLayer::addNewSpriteAtPosition(CCPoint p)
{
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(p.x/PTM_RATIO, p.y/PTM_RATIO);
    
    b2Body *body = world->CreateBody(&bodyDef);
    
    b2PolygonShape dynamicBox;
    dynamicBox.SetAsBox(.5f, .5f);
    
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &dynamicBox;    
    fixtureDef.friction = 300.f;
    
    body->CreateFixture(&fixtureDef);
}


void GameLayer::update(float dt)
{
    int velocityIterations = 8;
    int positionIterations = 1;
    
    world->Step(dt, velocityIterations, positionIterations);
    
    for (b2Body* b = world->GetBodyList(); b; b = b->GetNext())
    {
        if (b->GetUserData() != NULL) {
            CCSprite* myActor = (CCSprite*)b->GetUserData();
            myActor->setPosition( CCPointMake( b->GetPosition().x * PTM_RATIO, b->GetPosition().y * PTM_RATIO) );
            myActor->setRotation( -1 * CC_RADIANS_TO_DEGREES(b->GetAngle()) );
        }    
    }
}

void GameLayer::ccTouchesEnded(CCSet*
                                touches, CCEvent* event)
{
    CCSetIterator it;
    CCTouch* touch;
    
    for( it = touches->begin(); it != touches->end(); it++) 
    {
        touch = (CCTouch*)(*it);
        
        if(!touch)
            break;
        
        CCPoint location = touch->getLocationInView();
        
        location = CCDirector::sharedDirector()->convertToGL(location);
                
//        addNewSpriteAtPosition(ccpSub(location, getPosition()));//ccpSub(location, getPosition())
    }
}

CCScene* GameLayer::scene()
{
    CCScene *scene = CCScene::create();
    
    CCLayer* layer = new GameLayer();
    scene->addChild(layer);
    layer->release();

    
    return scene;
}

void GameLayer::ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent)
{
    
    CCSetIterator it = pTouches->begin();
    CCTouch* touch = (CCTouch*)(*it);
    
    touchstartPoint = touch->getLocation();
//    //    CCLOG("touchstartPoint %f %f",touchstartPoint.x,touchstartPoint.y);
}



void GameLayer::ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent)
{
    CCSetIterator it = pTouches->begin();
    CCTouch* touch = (CCTouch*)(*it);

    
//    for (b2Body* b = world->GetBodyList(); b; b = b->GetNext())
    {
        
//        b2BodyDef *def ;
//        b->ApplyForceToCenter(b2Vec2(100,0));
//        b2Vec2 p = b->GetPosition();
        CCPoint pos = getPosition();
        CCPoint tou = touch->getLocation();
        CCPoint add = ccpSub(tou, touchstartPoint);
        CCPoint to  = ccpAdd(pos, add);
        
        setPosition(to);
        touchstartPoint = tou;
        
        CKSneaky *handler = (CKSneaky *)getChildByTag(kTagHandler);
        
        handler->setPosition(ccpSub(handler->getPosition(), add));       

        {
            
//            CCSprite* myActor = (CCSprite*)b->GetUserData();
//            myActor->setPosition( CCPointMake( b->GetPosition().x * PTM_RATIO, b->GetPosition().y * PTM_RATIO) );
//            myActor->setRotation( -1 * CC_RADIANS_TO_DEGREES(b->GetAngle()) );
        }
    }

    
}

