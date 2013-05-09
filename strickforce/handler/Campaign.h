//
//  Campaign.h
//  strickforce
//
//  Created by 03 iphone on 13-5-8.
//
//

#ifndef __strickforce__Campaign__
#define __strickforce__Campaign__

typedef enum campTag
{
    campTag_start =0,
    campTag_soldiers,
    campTag_mainMenu,
    campTag_SelectStage
}campTag;

#include "cocos2d.h"
#include "SelectSave.h"

class Campaign : public SelectSave
{
public:
    
    virtual bool init();
    static cocos2d::CCScene* scene();
    void menuCloseCallback(CCObject* pSender);
    
    void gotoStage(int stageNum);
    
    CREATE_FUNC(Campaign);
private:
    int stageNum;
};


#endif /* defined(__strickforce__Campaign__) */
