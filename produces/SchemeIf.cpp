#include "SchemeIf.h"
#include "../SchemePair.h"
#include "../SchemeEvaluator.h"
#include "../SchemeBoolean.h"
SchemeValue_p SchemeIf::apply(SchemeValue_p params, Frame_p env, Tracker& tracker)
{
    if(!params->is_list())
        throw std::runtime_error(std::string("param is not list:")+params->to_string());

    if(params->toType<SchemePair*>()->count()!=3)
        throw std::runtime_error(std::string("invalid param count:")+params->to_string());

    auto p0 = car(params);
    auto p1 = car(cdr(params));
    auto p2 = car(cdr(cdr(params)));
    auto ret = eval(p0, env, tracker);
    if(!ret->is_boolean())
        throw std::runtime_error(std::string("if param 0 return not boolean.")+ret->to_string());

    if(ret.get() == sc_true().get())
        return eval(p1, env, tracker);
    else
        return eval(p2, env, tracker);
}
