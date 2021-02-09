#include "SchemeIf.h"
#include "../SchemePair.h"
#include "../SchemeEvaluator.h"
#include "../SchemeBoolean.h"
#include "../SchemeSymbol.h"
SchemeValue_p SchemeIf::apply(SchemeValue_p params, Frame_p env, Tracker& tracker)
{
    if(!params->is_list())
        throw std::runtime_error(std::string("param is not list:")+params->to_string());

    if(params->toType<SchemePair*>()->count()!=3)
        throw std::runtime_error(std::string("invalid param count:")+params->to_string());

    auto p0 = car(params);
    auto p1 = car(cdr(params));
    auto p2 = car(cdr(cdr(params)));

    auto collect = tracker.m_collect_proc;
    Tracker tracker_p0([collect,params](SchemeValue_p param){
        return collect(cons(symbol("if"),
                    cons(param, cdr(params))));
    }, tracker.m_check_proc);

    auto ret = eval(p0, env, tracker_p0);
    if(!ret->is_boolean())
        throw std::runtime_error(std::string("if param 0 return not boolean.")+ret->to_string());

    auto result_expr = (ret.get() == sc_true().get())? p1: p2;

    Tracker tracker_p1([collect](SchemeValue_p param){
        return collect(param);
    }, tracker.m_check_proc);
    return eval(result_expr, env, tracker_p1);
}
