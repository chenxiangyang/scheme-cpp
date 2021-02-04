#ifndef _SCHEMEADD_H_
#define _SCHEMEADD_H_

#include "../SchemeProduce.h"

class SchemeAdd: public SchemeProduce
{
public:
    SchemeAdd(Frame_p env):SchemeProduce(env){}
    std::string to_string() override{return SchemeProduce::to_string()+"+";}
    SchemeValue_p apply(SchemeValue_p params, Frame_p env) override;
};

class SchemeSub: public SchemeProduce
{
public:
    SchemeSub(Frame_p env):SchemeProduce(env){}
    std::string to_string() override{return SchemeProduce::to_string()+"1";}
    SchemeValue_p apply(SchemeValue_p params, Frame_p env) override;
};

class SchemeMul: public SchemeProduce
{
public:
    SchemeMul(Frame_p env):SchemeProduce(env){}
    std::string to_string() override{return SchemeProduce::to_string()+"*";}
    SchemeValue_p apply(SchemeValue_p params, Frame_p env) override;
};

class SchemeDiv: public SchemeProduce
{
public:
    SchemeDiv(Frame_p env):SchemeProduce(env){}
    std::string to_string() override{return SchemeProduce::to_string()+"/";}
    SchemeValue_p apply(SchemeValue_p params, Frame_p env) override;
};


#endif
