#include <iostream>
#include "SchemeCommProduce.h"
#include "../SchemePair.h"
#include "../SchemeEvaluator.h"
#include "../SchemeString.h"
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

SchemeValue_p produce_show_env(SchemeValue_p param, Frame_p env, Frame_p func_env)
{
    if(param->is_nil())
    {
        std::string str("func env:");
        str+=func_env->to_string(true);
        str+="\ncurrent env:";
        str+=env->to_string(true);
        auto result = std::make_shared<SchemeString>(str);
        //std::cout<<str<<std::endl;
        return result;
    }
    else if(param->is_list() && cdr(param)==nil())
    {
        auto func = car(param);
        if(!func->is_produce())
            throw std::runtime_error(std::string("param is not a produce:")+func->to_string());

        auto produce = func->toType<SchemeProduce*>();
        auto env = produce->env();
        std::string str = func->to_string();
        str += " env:";
        str += env->to_string(true);
        //std::cout<<str<<std::endl;
        return std::make_shared<SchemeString>(str);
    }
    throw std::runtime_error(std::string("invalid show_env param:")+param->to_string());
}

SchemeValue_p produce_begin(SchemeValue_p param, Frame_p env, Frame_p func_env)
{
    if(!param->is_list())
        throw std::runtime_error(std::string("invalid begin param:")+param->to_string());

    while(1)
    {
        if(cdr(param)==nil())
            return car(param);
        param = cdr(param);
    }
}

SchemeValue_p produce_display(SchemeValue_p param, Frame_p env, Frame_p func_env)
{
    std::cout<<car(param)->to_string()<<std::endl;
    return nil();
}
