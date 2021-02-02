#include "SchemeAdd.h"
#include "../SchemeEvaluator.h"
#include "../SchemePair.h"
#include "../SchemeNumber.h"
SchemeValue_p SchemeAdd::apply(SchemeValue_p params, Frame_p env)
{
    float sum = 0.0;

    while(params->is_pair())
    {
        auto first = car(params);
        auto num = eval(first, m_env);

        if(num->is_number() == false)
            throw std::runtime_error(std::string("SchemeAdd::apply num is not number, it's ")+num->to_string());

        auto scfvalue = num->toType<SchemeFloat*>();

        if(scfvalue)
            sum += scfvalue->m_value;
        else
            sum += num->toType<SchemeInteger*>()->m_value;

        params = cdr(params);
    }
    return std::make_shared<SchemeFloat>(sum);
}

SchemeValue_p SchemeSub::apply(SchemeValue_p params, Frame_p env)
{
    float sum = 0.0;

    auto minuend = car(params);
    params = cdr(params);
    if(minuend->toType<SchemeFloat*>())
        sum = minuend->toType<SchemeFloat*>()->m_value;
    else if(minuend->toType<SchemeInteger*>())
        sum = minuend->toType<SchemeInteger*>()->m_value;
    while(params->is_pair())
    {
        auto first = car(params);
        auto num = eval(first, m_env);

        if(num->is_number() == false)
            throw std::runtime_error(std::string("SchemeAdd::apply num is not number, it's ")+num->to_string());

        auto scfvalue = num->toType<SchemeFloat*>();

        if(scfvalue)
            sum -= scfvalue->m_value;
        else
            sum -= num->toType<SchemeInteger*>()->m_value;

        params = cdr(params);
    }
    return std::make_shared<SchemeFloat>(sum);
}
