#ifndef _SCHEMECOMMPRODUCE_H_
#define _SCHEMECOMMPRODUCE_H_

#include "../SchemeProduce.h"
#include <functional>
typedef std::function<SchemeValue_p(SchemeValue_p,Frame_p,Frame_p,Tracker&)> CommFunc;
class SchemeCommonProduce: public SchemeProduce
{
public:
    SchemeCommonProduce(CommFunc func, Frame_p env, std::string func_name):
        SchemeProduce(env),m_func(func),m_func_name(func_name){}
    std::string to_string()override
    {
        return SchemeProduce::to_string()+":"+m_func_name;
    }
    SchemeValue_p apply(SchemeValue_p params, Frame_p env, Tracker& tracker) override;
private:
    CommFunc m_func;
    std::string m_func_name;
};

SchemeValue_p produce_cons(SchemeValue_p param,Frame_p env,Frame_p func_env,Tracker& tracker);
SchemeValue_p produce_car(SchemeValue_p param,Frame_p env,Frame_p func_env,Tracker& tracker);
SchemeValue_p produce_cdr(SchemeValue_p param,Frame_p env,Frame_p func_env,Tracker& tracker);
SchemeValue_p produce_quote(SchemeValue_p param,Frame_p env,Frame_p func_env,Tracker& tracker);
SchemeValue_p produce_eval(SchemeValue_p param,Frame_p env,Frame_p func_env,Tracker& tracker);
SchemeValue_p produce_show_env(SchemeValue_p param,Frame_p env,Frame_p func_env,Tracker& tracker);
SchemeValue_p produce_begin(SchemeValue_p param,Frame_p env,Frame_p func_env,Tracker& tracker);
SchemeValue_p produce_display(SchemeValue_p param,Frame_p env,Frame_p func_env,Tracker& tracker);
SchemeValue_p produce_load(SchemeValue_p param, Frame_p env, Frame_p func_env,Tracker& tracker);
SchemeValue_p load(std::string file, Frame_p env);
SchemeValue_p produce_call_with_current_context(SchemeValue_p param, Frame_p env, Frame_p func_env,Tracker& tracker);
SchemeValue_p produce_set_change(SchemeValue_p param, Frame_p env, Frame_p func_env,Tracker& tracker);

#endif
