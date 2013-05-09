
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
        
    CCMenu *menu = CCMenu::create();
    addChild(menu);
//    CCMenuItemFont *play = CCMenuItemFont::create("play",this,menu_selector(fireLayer::menuCloseCallback));
//    menu->addChild(play,2);
    
    CCSprite *back = CCSprite::create("selectSaveBackground.jpg");
//    CCTintTo
    CCSize sizeb = back->getContentSize();
    
    CCLOG("%f %f",sizeb.width,sizeb.height);
    back->setPosition(ccp(size.width/2, size.height/2));
    back->setScale(0.5f);
    addChild(back,-1);
    
    CCMoveBy *moveBy = CCMoveBy::create(5.0f, ccp(20,0));
    CCSequence *seq = (CCSequence *)CCSequence::create(moveBy,moveBy->reverse());
    CCRepeatForever *forever = CCRepeatForever::create(seq);
    back->runAction(forever);
    
    addSelectColumn();

    return true;    
}

void SelectSave::addSelectColumn()
{
    CCLabelTTF *selectsave = CCLabelTTF::create("SELECT SAVE", "Thonburi", 32);
    CCSize  size = CCDirector::sharedDirector()->getWinSize();
    CCMenu *menu = CCMenu::create();
    
    CCMenuItemImage *image = CCMenuItemImage::create("selectsaveBackground.png", "selectsaveBackground.png");
    menu->addChild(image);
    addChild(menu);
    selectsave->setPosition(ccp(size.width/2, size.height/2));
    menu->setPosition(ccp(size.width/2, size.height/4));
    addChild(selectsave);
    
    
}

void SelectSave::menuCloseCallback(CCObject *pSender)
{
    CCDirector::sharedDirector()->replaceScene(fireLayer::scene());
}
