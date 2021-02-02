#ifndef _SCHEMEADD_H_
#define _SCHEMEADD_H_

#include "../SchemeProduce.h"

class SchemeAdd: public SchemeProduce
{
public:
    SchemeAdd(Frame_p env):SchemeProduce(env){}
    SchemeValue_p apply(SchemeValue_p params) override;
};

class SchemeSub: public SchemeProduce
{
public:
    SchemeSub(Frame_p env):SchemeProduce(env){}
    SchemeValue_p apply(SchemeValue_p params) override;
};


#endif
