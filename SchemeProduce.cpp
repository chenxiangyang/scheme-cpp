#include "SchemeProduce.h"
#include "SchemePair.h"
#include "SchemeSymbol.h"
SchemeValue_p SchemeDefine::apply(SchemeValue_p params, Frame_p env)
{
    if(params->is_pair()==false)
        throw std::runtime_error("apply param invalid.");

    SchemePair* pair = params->toType<SchemePair*>();
    auto car = pair->car();
    auto cdr = pair->cdr();
    auto symbol = car->toType<SchemeSymbol*>();
    env->set_env(symbol->value(), cdr);
}