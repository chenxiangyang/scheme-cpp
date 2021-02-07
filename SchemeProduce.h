#ifndef _SCHEMEPRODUCE_H_
#define _SCHEMEPRODUCE_H_
#include <iostream>
#include "SchemeValue.h"
#include "Frame.h"
typedef std::function<SchemeValue_p(SchemeValue_p param)> ContinuationCollector;

typedef std::function<bool(SchemeValue_p)> CheckContinuationProc;

inline SchemeValue_p default_cont(SchemeValue_p param){return param;}
inline bool check_if_in_continuation_default(SchemeValue_p continuation){
    //std::cout<<"***********default check function**********"<<std::endl;
    return false;
}

class Tracker
{
public:
    Tracker()
    {
        m_collect_proc = default_cont;
        m_check_proc = check_if_in_continuation_default;
    }

    Tracker(ContinuationCollector collect_proc, CheckContinuationProc check_proc)
    {
        m_collect_proc = collect_proc;
        m_check_proc = check_proc;
    }

    ContinuationCollector m_collect_proc;

    //check if in target continuation;
    CheckContinuationProc m_check_proc;
};

class SchemeProduce: public SchemeValue
{
public:
    SchemeProduce(Frame_p env):m_env(env){}
    bool is_produce(){return true;}
    std::string to_string() override{return "produce";}
    virtual SchemeValue_p apply(SchemeValue_p params, Frame_p env, Tracker& tracker) = 0;
    Frame_p env()
    {
        return m_env;
    }
protected:
    Frame_p m_env;
};

class SchemeDefine: public SchemeProduce
{
public:
    SchemeDefine(Frame_p env):SchemeProduce(env){}
    SchemeValue_p apply(SchemeValue_p params, Frame_p env, Tracker& tracker) override;
    std::string to_string()override {return "define";}
};

#endif
