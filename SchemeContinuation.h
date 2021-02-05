#ifndef _SCHEMECONTINUATION_H_
#define _SCHEMECONTINUATION_H_
#include "SchemeValue.h"
#include "SchemeProduce.h"
#include "Frame.h"
class SchemeContinuation: public SchemeProduce
{
public:
    SchemeContinuation(SchemeValue_p proc, SchemeValue_p holder_place, Frame_p env):
        SchemeProduce(env),
        m_holder_place(holder_place),
        m_proc(proc){}
    bool is_continuation() override{return true;}
    std::string to_string() override;
    SchemeValue_p apply(SchemeValue_p params, Frame_p env) override;

private:
    SchemeValue_p m_proc;
    SchemeValue_p m_holder_place;
};
#endif
