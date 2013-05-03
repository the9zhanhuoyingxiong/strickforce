//
//  Amok_Jebat.cpp
//  HelloWorld
//
//  Created by The9 on 13-4-21.
//
//

#include "Amok_Jebat.h"


bool Amok_Jebat::init(tag_amok tag)
{
    if (!Person::init())
    {
        return false;
    }
    
    flag = tag;
    
    CCSpriteFrameCache *frameCache = CCSpriteFrameCache::sharedSpriteFrameCache();
    frameCache->addSpriteFramesWithFile("JebatSpriteFrame.plist");
    
    CCRepeat *rep = this->createAnim(tag);
     this->initWithSpriteFrameName(string->getCString());
    
        
    if (tag != Amok_stand  )
    {
        this->runAction(rep);
    }
    
    else
    {
        CCRepeatForever *forever = CCRepeatForever::create(rep);
        this->runAction(forever);
    }
    
        
    return true;
}


Amok_Jebat * Amok_Jebat::create(tag_amok tag)
{
    Amok_Jebat *pobSprite = new Amok_Jebat();
    if (pobSprite && pobSprite->init(tag))
    {
        pobSprite->autorelease();
        return pobSprite;
    }
    CC_SAFE_DELETE(pobSprite);
    return NULL;

}

void Amok_Jebat::runAtTheDic()
{
    
    if (getFlag() != Amok_run)
    {
        this->stopAllActions();
        CCRepeatForever *forer = CCRepeatForever::create(createAnim(Amok_run));
        this->runAction(forer);
    }
    
}

void Amok_Jebat::dorunning()
{
    if (getFlag() != Amok_run)
    {
        stopAllActions();
        CCRepeatForever *forever = CCRepeatForever::create(createAnim(Amok_run));
        runAction(forever);
    }

}

void Amok_Jebat::runOrbit()
{
    this->changeDirecion();
    
     this->stopAllActions();
     CCRepeatForever *f = CCRepeatForever::create(createAnim(Amok_run));
    this->runAction(f);
    CCOrbitCamera *orbit = CCOrbitCamera::create(0.01f, 1, 0, 0, 180*getDirection(), 0, 0);
    this->runAction(orbit);
    
}

CCRepeat  * Amok_Jebat::createAnim(tag_amok tag)
{
     this->flag = tag;
    CCRepeat  *rep;
    
    switch (tag)
    {
        case Amok_attack1:
        {
            rep = Amok_Jebat::create("AMOK_JEBAT_attack1_", 11, 0.05f, 1);
            string = CCString::create("AMOK_JEBAT_attack1_1.png");
            break;
        }
        case Amok_attack2:
        {
            rep  = Amok_Jebat::create("AMOK_JEBAT_attack2_", 10, 0.05f, 1);
            string = CCString::create("AMOK_JEBAT_attack2_1.png");
            break;
        }
        case Amok_attack3:
        {
            rep = Amok_Jebat::create("AMOK_JEBAT_attack3_", 10 , 0.05f, 1);
            string = CCString::create("AMOK_JEBAT_attack3_1.png");
            break;
        }
        case Amok_attack4:
        {
            rep = Amok_Jebat::create("AMOK_JEBAT_attack4_", 26, 0.05f, 1);
            string = CCString::create("AMOK_JEBAT_attack4_1.png");
            break;
        }
        case Amok_attack5:
        {
            rep = Amok_Jebat::create("AMOK_JEBAT_attack5_", 20, 0.05f, 1);
            string = CCString::create("AMOK_JEBAT_attack5_1.png");
            break;
        }
        case Amok_autojump:
        {
            rep = Amok_Jebat::create("AMOK_JEBAT_autojump_", 15, 0.05f, 1);
            string = CCString::create("AMOK_JEBAT_autojump_1.png");
            break;
        }
        case Amok_die:
        {
            rep = Amok_Jebat::create("AMOK_JEBAT_die_", 13, 0.05f, 1);
            string = CCString::create("AMOK_JEBAT_die_1.png");
            
            break;
        }
        case Amok_hurt:
        {
            rep = Amok_Jebat::create("AMOK_JEBAT_hurt_", 8, 0.05f, 1);
            string = CCString::create("AMOK_JEBAT_hurt_1.png");
            break;
        }
        case Amok_jump:
        {
            rep = Amok_Jebat::create("AMOK_JEBAT_jump_", 18, 0.05f, 1);
            string = CCString::create("AMOK_JEBAT_jump_1.png");
            break;
        }
        case Amok_run:
        {
            rep = Amok_Jebat::create("AMOK_JEBAT_run_", 18, 0.05f, 1);
            string = CCString::create("AMOK_JEBAT_run_1.png");
            break;
        }
        case Amok_slide:
        {
            rep = Amok_Jebat::create("AMOK_JEBAT_slide_",13 , 0.05f, 1);
            string = CCString::create("AMOK_JEBAT_slide_1.png");
            break;
        }
        case Amok_stand:
        {
            rep = Amok_Jebat::create("AMOK_JEBAT_stand_",18 , 0.05f, 78);//没有 9
            string = CCString::create("AMOK_JEBAT_stand_1.png");
            break;
        }
        default:
            break;
    }
    return  rep;

}

CCRepeat  * Amok_Jebat::create(const char *str, int numberPic, float delay, int times)
{
    CCString *string;
    
    CCSpriteFrameCache *frameCache = CCSpriteFrameCache::sharedSpriteFrameCache();
    frameCache->addSpriteFramesWithFile("JebatSpriteFrame.plist", "JebatSpriteFrame.png");
    
    CCArray *frames = CCArray::createWithCapacity(numberPic);
    
    for (int i = 1 ; i <= numberPic; i ++)
    {
        string = CCString::createWithFormat("%s%d.png",str,i);
        CCSpriteFrame *fram = frameCache->spriteFrameByName(string->getCString());
        frames->addObject(fram);
    }
    
    CCAnimation *animation = CCAnimation::createWithSpriteFrames(frames,delay);
    CCAnimate   *animate   = CCAnimate::create(animation);
    CCRepeat    *rep       = CCRepeat::create(animate, times);

    return rep;
}

int Amok_Jebat::getFlag()
{
    return flag;
}

void Amok_Jebat::turnLeft()
{
    int direc = getDirection();
    if (direc == faceToLeft)
    {
        runAtTheDic();
    }
    else if (direc == faceToRight)
    {
        runOrbit();
    }

}

void Amok_Jebat::turnRight()
{
    int direc = getDirection();
    if (direc == faceToRight)
    {
        runAtTheDic();
    }
    if (direc == faceToLeft)
    {
        runOrbit();
    }

}

void Amok_Jebat::doStanding()
{
    if (getFlag() != Amok_stand)
    {
        stopAllActions();
        runAction(createAnim(Amok_stand));
    }
   
}
void Amok_Jebat::doJump()
{
    if (getFlag() != Amok_jump)
    {
        stopAllActions();
        runAction(createAnim(Amok_jump));
    }
}


void Amok_Jebat::changeToAnim(tag_amok tag)
{
    
    if (getFlag() != flag)
    {
        this->stopAllActions();
        CCRepeat *rep =  createAnim(tag);
        CCRepeat *re  =  createAnim(Amok_stand);
        CCSequence *seq = (CCSequence *)CCSequence::create(rep,re,NULL);
        
        runAction(seq);

    }
}


void Amok_Jebat::setStartPos()
{
    
}



