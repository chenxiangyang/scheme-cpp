#include <vector>
#include <iostream>
#include <algorithm>
#include "SchemeEvaluator.h"
#include "SchemeProduce.h"
#include "SchemeSymbol.h"
#include "SchemePair.h"
#include "SchemeLambda.h"
#include "SchemeString.h"
#include "produces/SchemeAdd.h"
#include "produces/SchemeIf.h"
#include "produces/SchemeCompare.h"
#include "produces/SchemeCommProduce.h"
#include "SchemeContinuation.h"

std::vector<std::string> raw_func_name_list = {
    "define","lambda","if","quote","set!"
};

SchemeEvaluator::SchemeEvaluator()
{
    m_global = create_frame();

    m_global->set_env("define", SchemeValue_p(new SchemeDefine(m_global)));
    m_global->set_env("lambda", SchemeValue_p(new SchemeLambda(m_global)));
    m_global->set_env("if", SchemeValue_p(new SchemeIf(m_global)));
    m_global->set_env("+", SchemeValue_p(new SchemeAdd(m_global)));
    m_global->set_env("-", SchemeValue_p(new SchemeSub(m_global)));
    m_global->set_env("*", SchemeValue_p(new SchemeMul(m_global)));
    m_global->set_env("/", SchemeValue_p(new SchemeDiv(m_global)));
    m_global->set_env(">", SchemeValue_p(new SchemeCompareGT(m_global)));
    m_global->set_env("<", SchemeValue_p(new SchemeCompareLT(m_global)));
    m_global->set_env("=", SchemeValue_p(new SchemeCompareEQ(m_global)));
    m_global->set_env("eq?", SchemeValue_p(new SchemeCompareObjectEQ(m_global)));
    m_global->set_env("cons", SchemeValue_p(new SchemeCommonProduce(produce_cons,m_global,"cons")));
    m_global->set_env("car", SchemeValue_p(new SchemeCommonProduce(produce_car,m_global,"car")));
    m_global->set_env("cdr", SchemeValue_p(new SchemeCommonProduce(produce_cdr,m_global,"cdr")));
    m_global->set_env("quote", SchemeValue_p(new SchemeCommonProduce(produce_quote,m_global,"quote")));
    m_global->set_env("eval", SchemeValue_p(new SchemeCommonProduce(produce_eval,m_global,"eval")));
    m_global->set_env("env", SchemeValue_p(new SchemeCommonProduce(produce_show_env,m_global,"env")));
    m_global->set_env("begin", SchemeValue_p(new SchemeCommonProduce(produce_begin,m_global,"begin")));
    m_global->set_env("display", SchemeValue_p(new SchemeCommonProduce(produce_display,m_global,"display")));
    m_global->set_env("load", SchemeValue_p(new SchemeCommonProduce(produce_load,m_global,"load")));
    m_global->set_env("call/cc", SchemeValue_p(new SchemeCommonProduce(produce_call_with_current_context,m_global,"call/cc")));
    m_global->set_env("set!", SchemeValue_p(new SchemeCommonProduce(produce_set_change,m_global,"set!")));
}

SchemeValue_p SchemeEvaluator::eval(SchemeValue_p expr, Frame_p env, Tracker& tracker)
{
    return ::eval(expr, env, tracker);
}

SchemeValue_p SchemeEvaluator::eval(SchemeValue_p expr)
{
    Tracker tracker;
    return ::eval(expr, m_global, tracker);
}

bool is_raw_func(SchemeValue_p sym)
{
    if(!sym->is_symbol())
        return false;
    std::string name = sym->toType<SchemeSymbol*>()->value();
    auto itor = std::find(raw_func_name_list.begin(), raw_func_name_list.end(), name);
    return !(itor==raw_func_name_list.end());
}

SchemeValue_p eval(SchemeValue_p expr, Frame_p env, Tracker& tracker)
{
    if(expr->is_symbol())
        return env->get(expr->toType<SchemeSymbol*>()->value());
    if(expr->is_boolean())
        return expr;
    if(expr->is_number())
        return expr;
    if(expr->is_string())
        return expr;
    if(expr->is_produce())
        return expr;
    if(expr->is_nil())
        return expr;
    if(expr->is_pair())
    {
        auto& collector = tracker.m_collect_proc;
        auto& check_proc = tracker.m_check_proc;
        std::cout<<"[[[["<<expr->to_string()<<"]]]]"<<std::endl;
        auto first = car(expr);
        auto next = cdr(expr);

        Tracker op_eval_tracker([collector, next](SchemeValue_p param){
            return collector(cons(param, next));
        },check_proc);

        auto sc_op = eval(first, env, op_eval_tracker);

        auto is_raw= is_raw_func(first);
        auto params = next;
        if(!is_raw)
        {
            if(!next->is_list() && !next->is_nil())
                throw std::runtime_error(std::string("param is not list or nil:")+next->to_string());

            Tracker param_tracker([sc_op,collector](SchemeValue_p param){
                return collector(cons(sc_op,param));
            },check_proc);
            params = eval_params(next, env,param_tracker);
        }

        if(sc_op->is_produce())
        {
            if(sc_op->is_continuation())
            {
                if(check_proc(sc_op))
                    throw ContinuationException(car(params), sc_op);
            }

            auto result = sc_op->toType<SchemeProduce*>()->apply(params, env, tracker);
            return result;
        }
    }
    throw std::runtime_error(std::string("unknown expr:")+expr->to_string());
}

SchemeValue_p eval_params(SchemeValue_p params, Frame_p env, Tracker& tracker)
{
    if(params->is_nil())
        return nil();

    auto first = car(params);
    auto rest = cdr(params);

    auto collector = tracker.m_collect_proc;
    auto check_proc = tracker.m_check_proc;

    Tracker eval_tracker([collector, rest](SchemeValue_p param){
        return collector(cons(param, rest));},check_proc);

    auto result_first = eval(first, env, eval_tracker);

    Tracker rest_param_tracker([result_first,collector](SchemeValue_p param){
        return collector(cons(result_first, param));
    },check_proc);
    auto result_rest = eval_params(rest, env, rest_param_tracker);

    return cons(result_first, result_rest);
}
