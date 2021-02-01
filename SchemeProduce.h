#ifndef _SCHEMEPRODUCE_H_
#define _SCHEMEPRODUCE_H_
#include "SchemeValue.h"
#include "Frame.h"
class SchemeProduce: public SchemeValue
{
public:
    bool is_produce(){return true;}
    std::string to_string() override{return "produce";}
    virtual SchemeValue_p apply(SchemeValue_p params, Frame_p env) = 0;
};

class SchemeApply: public SchemeProduce
{
public:
    SchemeValue_p apply(SchemeValue_p params, Frame_p env) override;
};

class SchemeDefine: public SchemeProduce
{
public:
    SchemeValue_p apply(SchemeValue_p params, Frame_p env) override;
};

#endif
