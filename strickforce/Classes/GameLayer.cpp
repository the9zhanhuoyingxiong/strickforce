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
#include "Campaign.h"

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
//     new GameLayer("firstStage.tmx","firstStage.plist");
    
}

GameLayer::GameLayer(const char  *tmxName,const char *plistName)
{    
    setTouchEnabled( true );
    setAccelerometerEnabled( true );
    bGameLayer = this;
    CCTMXTiledMap *map = CCTMXTiledMap::create(tmxName);
    
    map->setScale(scaleBackground);
    CCSize mSize = map->getContentSize();
    addChild(map,-10,kTagBackground);
    map->setPosition(ccp(-mSize.width/3*scaleBackground,-mSize.height/3*scaleBackground));
    
    CKSneaky *stick = CKSneaky::create();

    addChild(stick,10,kTagHandler);
    setPosition(CCPointZero);
        
    initPhysics();
    initPlayer();    
    
    CCMenuItemFont *back = CCMenuItemFont::create("back",this,menu_selector(GameLayer::menuCloseCallback));    
    CCMenu *menu = CCMenu::create(back,NULL);
    CCSize sizeWin = CCDirector::sharedDirector()->getWinSize();
    CCSize sizeBack= menu->getContentSize();
    menu->setPosition(ccp(sizeWin.width-50  ,sizeWin.height-25));
    addChild(menu);
    
     addGroundEdge(plistName);
           
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
    addChild(aplayer);
    
    b2BodyDef playerBodyDef;
    playerBodyDef.type = b2_dynamicBody;
    playerBodyDef.position.Set(100.f/PTM_RATIO, 180.f/PTM_RATIO);
    
    b2Body* playerBody = world->CreateBody(&playerBodyDef);

    b2PolygonShape playerShape ;
    playerShape.SetAsBox(0.25f  ,0.5f);//pSize.height/12/PTM_RATIO);
    playerBody->SetFixedRotation(true);
    
    b2FixtureDef fixtureDef ;
    fixtureDef.shape = &playerShape;
    fixtureDef.density =2.0f;
    fixtureDef.friction=2.50f;
    
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

   
        
   }

void GameLayer::draw()
{
    // IMPORTANT:    // This is only for debug purposes    // It is recommend to disable it    //
    CCLayer::draw();

    ccGLEnableVertexAttribs( kCCVertexAttribFlag_Position );

    kmGLPushMatrix();

    world->DrawDebugData();

    kmGLPopMatrix();
   
}

void GameLayer::addGroundEdge(const char *plistName)
{
    CCDictionary * lineDic = CCDictionary::createWithContentsOfFile(plistName);//fivestage471
    lineDic->retain();
    CCTMXTiledMap *map = (CCTMXTiledMap *)getChildByTag(kTagBackground);
    CCPoint mPos = map->getPosition();
    
    for (int i = 0; i < lineDic->count(); i++)
    {
        CCDictionary *line = (CCDictionary *) lineDic->objectForKey(CCString::createWithFormat("%d",i)->getCString());
        if (line)
        {
            float x     = ((CCString *) line->objectForKey("x"))->floatValue();
            float y     = ((CCString *) line->objectForKey("y"))->floatValue();
            
            float width = ((CCString *) line->objectForKey("width")) ->floatValue();
            float height= ((CCString *) line->objectForKey("height"))->floatValue();
            
//            CCLOG("%f %f %f %f",x,y,width,height);
            
            CCPoint p = ccpMult(CCPoint(x, y), 0.5f) ;
            CCPoint odd = ccpMult(CCPoint(width,-height), 0.5f) ;
//            ccDrawLine(p, ccpAdd(p,ccp(100, 0)));

//            ccDrawLine(p, ccpAdd(p, odd));
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
    lineDic->release();
}

void GameLayer::addNewSpriteAtPosition(CCPoint p)
{
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(p.x/PTM_RATIO, p.y/PTM_RATIO);
    
    b2Body *body = world->CreateBody(&bodyDef);
    
    b2PolygonShape dynamicBox;
    dynamicBox.SetAsBox(.5f, 2.0f);
    
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &dynamicBox;
    fixtureDef.density = 10000.f;
    
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

void GameLayer::ccTouchesEnded(CCSet* touches, CCEvent* event)
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
                
    }
}

CCScene* GameLayer::scene(stageTag tag)
{
    CCScene *scene = CCScene::create();
    CCString *num = CCString::createWithFormat("%d",  (int)tag+1);
    CCLOG("%d",num);
    CCDictionary *stageDic = CCDictionary::createWithContentsOfFile("StageTmxPlist.plist");
    CCDictionary *stageNum = (CCDictionary *)stageDic->objectForKey(num->getCString());

    CCString *tmxName = (CCString *)stageNum->objectForKey("tmxName");
    CCString *plistName= (CCString *)stageNum->objectForKey("plistName");
    
    CCLayer* layer = new GameLayer(tmxName->getCString(),plistName->getCString());
    scene->addChild(layer);
    layer->release();

    
    return scene;
}

void GameLayer::ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent)
{
    
    CCSetIterator it = pTouches->begin();
    CCTouch* touch = (CCTouch*)(*it);
    
    touchstartPoint = touch->getLocation();
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

void GameLayer::menuCloseCallback(CCObject *pSender)
{
    CCDirector::sharedDirector()->replaceScene(Campaign::scene());
}

