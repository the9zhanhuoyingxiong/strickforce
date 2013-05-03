//
//  fireLayer.h
//  HelloWorld
//
//  Created by 03 iphone on 13-4-28.
//
//

#ifndef __HelloWorld__fireLayer__
#define __HelloWorld__fireLayer__

#include "cocos2d.h"
#include "Amok_Jebat.h"
#include "Box2D.h"

class fireLayer : public cocos2d::CCLayer
{
public:
    fireLayer(void);
    virtual ~fireLayer(void);

    virtual bool init();
    
    static cocos2d::CCScene* scene();
    static fireLayer *shardfireLayer(void);

    void draw(cocos2d::CCPoint origin,cocos2d::CCPoint destination);

    virtual void draw(void);
    virtual void ccTouchesBegan(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);
    virtual void ccTouchesMoved(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);
    cocos2d::CCPoint tilePosFromLocation(cocos2d::CCPoint location, cocos2d::CCTMXTiledMap *tileMap);
    void menuCloseCallback(CCObject* pSender);
    CREATE_FUNC(fireLayer);
    
    Amok_Jebat *player;
    cocos2d::CCPoint  touchstartPoint;
    cocos2d::CCPoint  touchendPoint;
    
    cocos2d::CCPoint  topPoint;
    cocos2d::CCPoint  bottonPoint;
    cocos2d::CCDictionary *lineDic;

};


#endif /* defined(__HelloWorld__fireLayer__) */
