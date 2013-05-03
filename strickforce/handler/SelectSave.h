//
//  SelectSave.h
//  fiire
//
//  Created by 03 iphone on 13-4-28.
//
//

#ifndef __fiire__SelectSave__
#define __fiire__SelectSave__

#include "cocos2d.h"

class SelectSave : public cocos2d::CCLayer
{
public:
    
    virtual bool init();    
    static cocos2d::CCScene* scene();
    void menuCloseCallback(CCObject* pSender);
    void addSelectColumn();
    CREATE_FUNC(SelectSave);
};


#endif /* defined(__fiire__SelectSave__) */
