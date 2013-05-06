//
//  Amok_Jebat.h
//  HelloWorld
//
//  Created by The9 on 13-4-21.
//
//

#ifndef __HelloWorld__Amok_Jebat__
#define __HelloWorld__Amok_Jebat__

#include "cocos2d.h"
#include "Person.h"
#include "Box2D.h"


typedef enum tag_amok
{
    Amok_attack1 = 0,
    Amok_attack2,
    Amok_attack3,
    Amok_attack4,
    Amok_attack5,
    Amok_autojump,
    Amok_die,
    Amok_hurt,
    Amok_jump,
    Amok_run,
    Amok_slide,
    Amok_stand
    
}tag_amok;



using namespace cocos2d;

class Amok_Jebat : public Person{
    
public:
    
    bool init(tag_amok  tag);
    int  getFlag();
    
    static Amok_Jebat * create(tag_amok tag);
    
    CCRepeat * createAnim(tag_amok  tag);
    
    CCRepeat * create(const char *str , int numberPic , float delay , int times);
    
    virtual void runAtTheDic();
    virtual void runOrbit();
    void changeToAnim(tag_amok tag);
    
    void setStartPos();
    void dorunning();
    void turnLeft();
    void turnRight();
    
    void doStanding();
    void doJump();

private:
    CCString *string;
    int flag;
    int stayLineNumber;
public:
    b2Body *amokBody;
    bool isUp;
    bool isDown;
    bool isLeft;
    bool isRight;
    
};


#endif /* defined(__HelloWorld__Amok_Jebat__) */
