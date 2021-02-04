#ifndef _SCHEMECOMMPRODUCE_H_
#define _SCHEMECOMMPRODUCE_H_

#include "../SchemeProduce.h"
#include <functional>
typedef std::function<SchemeValue_p(SchemeValue_p,Frame_p,Frame_p)> CommFunc;
class SchemeCommonProduce: public SchemeProduce
{
public:
    SchemeCommonProduce(CommFunc func, Frame_p env):
        SchemeProduce(env),m_func(func){}
    SchemeValue_p apply(SchemeValue_p params, Frame_p env) override;
private:
    CommFunc m_func;
};

SchemeValue_p produce_cons(SchemeValue_p param,Frame_p env,Frame_p func_env);
SchemeValue_p produce_car(SchemeValue_p param,Frame_p env,Frame_p func_env);
SchemeValue_p produce_cdr(SchemeValue_p param,Frame_p env,Frame_p func_env);
SchemeValue_p produce_quote(SchemeValue_p param,Frame_p env,Frame_p func_env);
SchemeValue_p produce_eval(SchemeValue_p param,Frame_p env,Frame_p func_env);
SchemeValue_p produce_show_env(SchemeValue_p param,Frame_p env,Frame_p func_env);
SchemeValue_p produce_begin(SchemeValue_p param,Frame_p env,Frame_p func_env);
SchemeValue_p produce_display(SchemeValue_p param,Frame_p env,Frame_p func_env);
SchemeValue_p produce_load(SchemeValue_p param, Frame_p env, Frame_p func_env);
SchemeValue_p load(std::string file, Frame_p env);
SchemeValue_p produce_call_with_current_context(SchemeValue_p param, Frame_p env, Frame_p func_env);
SchemeValue_p produce_set_change(SchemeValue_p param, Frame_p env, Frame_p func_env);

#endif
