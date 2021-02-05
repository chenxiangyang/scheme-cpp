#ifndef _SCHEMECONTINUATION_H_
#define _SCHEMECONTINUATION_H_
#include "SchemeValue.h"
#include "SchemeProduce.h"
#include "Frame.h"
#include <iostream>
class SchemeContinuation: public SchemeProduce
{
public:
    SchemeContinuation(SchemeValue_p proc, SchemeValue_p holder_place, Frame_p env):
        SchemeProduce(env),
        m_holder_place(holder_place),
        m_proc(proc){
        std::cout<<"SchemeContinuation:"<<m_proc->to_string()<<std::endl;
    }
    bool is_continuation() override{return true;}
    std::string to_string() override;
    SchemeValue_p apply(SchemeValue_p params, Frame_p env) override;

private:
    SchemeValue_p m_proc;
    SchemeValue_p m_holder_place;
};

class ContinuationException: public std::exception
{
public:
    ContinuationException(SchemeValue_p ret, SchemeValue_p continuation):
        m_return(ret),m_continuation(continuation){}

    const char* what() const noexcept
    {
        //std::cout<<m_return->to_string().c_str();
        return m_return->to_string().c_str();
    }

    SchemeValue_p return_value()
    {
        return m_return;
    }

    SchemeValue_p continuation_value()
    {
        return m_continuation;
    }

private:
    SchemeValue_p m_return;
    SchemeValue_p m_continuation;
};

#endif
