#ifndef _SCHEME_LAMBDA_H_
#define _SCHEME_LAMBDA_H_
#include "SchemeProduce.h"
class SchemeLambda: public SchemeProduce
{
public:
    SchemeLambda(Frame_p env):SchemeProduce(env){}
    SchemeValue_p apply(SchemeValue_p params, Frame_p env, Tracker& tracker) override;
};

class SchemeLambdaExpr: public SchemeProduce
{
public:
    SchemeLambdaExpr(Frame_p env):SchemeProduce(env){}

    std::string to_string() override;
    SchemeValue_p apply(SchemeValue_p params, Frame_p env, Tracker& tracker) override;

    SchemeValue_p m_formal_parameters;
    SchemeValue_p m_body;
};

#endif
