//
//  SelectSaveItem.cpp
//  fiire
//
//  Created by 03 iphone on 13-4-28.
//
//
#include "cocos2d.h"
#include "SelectSaveItem.h"

using namespace cocos2d;

CCScene* SelectSaveItem::scene()
{
    CCScene *scene = CCScene::create();
    SelectSaveItem *layer = SelectSaveItem::create();
    scene->addChild(layer);
    return scene;
}

bool SelectSaveItem::init()
{
    if ( !CCLayer::init() )
    {
        return false;
    }
    
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    
    //    CCMenu *menu = CCMenu::create();
    //    addChild(menu);
    //    CCMenuItemFont *play = CCMenuItemFont::create("play");//,this,menu_selector(HelloWorld::menuCloseCallback));
    //    menu->addChild(play,2);
    
    CCSprite *back = CCSprite::create("selectSaveBackground.jpg");
    CCSize sizeb = back->getContentSize();
    
    CCLOG("%f %f",sizeb.width,sizeb.height);
    back->setPosition(ccp(size.width/2, size.height/2));
    back->setScale(0.5f);
    addChild(back,-1);
    
    CCMoveBy *moveBy = CCMoveBy::create(5.0f, ccp(20,0));
    CCSequence *seq = (CCSequence *)CCSequence::create(moveBy,moveBy->reverse());
    CCRepeatForever *forever = CCRepeatForever::create(seq);
    back->runAction(forever);
//    CCMenuItem
    return true;
}

