#include <iostream>
#include "SchemeCommProduce.h"
#include "../SchemePair.h"
#include "../SchemeEvaluator.h"
SchemeValue_p SchemeCommonProduce::apply(SchemeValue_p params, Frame_p env)
{
    return m_func(params, env, m_env);
}

SchemeValue_p produce_cons(SchemeValue_p params, Frame_p env, Frame_p func_env)
{
    if(!params->is_list() || params->toType<SchemePair*>()->count()!=2)
        throw std::runtime_error(std::string("invalid cons params:")+params->to_string());

    std::cout<<"cons param:"<<params->to_string()<<std::endl;
    return cons(car(params), car(cdr(params)));
}

SchemeValue_p produce_car(SchemeValue_p param, Frame_p env, Frame_p func_env)
{
    //std::cout<<"car param:"<<param->to_string()<<std::endl;
    if(!param->is_pair())
        throw std::runtime_error(std::string("invalid car params:")+param->to_string());
    auto result = car(car(param));
    //std::cout<<"car result:"<<result->to_string()<<std::endl;
    return result;
}

SchemeValue_p produce_cdr(SchemeValue_p param, Frame_p env, Frame_p func_env)
{
    //std::cout<<"cdr param:"<<param->to_string()<<std::endl;
    if(!param->is_pair())
        throw std::runtime_error(std::string("invalid cdr params:")+param->to_string());
    auto result = cdr(car(param));
    //std::cout<<"cdr result:"<<result->to_string()<<std::endl;
    return result;
}

SchemeValue_p produce_quote(SchemeValue_p param, Frame_p env, Frame_p func_env)
{
    if(param->is_pair() && cdr(param)!=nil())
        throw std::runtime_error(std::string("invalid quote params:")+param->to_string());
    return car(param);
}

SchemeValue_p produce_eval(SchemeValue_p param, Frame_p env, Frame_p func_env)
{
    //if(!param->is_list() || cdr(param)==nil())
    //    throw std::runtime_error(std::string("invalid eval params:")+param->to_string());
    return eval(car(param), env);
}
