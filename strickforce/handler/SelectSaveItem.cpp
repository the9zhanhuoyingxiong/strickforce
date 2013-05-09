//
//  SelectSaveItem.cpp
//  fiire
//
//  Created by 03 iphone on 13-4-28.
//
//
#include "cocos2d.h"
#include "SelectSaveItem.h"
#include "SelectMode.h"

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
    if ( !SelectSave::init() )
    {
        return false;
    }
    
    addSelectColumn();
//    CCSize size = CCDirector::sharedDirector()->getWinSize();
//    CCMenu *menu = CCMenu::create();
//    addChild(menu);
//    menu->setPosition(ccp(size.width/2,size.height/3));
//    CCMenuItemFont *play = CCMenuItemFont::create("play");//,this,menu_selector(fireLayer::menuCloseCallback)
//    menu->addChild(play,2);

    
    return true;
}

void SelectSaveItem::addSelectColumn()
{
    CCLabelTTF *selectsave = CCLabelTTF::create("SELECT SAVE", "Thonburi", 32);
    CCSize  size = CCDirector::sharedDirector()->getWinSize();
   
    
    
    CCMenuItemImage *image1 = CCMenuItemImage::create("selectsaveBackground.png", "selectsaveBackground.png",this,menu_selector(SelectSaveItem::columnSelect));
    CCMenuItemImage *image2 = CCMenuItemImage::create("selectsaveBackground.png", "selectsaveBackground.png");
    CCMenuItemImage *image3 = CCMenuItemImage::create("selectsaveBackground.png", "selectsaveBackground.png");
    
    image1->setTag(Item0);
    image2->setTag(Item1);
    image3->setTag(Item2);
    
    CCMenu *menu = CCMenu::create(image1,image2,image3,NULL);
    addChild(menu);
    menu->alignItemsVertically();
    selectsave->setPosition(ccp(size.width/2, size.height/2));
    menu->setPosition(ccp(size.width/2, size.height/4));
    addChild(selectsave);
    
    CCPoint p  = image1->getPosition();
    
    
//    CCLOG("%f %f",p.x,p.y);
    
}

void SelectSaveItem::columnSelect(CCObject *pSender)
{
    CCMenuItem *item = (CCMenuItem *)pSender;
    int tag = item->getTag();//选择已有数据进行游戏
    
    CCDirector::sharedDirector()->replaceScene(SelectMode::scene());
}





