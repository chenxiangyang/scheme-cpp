#include "SchemeIf.h"
#include "../SchemePair.h"
SchemeValue_p SchemeIf::apply(SchemeValue_p params, Frame_p env)
{
    if(!params->is_list())
        throw std::runtime_error(std::string("param is not list:")+params->to_string());

    if(params->toType<SchemePair*>()->count()!=3)
        throw std::runtime_error(std::string("invalid param count:")+params->to_string());

    auto p0 = car(params);
    auto p1 = car(cdr(params));
    auto p2 = car(cdr(cdr(params)));
}
