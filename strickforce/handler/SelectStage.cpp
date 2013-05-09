//
//  SelectStage.cpp
//  strickforce
//
//  Created by 03 iphone on 13-5-8.
//
//

#include "SelectStage.h"
#include "SelectMode.h"
using namespace cocos2d;

CCScene* SelectStage::scene()
{
    CCScene *scene = CCScene::create();
    SelectStage *layer = SelectStage::create();
    scene->addChild(layer);
    return scene;
}

bool SelectStage::init()
{
    if ( !CCLayer::init() )
    {
        return false;
    }
    
    CCDictionary *stageInfo = CCDictionary::createWithContentsOfFile("stageInfo.plist");
    CCMenu *menu = CCMenu::create();
    int tag = stageTag0;
    for (int i = 0 ; i < stageInfo->count(); i++,tag++) {
        CCString *s = CCString::createWithFormat("%d",i+1);
        CCDictionary *dic =(CCDictionary *) stageInfo->objectForKey(s->getCString());
        CCString *stageName = (CCString *)dic->objectForKey("name");
        CCString *stageInfo = CCString::createWithFormat("%d    %s",i+1,stageName->getCString());
        CCMenuItemFont *font = CCMenuItemFont::create(stageInfo->getCString(),this,menu_selector(SelectStage::menuCloseCallback));
        menu->addChild(font);
        font->setTag(tag);
    }
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    
    CCMenuItemFont *back = CCMenuItemFont::create("back",this,menu_selector(SelectStage::menuCloseCallback));
    menu->addChild(back);
    back->setTag(tag_back);
    
    addChild(menu);
    menu->alignItemsVertically();
    menu->setScale(0.4f);
    menu->setPosition(ccp(200,50));
    
    CCDictionary *dic = (CCDictionary *) stageInfo->objectForKey("1");
    CCString *mod    = (CCString *)dic->objectForKey("MODE");
    CCString *goal    = (CCString *)dic->objectForKey("Goal");
    CCString *num    = (CCString *)dic->objectForKey("num");
    CCString *missdes = (CCString *)dic->objectForKey("MISSIONDESCRIPTION");
    CCString *picture  = (CCString *)dic->objectForKey("smallPic");
    
    float fondSize = 15;
    
    CCSprite *firstCard = CCSprite::create(picture->getCString());
    CCLabelTTF* MODE = CCLabelTTF::create("MODE", "Thonburi", fondSize);
    CCSize sizeMode = MODE->getContentSize();
    firstCard->setTag(tag_smallBack);
    MODE->setPosition(ccp(sizeMode.width, size.height/2));    
    this->addChild(MODE,2);
    
    float oddleft = sizeMode.width/2;
    float oddDown = sizeMode.height;
    
    
    
    CCLabelTTF* match = CCLabelTTF::create(mod->getCString(), "Thonburi", fondSize);
    CCSize sizeMatch = match->getContentSize();
    match->setPosition(ccp(size.width/2-sizeMatch.width/2, size.height/2));
    match->setTag(tag_match);
    this->addChild(match,2);
    
    CCLabelTTF * goalLabel = CCLabelTTF::create(goal->getCString(), "Thonburi", fondSize);
    CCLabelTTF * numLabel = CCLabelTTF::create(num->getCString(), "Thonburi", fondSize) ;
    CCSize gLabelSize = goalLabel->getContentSize();
    CCSize nLabelSize = numLabel->getContentSize();
    
    goalLabel->setPosition(ccp(gLabelSize.width/2+oddleft, size.height/2-sizeMode.height));
    numLabel->setPosition(ccp(size.width/2-nLabelSize.width/2, size.height/2-sizeMode.height));
    
    addChild(goalLabel);
    addChild(numLabel);
    
    
    CCLabelTTF* missionDes = CCLabelTTF::create("MISSION DESCRIPTION", "Thonburi", fondSize);
    CCSize sizeMDes = missionDes->getContentSize();
    missionDes->setPosition(ccp(sizeMDes.width/2+oddleft, size.height/2-oddDown*2));
    this->addChild(missionDes,2);
    
    CCLabelTTF* missionContent = CCLabelTTF::create(missdes->getCString(), "Thonburi", fondSize);
    CCSize sizemCxt = missionContent->getContentSize();
    missionContent->setTag(tag_missionContent);
    missionContent->setPosition(ccp(sizemCxt.width/2-oddleft, size.height/3));
    this->addChild(missionContent,2);
    
    CCLabelTTF* special = CCLabelTTF::create("  ", "Thonburi", fondSize);
    special->setTag(tag_special);
    special->setPosition(ccp(130, size.height - 220 ));
    this->addChild(special,2);
    
    firstCard->setScale(0.7);
    firstCard->setPosition(ccp(size.width / 2 - 120, size.height - 80 ));
    this->addChild(firstCard,1);
    
    return true;    
}

void SelectStage::menuCloseCallback(CCObject *pSender)
{
    CCMenuItemFont *font = (CCMenuItemFont*)pSender;
    int pTag = font->getTag();
    
    switch (pTag) {
        case tag_back:
            CCDirector::sharedDirector()->replaceScene(SelectMode::scene());
            break;            
        default:           
        {
            if (pTag >= stageTag0 && pTag <= stageTage14)
            {
                tag = pTag;
                CCSize size = CCDirector::sharedDirector()->getWinSize();
                CCDictionary *stageInfo = CCDictionary::createWithContentsOfFile("stageInfo.plist");
                
                CCString *tagstr = CCString::createWithFormat("%d",pTag);
                CCDictionary *dic = (CCDictionary *) stageInfo->objectForKey(tagstr->getCString());
                
                CCString *mod    = (CCString *)dic->objectForKey("MODE");                
                CCString *goal    = (CCString *)dic->objectForKey("Goal");
                CCString *num    = (CCString *)dic->objectForKey("num");
                CCString *mission    = (CCString *)dic->objectForKey("MISSIONDESCRIPTION");
                CCString *picture  = (CCString *)dic->objectForKey("smallPic");
                CCSprite *smallBack = (CCSprite *) getChildByTag(tag_smallBack);
                CCSprite *newsmall = CCSprite::create(picture->getCString());
                
                newsmall->setPosition(ccp(size.width / 2 - 120, size.height - 80 ));
                
                CCLabelTTF *matchCXT = (CCLabelTTF *)getChildByTag(tag_match);
                CCLabelTTF *missiONCXT = (CCLabelTTF *)getChildByTag(tag_missionContent);
                CCLabelTTF *specialCXT = (CCLabelTTF *)getChildByTag(tag_special);
                
                smallBack->setTexture(newsmall->getTexture());
            
                matchCXT->setString(mod->getCString());
                missiONCXT->setString(mission->getCString());
            }
            break;
        }
          
    }
    
    
}



