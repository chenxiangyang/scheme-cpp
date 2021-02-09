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
SchemeValue_p SchemeCommonProduce::apply(SchemeValue_p params, Frame_p env, Tracker &tracker)
{
    return m_func(params, env, m_env, tracker);
}

SchemeValue_p produce_cons(SchemeValue_p params, Frame_p env, Frame_p func_env, Tracker &tracker)
{
    if(!params->is_list() || params->toType<SchemePair*>()->count()!=2)
        throw std::runtime_error(std::string("invalid cons params:")+params->to_string());

    std::cout<<"cons param:"<<params->to_string()<<std::endl;
    return cons(car(params), car(cdr(params)));
}

SchemeValue_p produce_car(SchemeValue_p param, Frame_p env, Frame_p func_env,Tracker& tracker)
{
    //std::cout<<"car param:"<<param->to_string()<<std::endl;
    if(!param->is_pair())
        throw std::runtime_error(std::string("invalid car params:")+param->to_string());
    auto result = car(car(param));
    //std::cout<<"car result:"<<result->to_string()<<std::endl;
    return result;
}

SchemeValue_p produce_cdr(SchemeValue_p param, Frame_p env, Frame_p func_env,Tracker& tracker)
{
    //std::cout<<"cdr param:"<<param->to_string()<<std::endl;
    if(!param->is_pair())
        throw std::runtime_error(std::string("invalid cdr params:")+param->to_string());
    auto result = cdr(car(param));
    //std::cout<<"cdr result:"<<result->to_string()<<std::endl;
    return result;
}

SchemeValue_p produce_quote(SchemeValue_p param, Frame_p env, Frame_p func_env,Tracker& tracker)
{
    if(param->is_pair() && cdr(param)!=nil())
        throw std::runtime_error(std::string("invalid quote params:")+param->to_string());
    return car(param);
}

SchemeValue_p produce_eval(SchemeValue_p param, Frame_p env, Frame_p func_env, Tracker& tracker)
{
    //if(!param->is_list() || cdr(param)==nil())
    //    throw std::runtime_error(std::string("invalid eval params:")+param->to_string());
    //Tracker tracker;
    return eval(car(param), env, tracker);
}

SchemeValue_p produce_show_env(SchemeValue_p param, Frame_p env, Frame_p func_env,Tracker& tracker)
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

SchemeValue_p produce_begin(SchemeValue_p param, Frame_p env, Frame_p func_env,Tracker& tracker)
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

SchemeValue_p produce_display(SchemeValue_p param, Frame_p env, Frame_p func_env,Tracker& tracker)
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
            auto first = get_line(token);
            if(first==NULL)
                return ret;
            Tracker tracker;
            ret = ::eval(first, env, tracker);
            try{
        }
        catch(std::exception& e)
        {
            std::cerr<<e.what()<<std::endl;
            break;
        }
    }
    return sc_false();
}

SchemeValue_p produce_load(SchemeValue_p param, Frame_p env, Frame_p func_env,Tracker& tracker)
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

SchemeValue_p produce_call_with_current_context(SchemeValue_p param, Frame_p env, Frame_p func_env,Tracker& tracker)
{
    auto& collector = tracker.m_collect_proc;
    auto& check_proc = tracker.m_check_proc;
    auto holder = std::make_shared<SchemeString>("__call/cc__placeholder__");
    auto ret = collector(holder);
    //std::cout<<ret->to_string()<<std::endl;
    auto contin = std::make_shared<SchemeContinuation>(ret, holder, env);

    auto check_cont = [contin, check_proc](SchemeValue_p cont){
        //std::cout<<"<<<<<in check function>>>>>"<<std::endl;
            return contin==cont || check_proc(cont);
    };
    Tracker call_cc_tracker(default_cont, check_cont);
    auto lambda = eval(car(param), env, call_cc_tracker);

    if(!lambda->is_produce())
        std::runtime_error(std::string()+"param of call/cc must be produce,"+lambda->to_string());
    try{
        return lambda->toType<SchemeProduce*>()->apply(cons(contin,nil()), env, call_cc_tracker);
    }
    catch(ContinuationException& e)
    {
        if(e.continuation_value() == contin)
            return e.return_value();
        throw e;
    }
}

SchemeValue_p produce_set_change(SchemeValue_p param, Frame_p env, Frame_p func_env,Tracker& tracker)
{
    if(!param->is_list() || param->toType<SchemePair*>()->count()!=2)
        throw std::runtime_error(std::string()+"invalid set! param:"+param->to_string());
    auto name = car(param);

    auto collect = tracker.m_collect_proc;
    auto this_tracker = Tracker([name,collect](SchemeValue_p param){
            return collect(cons(symbol("set!"),
                                cons(name, cons(param,nil()))));},tracker.m_check_proc);

    auto ctx = eval(car(cdr(param)),env,this_tracker);

    if(!name->is_symbol())
        throw std::runtime_error(std::string()+"set! param name is not symbol:"+name->to_string());

    env->change_env(name->toType<SchemeSymbol*>()->value(), ctx);
    return sc_true();
}
