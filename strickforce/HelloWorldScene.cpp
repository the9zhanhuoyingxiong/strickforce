#include "HelloWorldScene.h"
#include "SelectSave.h"
#include "SelectSaveItem.h"
#include "fireLayer.h"
#include "SimpleAudioEngine.h"

using namespace cocos2d;
using namespace CocosDenshion;

CCScene* HelloWorld::scene()
{
    CCScene *scene = CCScene::create();
    HelloWorld *layer = HelloWorld::create();
    scene->addChild(layer);
    return scene;
}

bool HelloWorld::init()
{
    if ( !CCLayer::init() )
    {
        return false;
    }
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    CCSprite *title = CCSprite::create("title.png");
    title->setScale(0.5f);
    title->setPosition(ccp(size.width/2,size.height - title->getContentSize().height/3 ));
    addChild(title,4);
    
    CCSprite* pSprite = CCSprite::create("startGameImage.jpg");
    pSprite->setScale(0.5f);
    pSprite->setPosition( ccp(size.width/2, size.height/2) );
    this->addChild(pSprite, 0);
    
    CCRect rectBack = pSprite->boundingBox();
    CCSize sizeBack = rectBack.size;
    CCPoint posBack = pSprite->getPosition();
    for ( int i = 0 ; i < 5; i++)
    {
        const char *string;
        switch (i)
        {
            case 0:
                string = "THE\nENGINEER";
                break;
            case 1:
                string = "THE\nMERCENARY";
                break;
            case 2:
                string = "THE\nGENERAL";
                break;
            case 3:
                string = "THE\nJUGGERNAUT";
                break;                
            default:
                string = "THE\nSNIPER";
                break;
        }
//        CCLabelBMFont *font = CCLabelBMFont::create(string, "aaa");
//        addChild(font);
        CCMenuItemFont *FONT = CCMenuItemFont::create(string);
//        addChild(FONT);
        FONT->setPosition(ccp(posBack.x+(i-2)/5*sizeBack.width, posBack.y));
//        font->setPosition(ccp(posBack.x+(i-2)/5*sizeBack.width, posBack.y));
        
    }
//    CCMenuItemFont *engineer = CCMenuItemFont::create("THE\nENGINEER");
//    CCMenuItemFont *mercenary = CCMenuItemFont::create("THE\nMERCENARY");
//    CCMenuItemFont *general  = CCMenuItemFont::create("THE\nGENERAL");
//    CCMenuItemFont *juggernaut = CCMenuItemFont::create("");    
    
    CCMenu *menu = CCMenu::create();
    addChild(menu);
    CCMenuItemFont *play = CCMenuItemFont::create("play",this,menu_selector(HelloWorld::menuCloseCallback));
    menu->addChild(play,2);
    menu->setPosition(ccp(size.width/2, play->getContentSize().height));
//    CCFadeTo *fade = CCFadeTo::create(2.0f, 10);
//    pSprite->runAction(fade);
    return true;
}

void HelloWorld::menuCloseCallback(CCObject* pSender)
{
    CCDirector::sharedDirector()->replaceScene(SelectSaveItem::scene());

//#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
//    exit(0);
//#endif
}
