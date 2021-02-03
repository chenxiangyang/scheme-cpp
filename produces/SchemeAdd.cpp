#include <functional>
#include "SchemeAdd.h"
#include "../SchemeEvaluator.h"
#include "../SchemePair.h"
#include "../SchemeNumber.h"

typedef std::function<int(int,int)> ReduceOpInt;
typedef std::function<float(float,float)> ReduceOpFloat;

SchemeValue_p eval_reduce( ReduceOpFloat func_float, ReduceOpInt func_int, SchemeValue_p params)
{
    float sum_float = 0.0;
    int sum_int = 0;
    bool all_param_int = true;

    auto minuend = car(params);
    params = cdr(params);
    if(minuend->toType<SchemeFloat*>())
    {
        all_param_int = false;
        sum_float = minuend->toType<SchemeFloat*>()->m_value;
    }
    else if(minuend->toType<SchemeInteger*>())
    {
        sum_int = minuend->toType<SchemeInteger*>()->m_value;
        sum_float = sum_int;
    }
    while(params->is_pair())
    {
        auto first = car(params);
        auto num = first;

        if(num->is_number() == false)
            throw std::runtime_error(std::string("eval_reduce::apply num is not number, it's ")+num->to_string());

        auto scfvalue = num->toType<SchemeFloat*>();

        if(scfvalue)
        {
            all_param_int = false;
            sum_float = func_float(sum_float, scfvalue->m_value);
        }
        else
        {
            sum_int = func_int(sum_int, num->toType<SchemeInteger*>()->m_value);
            sum_float = func_float(sum_float, num->toType<SchemeInteger*>()->m_value);
        }

        params = cdr(params);
    }
    if(all_param_int)
        return std::make_shared<SchemeInteger>(sum_int);
    return std::make_shared<SchemeFloat>(sum_float);
}

SchemeValue_p SchemeAdd::apply(SchemeValue_p params, Frame_p env)
{
    return eval_reduce([](float x, float y){return x+y;}, [](int x,int y){return x+y;},params);
}

SchemeValue_p SchemeSub::apply(SchemeValue_p params, Frame_p env)
{
    return eval_reduce([](float x, float y){return x-y;}, [](int x,int y){return x-y;},params);
}

SchemeValue_p SchemeMul::apply(SchemeValue_p params, Frame_p env)
{
    return eval_reduce([](float x, float y){return x*y;}, [](int x,int y){return x*y;},params);
}

SchemeValue_p SchemeDiv::apply(SchemeValue_p params, Frame_p env)
{
    return eval_reduce([](float x, float y){return x/y;}, [](int x,int y){return x/y;},params);
}
