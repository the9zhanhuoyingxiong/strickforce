//
//  CKSneaky.cpp
//  Cocos2d_x_402_Plane
//
//  Created by Cike Adolf on 13-4-10.
//
//

#include "Handler.h"
using namespace cocos2d;
#include "Amok_Jebat.h"
#include "fireLayer.h"
#include "GameLayer.h"




CCScene* CKSneaky::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    CKSneaky *layer = CKSneaky::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

bool CKSneaky::init(){
    if (!CCLayer::init()) {
        return false;
    }

    
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("HudLayerSpriteFrame.plist", "HudLayerSpriteFrame.png");
    this->addJoystick();
    this->addAttackButton();
    this->addjumpFunction();
    this->scheduleUpdate();
    return true;
}

void CKSneaky::addAttackButton() //fireButtonBase,jumpButtonBase
{
    CCSpriteFrameCache *frameCache = CCSpriteFrameCache::sharedSpriteFrameCache();
    frameCache->addSpriteFramesWithFile("HudLayerSpriteFrame.plist");
    
    float buttonRadius= 50;
    SneakyButtonSkinnedBase * attackButtonBase = new SneakyButtonSkinnedBase();
    
    CCSize screenSize = CCDirector::sharedDirector()->getWinSize();
    
    fire = new SneakyButton();
    fire->setIsHoldable(true);
    fire->autorelease();
    attackButtonBase->setPosition(CCPointMake(screenSize.width - buttonRadius * 2.0f, buttonRadius * 0.5f));
    
    attackButtonBase->setDefaultSprite(CCSprite::createWithSpriteFrameName("ButtonAttack_1Glow.png"));
    attackButtonBase->setPressSprite(CCSprite::createWithSpriteFrameName("ButtonAttack_1Glow.png"));
    attackButtonBase->setDisabledSprite(CCSprite::createWithSpriteFrameName("ButtonAttack_1Glow.png"));
    attackButtonBase->setButton(fire);
    addChild(attackButtonBase,3);

}

void CKSneaky::addjumpFunction()
{
    SneakyButtonSkinnedBase * skinFireButton = new SneakyButtonSkinnedBase();
    
    float buttonRadius= 50;
    CCSpriteFrameCache *frameCache = CCSpriteFrameCache::sharedSpriteFrameCache();
    frameCache->addSpriteFramesWithFile("HudLayerSpriteFrame.plist");
    
    CCSize screenSize = CCDirector::sharedDirector()->getWinSize();
    jump = new SneakyButton();
    jump->autorelease();
    jump->setIsHoldable(true);
    
    skinFireButton->setPosition(CCPointMake(screenSize.width - buttonRadius * 0.5f, buttonRadius * 0.5f));
    skinFireButton->setDefaultSprite(CCSprite::createWithSpriteFrameName("ButtonJump_1Glow.png"));
    skinFireButton->setPressSprite(CCSprite::createWithSpriteFrameName("ButtonJump_1Glow.png"));
    skinFireButton->setDisabledSprite(CCSprite::createWithSpriteFrameName("ButtonJump_1Glow.png"));
    skinFireButton->setButton(jump);
    addChild(skinFireButton,3);

}

void CKSneaky::addJoystick(){
    
    joystick = new SneakyJoystick();
    joystick->initWithRect(CCRect(0, 0, 10, 10));
    joystick->setAutoCenter(true);
    joystick->setIsDPad(true);
    joystick->setNumberOfDirections(4);
    joystick->setDeadRadius(10);
    joystick->setThumbRadius(10);
    joystick->setJoystickRadius(10);
    //                                                    joystick->setTouchRadius();
    
    
    joystickBase = new SneakyJoystickSkinnedBase();
    joystickBase->init();
    joystickBase->autorelease();
    joystickBase->setBackgroundSprite(CCSprite::createWithSpriteFrameName("ButtonDpad_Bg.png"));
    joystickBase->setThumbSprite(CCSprite::createWithSpriteFrameName("ButtonDpad_1.png"));
    joystickBase->setJoystick(joystick);
    joystickBase->setPosition(ccp(joystickBase->boundingBox().size.width - 30, joystickBase->boundingBox().size.height - 30));
    
    this->addChild(joystickBase);
}

