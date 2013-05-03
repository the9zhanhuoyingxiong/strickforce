//
//  SelectSaveItem.h
//  fiire
//
//  Created by 03 iphone on 13-4-28.
//
//

#ifndef __fiire__SelectSaveItem__
#define __fiire__SelectSaveItem__

#include "cocos2d.h"

class SelectSaveItem : public cocos2d::CCLayer
{
public:
    
    virtual bool init();
    static cocos2d::CCScene* scene();
    void menuCloseCallback(CCObject* pSender);
    
    CREATE_FUNC(SelectSaveItem);
};


#endif /* defined(__fiire__SelectSaveItem__) */
