#ifndef _SCHEMEPRODUCE_H_
#define _SCHEMEPRODUCE_H_
#include "SchemeValue.h"
#include "Frame.h"
class SchemeProduce: public SchemeValue
{
public:
    SchemeProduce(Frame_p env):m_env(env){}
    bool is_produce(){return true;}
    std::string to_string() override{return "produce";}
    virtual SchemeValue_p apply(SchemeValue_p params) = 0;
protected:
    Frame_p m_env;
};

class SchemeApply: public SchemeProduce
{
public:
    SchemeValue_p apply(SchemeValue_p params) override;
};

class SchemeDefine: public SchemeProduce
{
public:
    SchemeDefine(Frame_p env):SchemeProduce(env){}
    SchemeValue_p apply(SchemeValue_p params) override;
};

#endif
