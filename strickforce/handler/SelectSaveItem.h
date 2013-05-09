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
#include "SelectSave.h"

typedef enum Item
{
    Item0 = 10,
    Item1,
    Item2
}Item;

class SelectSaveItem : public SelectSave
{
public:
    
    virtual bool init();
    static cocos2d::CCScene* scene();
    void menuCloseCallback(CCObject* pSender);
    void addSelectColumn();
    void columnSelect(CCObject* pSender);

    CREATE_FUNC(SelectSaveItem);
};


#endif /* defined(__fiire__SelectSaveItem__) */
