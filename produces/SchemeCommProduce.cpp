#include <iostream>
#include <fstream>
#include "../SchemeReader.h"
#include "../SchemeTokens.h"
#include "SchemeCommProduce.h"
#include "../SchemePair.h"
#include "../SchemeEvaluator.h"
#include "../SchemeString.h"
#include "../SchemeBoolean.h"
#include "../SchemeSymbol.h"
#include "../SchemeContinuation.h"
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

SchemeValue_p load(std::string file, Frame_p env)
{
    std::ifstream in;
    in.open(file);
    if(in.is_open()==false)
    {
        std::cout<<"invalid file:"<<file<<std::endl;
        return sc_false();
    }

    auto reader = std::make_shared<SchemeReader>([&in](){
        char c = 0;
        if(!in.eof())
        {
            in.read(&c,1);
            return c;
        }
        return c;
    });

    auto token = std::make_shared<SchemeTokens>(reader);

    SchemeValue_p ret = sc_false();
    while(1)
    {
        try{
            auto first = get_line(token);
            if(first==NULL)
                return ret;
            ret = ::eval(first, env);
        }
        catch(std::exception& e)
        {
            std::cout<<e.what()<<std::endl;
            break;
        }
    }
    return sc_false();
}

SchemeValue_p produce_load(SchemeValue_p param, Frame_p env, Frame_p func_env)
{
    if(!param->is_list())
        throw std::runtime_error(std::string() + "invalid load param:" + param->to_string());

    SchemeValue_p ret = sc_false();
    while(1)
    {
        if(param->is_nil())
            break;
        auto name = car(param);
        if(!name->is_string())
            throw std::runtime_error(std::string() + "invalid name type:" + name->to_string());

        ret = load(name->toType<SchemeString*>()->value(), env);

        param = cdr(param);
    }

    return ret;
}

SchemeValue_p produce_call_with_current_context(SchemeValue_p param, Frame_p env, Frame_p func_env)
{
    return nil();
}

SchemeValue_p produce_set_change(SchemeValue_p param, Frame_p env, Frame_p func_env)
{
    if(!param->is_list() || param->toType<SchemePair*>()->count()!=2)
        throw std::runtime_error(std::string()+"invalid set! param:"+param->to_string());
    auto name = car(param);
    auto ctx = eval(car(cdr(param)),env);

    if(!name->is_symbol())
        throw std::runtime_error(std::string()+"set! param name is not symbol:"+name->to_string());

    env->change_env(name->toType<SchemeSymbol*>()->value(), ctx);
    return sc_true();
}
