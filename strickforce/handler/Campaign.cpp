//
//  Campaign.cpp
//  strickforce
//
//  Created by 03 iphone on 13-5-8.
//
//

#include "Campaign.h"
#include "SelectMode.h"
#include "GameLayer.h"
#include "SelectStage.h"

using namespace cocos2d;

CCScene* Campaign::scene()
{
    CCScene *scene = CCScene::create();
    Campaign *layer = Campaign::create();
    scene->addChild(layer);
    return scene;
}

bool Campaign::init()
{
    if ( !SelectSave::init() )
    {
        return false;
    }
    stageNum = stageTag0;
    
    SelectStage *stages = SelectStage::create();
    addChild(stages);
    stages->setTag(campTag_SelectStage);

    
    CCMenuItemFont *start    = CCMenuItemFont::create("START",this,menu_selector(Campaign::menuCloseCallback));
    CCMenuItemFont *soldiers = CCMenuItemFont::create("SOLDIERS",this,menu_selector(Campaign::menuCloseCallback));
    CCMenuItemFont *mainMenu = CCMenuItemFont::create("mainMenu",this,menu_selector(Campaign::menuCloseCallback));
    
    start->setTag(campTag_start);
    soldiers->setTag(campTag_soldiers);
    mainMenu->setTag(campTag_mainMenu);
    
    CCMenu *menu = CCMenu::create(start,soldiers,mainMenu,NULL);
    addChild(menu,10);
    menu->setPosition(CCPointZero);
    menu->alignItemsVertically();
    
    CCSize size = menu->getContentSize();
    CCLOG("%f %f",size.width,size.height);
    menu->setPosition(ccp(size.width/6, size.height/6));
//    menu->setScale(0.5f);
    
    return true;
}



void Campaign::menuCloseCallback(CCObject *pSender)
{
    CCMenuItemFont *font = (CCMenuItemFont*)pSender;
    int tag = font->getTag();
    stageNum = tag;
    CCLOG("%d",tag);
    
    switch (tag) {
        case campTag_start:
        {
            SelectStage *stage = (SelectStage *)getChildByTag(campTag_SelectStage);
            CCDirector::sharedDirector()->replaceScene(GameLayer::scene((stageTag)stage->tag));
            break;
        }
        case campTag_soldiers:
            break;
        case campTag_mainMenu:
            CCDirector::sharedDirector()->replaceScene(SelectMode::scene());
            break;
        default:
            
            break;
    }
}

void Campaign::gotoStage(int stageNum)
{
    
}