void CKSneaky::addButton(SneakyButtonSkinnedBase *buttonBase,
                         SneakyButton *button, CCSprite * defaultSprite, CCSprite * pressSprite, CCSprite * activatedSprite, CCSprite * disabledSprite, CCPoint point){
    
    buttonBase = new SneakyButtonSkinnedBase();
    buttonBase->init();
    buttonBase->autorelease();
    
    button->initWithRect(CCRect(0, 0, 0, 0));
    button->setIsHoldable(true);
    button->setVisible(true);
//    button->setRadius(20);
    
    buttonBase->setButton(button);
    buttonBase->setPosition(point);
    
    buttonBase->setDefaultSprite(defaultSprite);
    buttonBase->setDisabledSprite(disabledSprite);
    buttonBase->setPressSprite(pressSprite);
    buttonBase->setActivatedSprite(activatedSprite);
    
    this->addChild(buttonBase);
}
int x = 1, y = 1;
void CKSneaky::update(float dt)
{
    CCPoint velocity = ccpMult(joystick->getVelocity(), 2);
    Amok_Jebat *player = GameLayer::sharedGameLayer()->aplayer;
//    player->release();
    int xs = velocity.x;
    int ys = velocity.y;
    if(xs != 0 )//&& velocity.y != 0)
    {
        
        
//        b2Body *body = player->amokBody;
//        body->ApplyForceToCenter(b2Vec2(xs*10,ys*10));
//        player->cocos2d::CCNode::setPosition(player->getPositionX() + velocity.x, player->getPositionY());
//        player->dorunning();
//        
        if( xs < 0 )
        {
            player->amokBody->ApplyForceToCenter(b2Vec2(-10,0));
            player->turnLeft();
        }
        if (xs > 0 )
        {
            player->amokBody->ApplyForceToCenter(b2Vec2(10,0));
            player->turnRight();            
        }
    }
    else if (xs == 0 && ys == 0)
    {
        player->doStanding();
    }
    else if (ys > 0)
    {
        player->doJump();
    }
//
//        
//    totalTime += dt;
//    
//    
//    
//    if (jump->getIsActive()&& totalTime > nextFireTime ) {
//        nextFireTime += 0.5;
//        player->stopAllActions();
//        if (player->getFlag() != Amok_run)
//        {
//            CCRepeat *rep =  player->createAnim(Amok_jump);
//            CCRepeat *re  = player->createAnim(Amok_stand);
//            CCSequence *seq = (CCSequence *)CCSequence::create(rep,re,NULL);
//            
//            player->runAction(seq);
//        }
//        
//    }
//    
//    if (fire->getIsActive()&& totalTime > nextFireTime ) {
//        nextFireTime += 0.5;
//        player->stopAllActions();
//        if (player->getFlag() != Amok_run)
//        {
//            CCRepeat *rep =  player->createAnim(Amok_attack1);
//            CCRepeat *re  = player->createAnim(Amok_stand);
//            CCSequence *seq = (CCSequence *)CCSequence::create(rep,re,NULL);            
//            player->runAction(seq);
//        }
//        
//    }
//    //
//    if (!fire->getIsActive()) {
//        nextFireTime = 0;
//        totalTime = 0;
//        //  CCLOG("!getIsActive");
//        
//    }
//
//    
////
//    if (!jump->getIsActive()) {
//        nextFireTime = 0;
//        totalTime = 0;
//      //  CCLOG("!getIsActive");        
//    }
}

CCPoint CKSneaky::tilePosFromLocation(CCPoint location, CCTMXTiledMap *tileMap)
{
    CCPoint pos = ccpSub(location, tileMap->getPosition());
    
    float scaleWidth = tileMap->getTileSize().width/CC_CONTENT_SCALE_FACTOR();
    float scaleHeight= tileMap->getTileSize().height/CC_CONTENT_SCALE_FACTOR();
    
    float posY = tileMap->getMapSize().height*tileMap->getTileSize().height-pos.y;
    
    pos = ccp((int)(pos.x/scaleWidth),(int)(posY/scaleHeight));
    CCLOG("[%f %f]",pos.x,pos.y);
    return pos;
}

void CKSneaky::handlerMoveVerticl()
{
    
}
void CKSneaky::handlerMoveUp()
{
    
}
void CKSneaky::handlerMoveDown()
{
    
}


