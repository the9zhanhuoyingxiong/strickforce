//
//  SelectMode.cpp
//  fiire
//
//  Created by 03 iphone on 13-5-7.
//
//

#include "SelectMode.h"
#include "SelectSaveItem.h"
#include "fireLayer.h"
#include "GameLayer.h"
#include "Campaign.h"
using namespace cocos2d;

CCScene* SelectMode::scene()
{
    CCScene *scene = CCScene::create();
    SelectMode *layer = SelectMode::create();
    scene->addChild(layer);
    return scene;
}

bool SelectMode::init()
{
    if ( !SelectSave::init() )
    {
        return false;
    }

    CCMenuItemFont *campaign = CCMenuItemFont::create("CAMPAIGN",this,menu_selector(SelectMode::selectCampaign));
    CCMenuItemFont *CHALLENGES = CCMenuItemFont::create("CHALLENGES");
    CCMenuItemFont *CUSTOMGAME = CCMenuItemFont::create("CUSTOMGAME");
    CCMenuItemFont *SOLDIERS = CCMenuItemFont::create("SOLDIERS");
    CCMenuItemFont *OPTIONS = CCMenuItemFont::create("OPTIONS");
    CCMenuItemFont *MEDALS = CCMenuItemFont::create("MEDALS");
    
    CCMenuItemFont *selectSave = CCMenuItemFont::create("SELECT SAVE",this,menu_selector(SelectMode::selectSave));
    CCSize SSize  = selectSave->getContentSize();
//    selectSave->setPosition(ccp(SSize.width/2, SSize.height));
    
//    CCLOG("SSize %f %f",SSize.width,SSize.height);
    CCMenu *menutosave = CCMenu::create(selectSave,NULL);
    addChild(menutosave);
    
    menutosave->setPosition(ccp(SSize.width/2, SSize.height));
    
//    campaign->setFontSize(5);
//    CHALLENGES->setFontSize(15);
//    CUSTOMGAME->setFontSize(15);
//    SOLDIERS->setFontSize(15);
//    OPTIONS->setFontSize(15);
//    MEDALS->setFontSize(15);
    
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    CCMenu *menu = CCMenu::create(campaign,CHALLENGES,CUSTOMGAME,SOLDIERS,OPTIONS,MEDALS,NULL);
    menu->setScale(0.5f);
    menu->setPosition(ccp(-size.width/8, size.height/4));
    menu->alignItemsVertically();
    this->setSkewX(0.5f);
    addChild(menu);
    
    
    
//    CCLog("menu %f %f %f %f",menu->getPositionX(),menu->getPositionY(),campaign->getPositionX(),campaign->getPositionY());
    
    return true;

}

void SelectMode::selectMode()
{
//    CCMenuItemFont *K = CCMenuItemFont::create()
//    CCMenuItemFont *campaign = CCMenuItemFont::create("CAMPAIGN");
//    CCMenuItemFont *CHALLENGES = CCMenuItemFont::create("CHALLENGES");
//    CCMenuItemFont *CUSTOMGAME = CCMenuItemFont::create("CUSTOMGAME");
//    CCMenuItemFont *SOLDIERS = CCMenuItemFont::create("SOLDIERS");
//    CCMenuItemFont *OPTIONS = CCMenuItemFont::create("OPTIONS");
//    CCMenuItemFont *MEDALS = CCMenuItemFont::create("MEDALS");
//    
//    CCMenu *menu = CCMenu::create(campaign,CHALLENGES,CUSTOMGAME,SOLDIERS,OPTIONS,MEDALS,NULL);
//    addChild(menu);
    
}

void SelectMode::selectSave()
{
    CCDirector::sharedDirector()->replaceScene(SelectSaveItem::scene());
}

void SelectMode::menuCloseCallback(CCObject *pSender)
{
//    CCMenuItem *font = (CCMenuItem *)pSender;
//    CCMenuItemFont   
    
}
void SelectMode::selectCampaign(){
    CCDirector::sharedDirector()->replaceScene(Campaign::scene());
}
