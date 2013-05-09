//
//  SelectStage.h
//  strickforce
//
//  Created by 03 iphone on 13-5-8.
//
//

#ifndef __strickforce__SelectStage__
#define __strickforce__SelectStage__

#include "cocos2d.h"
#include "SelectSave.h"
#include "tags.h"


class SelectStage : public cocos2d::CCLayer
{
public:
    
    virtual bool init();
    static cocos2d::CCScene* scene();
    void menuCloseCallback(CCObject* pSender);
    void selectCampaign();
    
    CREATE_FUNC(SelectStage);
    
    
    int tag;
};


#endif /* defined(__strickforce__SelectStage__) */
