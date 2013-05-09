//
//  SelectMode.h
//  fiire
//
//  Created by 03 iphone on 13-5-7.
//
//

#ifndef __fiire__SelectMode__
#define __fiire__SelectMode__

#include "cocos2d.h"
#include "SelectSave.h"

class SelectMode : public SelectSave
{
public:
    
    virtual bool init();
    static cocos2d::CCScene* scene();
    void menuCloseCallback(CCObject* pSender);
    void selectMode();
    void selectSave();
    void selectCampaign();
    
    CREATE_FUNC(SelectMode);
};


#endif /* defined(__fiire__SelectMode__) */
