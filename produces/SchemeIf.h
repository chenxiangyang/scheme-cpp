#ifndef _SCHEME_IF_H_
#define _SCHEME_IF_H_

#include "../SchemeProduce.h"
class SchemeIf: public SchemeProduce
{
public:
    SchemeIf(Frame_p env): SchemeProduce(env){}
    std::string to_string() override{return SchemeProduce::to_string()+":if";}
    SchemeValue_p apply(SchemeValue_p params, Frame_p env, Tracker& tracker) override;
};

#endif
