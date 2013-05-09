//
//  WritePlist.m
//  strickforce
//
//  Created by 03 iphone on 13-5-8.
//
//

#include "WritePlist.h"

#import "UIKit/UIKit.h"
//#import "Foundation/Foundation.h"


NS_CC_BEGIN

void WritePlist::writePlist()
{
    NSString *s = [[NSBundle mainBundle] pathForResource:@"secondStage" ofType:@"plist"];
    NSDictionary *dis = [NSDictionary dictionaryWithContentsOfFile:s];
    
    NSMutableDictionary *mut = [[NSMutableDictionary alloc] initWithCapacity:15];
    for (int i= 0; i < [dis count]; i++)
    {
        [[mut valueForKey:@""] floatValue];
    }
                         
   
}
NS_CC_END