#ifndef _SCHEME_COMPARE_H_
#define _SCHEME_COMPARE_H_

#include "../SchemeProduce.h"
class SchemeCompareGT: public SchemeProduce
{
public:
    SchemeCompareGT(Frame_p env):SchemeProduce(env){}
    SchemeValue_p apply(SchemeValue_p params, Frame_p env, Tracker& tracker) override;
};

class SchemeCompareLT: public SchemeProduce
{
public:
    SchemeCompareLT(Frame_p env):SchemeProduce(env){}
    SchemeValue_p apply(SchemeValue_p params, Frame_p env, Tracker& tracker) override;
};

class SchemeCompareEQ: public SchemeProduce
{
public:
    SchemeCompareEQ(Frame_p env):SchemeProduce(env){}
    SchemeValue_p apply(SchemeValue_p params, Frame_p env, Tracker& tracker) override;
};

class SchemeCompareObjectEQ: public SchemeProduce
{
public:
    SchemeCompareObjectEQ(Frame_p env):SchemeProduce(env){}
    SchemeValue_p apply(SchemeValue_p params, Frame_p env, Tracker& tracker) override;
};

#endif
