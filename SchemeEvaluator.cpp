#include <vector>
#include <algorithm>
#include "SchemeEvaluator.h"
#include "SchemeProduce.h"
#include "SchemeSymbol.h"
#include "SchemePair.h"
#include "SchemeLambda.h"
#include "produces/SchemeAdd.h"
#include "produces/SchemeIf.h"
#include "produces/SchemeCompare.h"
#include "produces/SchemeCommProduce.h"

std::vector<std::string> raw_func_name_list = {
    "define","lambda","if","quote"
};

SchemeEvaluator::SchemeEvaluator()
{
    m_global = create_frame();

    m_global->set_env("define", SchemeValue_p(new SchemeDefine(m_global)));
    m_global->set_env("lambda", SchemeValue_p(new SchemeLambda(m_global)));
    m_global->set_env("if", SchemeValue_p(new SchemeIf(m_global)));
    m_global->set_env("+", SchemeValue_p(new SchemeAdd(m_global)));
    m_global->set_env("-", SchemeValue_p(new SchemeSub(m_global)));
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

SchemeValue_p eval(SchemeValue_p expr, Frame_p env)
{
    if(expr->is_symbol())
        return env->get(expr->toType<SchemeSymbol*>()->value());
    if(expr->is_boolean())
        return expr;
    if(expr->is_number())
        return expr;
    if(expr->is_pair())
    {
        auto first = car(expr);
        auto next = cdr(expr);

        auto sc_op = eval(first, env);

        auto is_raw= is_raw_func(first);
        auto params = next;
        if(!is_raw)
        {
            if(!next->is_list() && !next->is_nil())
                throw std::runtime_error(std::string("param is not list or nil:")+next->to_string());

            params = eval_params(next, env);
        }

        if(sc_op->is_produce())
        {
            return sc_op->toType<SchemeProduce*>()->apply(params, env);
        }
    }
    throw std::runtime_error(std::string("unknown expr:")+expr->to_string());
}

SchemeValue_p eval_params(SchemeValue_p params, Frame_p env)
{
    if(params->is_nil())
        return nil();

    auto first = car(params);
    auto rest = cdr(params);
    auto result_first = eval(first, env);
    auto result_rest = eval_params(rest, env);

    return cons(result_first, result_rest);
}
