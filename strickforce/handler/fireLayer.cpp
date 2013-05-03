

#include "fireLayer.h"
#include "Handler.h"

//#import <Foundation/Foundation.h>

using namespace cocos2d;
typedef enum tag
{
 tag_background = 0
}tag;

fireLayer *firescene = NULL;

fireLayer::fireLayer()
{
    
}

fireLayer::~fireLayer()
{
    lineDic->release();
}


CCScene* fireLayer::scene()
{
    CCScene *scene = CCScene::create();
    fireLayer  *layer = fireLayer::create();
    scene->addChild(layer);    
    return scene;
}

fireLayer * fireLayer::shardfireLayer()
{
    return  firescene;
}

bool fireLayer::init()
{
    if ( !CCLayer::init() )
    {
       return false;
    }
    
    srandom(time(NULL));
    firescene = this;
    
    lineDic = CCDictionary::createWithContentsOfFile("fifthlinePoints.plist");
    lineDic->retain();
    int dicLineCount = lineDic->count();
    int randomLine   = (arc4random()) % dicLineCount;
    CCLOG("  %d",randomLine);
    
    
    
    CCArray *array = lineDic->allKeys();
    
    CCString *string = (CCString *)array->objectAtIndex(randomLine);
    CCDictionary *number = (CCDictionary *)lineDic -> objectForKey(string->getCString());
    
    
    int lineWidth = ((CCString *)number->objectForKey("width"))->intValue();
    int lineX     = ((CCString *)number->objectForKey("x"))->intValue();
    int lineY     = ((CCString *)number->objectForKey("y"))->intValue();
    
    
    int randomLinePosX =  arc4random() % lineWidth ;
    CCLOG("string %s lineWidth%d,pos+= %d",string->getCString(),lineWidth,randomLinePosX);
    
    
    
    player = Amok_Jebat::create(Amok_stand);
    player->setPosition(ccp(lineX, lineY+randomLinePosX));
    this->addChild(player,3,1);
    
    //    CCLOG("%s  array count = %d %f %f %f %f",string->getCString(),array->count(),lineWidth,lineY,lineX,lineX+randomLinePosX);
    
    
    CCTMXTiledMap *map = CCTMXTiledMap::create("fifth.tmx");
    this->addChild(map,-10,tag_background);
    map->setVisible(false);
    
    CKSneaky *stick = CKSneaky::create();
    this->addChild(stick,10);
    this->setPosition(CCPointZero);
    this->setTouchEnabled(true);
  
    return true;
}

void fireLayer::draw()
{
    CCTMXTiledMap *map = (CCTMXTiledMap *)this->getChildByTag(tag_background);
    CCTMXObjectGroup *objectGroup = map->objectGroupNamed("objectlayer");
    CCPoint  mapPos = map->getPosition();
    
    int numObjects = objectGroup->getObjects()->count();
    for (int i = 0; i < numObjects; i++)
    {
        CCDictionary *line = (CCDictionary *) lineDic->objectForKey(CCString::createWithFormat("%d",i)->getCString());//9   14
        float x     = ((CCString *) line->objectForKey("x"))->floatValue();
        float y     = ((CCString *) line->objectForKey("y"))->floatValue();
        float width = ((CCString *) line->objectForKey("width")) ->floatValue();
        float height= ((CCString *) line->objectForKey("height"))->floatValue();
        CCSize  sizeback = map->getContentSize();
        
        CCPoint p = CCPoint(x, y);
        CCPoint odd = CCPoint(width,-height);          
        CCPoint thisPosition = ccpAdd(p, mapPos);
        
//        draw(thisPosition, ccpAdd(thisPosition, odd));
        
        
        
    }
    
}


void fireLayer::draw(CCPoint origin, CCPoint dest)
{
    CCPoint thisPos = getPosition();    
    ccDrawLine( ccpAdd(thisPos, origin), ccpAdd(thisPos, dest));
    ccDrawColor4B(255, 255,0, 255);
//    glLineWidth(5.0f);
}

void fireLayer::ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent)
{
    
    CCSetIterator it = pTouches->begin();
    CCTouch* touch = (CCTouch*)(*it);
    
    touchstartPoint = touch->getLocation();
//    CCLOG("touchstartPoint %f %f",touchstartPoint.x,touchstartPoint.y);
}



void fireLayer::ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent)
{
    CCSetIterator it = pTouches->begin();
    CCTouch* touch = (CCTouch*)(*it);
    
    CCTMXTiledMap *menu =(CCTMXTiledMap *) getChildByTag(tag_background);
    
    CCPoint pos = menu->getPosition();
    CCPoint t = touch->getLocation();
    CCPoint add = ccpSub(t, touchstartPoint);
    menu->setPosition(ccpAdd(pos, add));
    
    CCPoint playLoc = player->getPosition();
    player->setPosition(ccpAdd(playLoc, add));
   // CCPoint tilepos = tilePosFromLocation(add, menu);
    
    
    menu->setPosition(ccpAdd(pos, add));
    CCPoint position = menu->getPosition();
//
    CCLOG("%f %f ",position.x, position.y);
    touchstartPoint = touch->getLocation();
}

CCPoint fireLayer::tilePosFromLocation(CCPoint location, CCTMXTiledMap *tileMap)
{
    CCPoint pos = ccpSub(location, tileMap->getPosition());
    
    float scaleWidth = tileMap->getTileSize().width;
    float scaleHeight= tileMap->getTileSize().height;///CC_CONTENT_SCALE_FACTOR();
    
    float posY = tileMap->getMapSize().height*tileMap->getTileSize().height-pos.y;
    
    pos = ccp((int)(pos.x/scaleWidth),(int)(posY/scaleHeight));
//    CCLOG("[%f %f]",pos.x,pos.y);
    return pos;

}


void fireLayer::menuCloseCallback(CCObject* pSender)
{
    CCDirector::sharedDirector()->replaceScene(fireLayer::scene());
}


