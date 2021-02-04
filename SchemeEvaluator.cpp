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
    m_global->set_env("cons", SchemeValue_p(new SchemeCommonProduce(produce_cons,m_global)));
    m_global->set_env("car", SchemeValue_p(new SchemeCommonProduce(produce_car,m_global)));
    m_global->set_env("cdr", SchemeValue_p(new SchemeCommonProduce(produce_cdr,m_global)));
    m_global->set_env("quote", SchemeValue_p(new SchemeCommonProduce(produce_quote,m_global)));
    m_global->set_env("eval", SchemeValue_p(new SchemeCommonProduce(produce_eval,m_global)));
    m_global->set_env("env", SchemeValue_p(new SchemeCommonProduce(produce_show_env,m_global)));
    m_global->set_env("begin", SchemeValue_p(new SchemeCommonProduce(produce_begin,m_global)));
    m_global->set_env("display", SchemeValue_p(new SchemeCommonProduce(produce_display,m_global)));
    m_global->set_env("load", SchemeValue_p(new SchemeCommonProduce(produce_load,m_global)));
    m_global->set_env("call/cc", SchemeValue_p(new SchemeCommonProduce(produce_call_with_current_context,m_global)));
    m_global->set_env("set!", SchemeValue_p(new SchemeCommonProduce(produce_set_change,m_global)));
}

SchemeValue_p SchemeEvaluator::eval(SchemeValue_p expr, Frame_p env)
{
    return ::eval(expr, env);
}

SchemeValue_p SchemeEvaluator::eval(SchemeValue_p expr)
{
    return ::eval(expr, m_global);
}

bool is_raw_func(SchemeValue_p sym)
{
    if(!sym->is_symbol())
        return false;
    std::string name = sym->toType<SchemeSymbol*>()->value();
    auto itor = std::find(raw_func_name_list.begin(), raw_func_name_list.end(), name);
    return !(itor==raw_func_name_list.end());
}

SchemeValue_p eval(SchemeValue_p expr, Frame_p env, Continuation continuation)
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
    if(expr->is_pair())
    {
        auto first = car(expr);
        auto next = cdr(expr);

        auto sc_op = eval(first, env, [continuation, next](SchemeValue_p param){
            return continuation(cons(param, next));
        });

        if(sc_op == env->get("call/cc"))
        {
            auto holder = std::make_shared<SchemeString>("__call/cc__placeholder__");
            auto ret = continuation(holder);
            std::cout<<ret->to_string()<<std::endl;
            auto contin = std::make_shared<SchemeContinuation>(ret, holder, env);

            auto lambda = eval(car(next), env);
            if(!lambda->is_produce())
                std::runtime_error(std::string()+"param of call/cc must be produce,"+lambda->to_string());
            return lambda->toType<SchemeProduce*>()->apply(cons(contin,nil()), env);
        }

        auto is_raw= is_raw_func(first);
        auto params = next;
        if(!is_raw)
        {
            if(!next->is_list() && !next->is_nil())
                throw std::runtime_error(std::string("param is not list or nil:")+next->to_string());

            params = eval_params(next, env,
                                 [sc_op,continuation](SchemeValue_p param){
                    return continuation(cons(sc_op,param));
            });
        }

        if(sc_op->is_produce())
        {
            return sc_op->toType<SchemeProduce*>()->apply(params, env);
        }
    }
    throw std::runtime_error(std::string("unknown expr:")+expr->to_string());
}

SchemeValue_p eval_params(SchemeValue_p params, Frame_p env, Continuation continuation)
{
    if(params->is_nil())
        return nil();

    auto first = car(params);
    auto rest = cdr(params);
    auto result_first = eval(first, env, [continuation, rest](SchemeValue_p param){
        return continuation(cons(param, rest));
    });
    auto result_rest = eval_params(rest, env, [result_first,continuation](SchemeValue_p param){
        return continuation(cons(result_first, param));
    });

    return cons(result_first, result_rest);
}
