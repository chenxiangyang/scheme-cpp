#include "SchemeProduce.h"
#include "SchemePair.h"
#include "SchemeSymbol.h"
#include "SchemeEvaluator.h"
SchemeValue_p SchemeDefine::apply(SchemeValue_p params, Frame_p env)
{
    if(params->is_pair()==false)
        throw std::runtime_error("apply param invalid.");

    SchemePair* pair = params->toType<SchemePair*>();
    auto first = pair->car();
    auto rest = pair->cdr();

    if(first->is_symbol())
    {
        auto symbol = first->toType<SchemeSymbol*>();
        m_env->set_env(symbol->value(), eval(rest->toType<SchemePair*>()->car(), m_env));
    }
    else if(first->is_list())
    {
        auto func_name = ::car(first);
        auto formal_params = ::cdr(first);

        auto expr = cons(std::make_shared<SchemeSymbol>("lambda"),cons(formal_params, rest));

        auto symbol = func_name->toType<SchemeSymbol*>();
        m_env->set_env(symbol->value(), eval(expr, m_env));
    }

    return nil();
}
