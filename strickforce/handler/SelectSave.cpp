
#include "SelectSave.h"
#include "cocos2d.h"
#include "fireLayer.h"
using namespace cocos2d;

CCScene* SelectSave::scene()
{
    CCScene *scene = CCScene::create();
    SelectSave *layer = SelectSave::create();
    scene->addChild(layer);
    return scene;
}

bool SelectSave::init()
{
    if ( !CCLayer::init() )
    {
        return false;
    }
    
    CCSize size = CCDirector::sharedDirector()->getWinSize();
        
        
    CCSprite *back = CCSprite::create("selectSaveBackground.jpg");
    CCSize sizeb = back->getContentSize();
    
    back->setPosition(ccp(size.width/2, size.height/2));
    back->setScale(0.5f);
    addChild(back,-1);
    
    CCMoveBy *moveBy = CCMoveBy::create(5.0f, ccp(20,0));
    CCSequence *seq = (CCSequence *)CCSequence::create(moveBy,moveBy->reverse());
    CCRepeatForever *forever = CCRepeatForever::create(seq);
    back->runAction(forever);

    return true;    
}



void SelectSave::menuCloseCallback(CCObject *pSender)
{
//    CCDirector::sharedDirector()->replaceScene(fireLayer::scene());
}
