#ifndef _SCHEMEPRODUCE_H_
#define _SCHEMEPRODUCE_H_
#include "SchemeValue.h"
#include "Frame.h"
typedef std::function<SchemeValue_p(SchemeValue_p param)> Continuation;
inline SchemeValue_p default_cont(SchemeValue_p param){return param;}

class SchemeProduce: public SchemeValue
{
public:
    SchemeProduce(Frame_p env):m_env(env){}
    bool is_produce(){return true;}
    std::string to_string() override{return "produce";}
    virtual SchemeValue_p apply(SchemeValue_p params, Frame_p env) = 0;
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
    SchemeValue_p apply(SchemeValue_p params, Frame_p env) override;
    std::string to_string()override {return "define";}
};

#endif
