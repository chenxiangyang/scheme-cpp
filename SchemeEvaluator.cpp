#include "SchemeEvaluator.h"
#include "SchemeProduce.h"
#include "SchemeSymbol.h"
#include "SchemePair.h"
#include "produces/SchemeAdd.h"

SchemeEvaluator::SchemeEvaluator()
{
    m_global = create_global_frame();
    m_global->set_env("define", SchemeValue_p(new SchemeDefine(m_global)));
    m_global->set_env("+", SchemeValue_p(new SchemeAdd(m_global)));
    m_global->set_env("-", SchemeValue_p(new SchemeSub(m_global)));
}

SchemeValue_p SchemeEvaluator::eval(SchemeValue_p expr, Frame_p env)
{
    return ::eval(expr, env);
}

SchemeValue_p SchemeEvaluator::eval(SchemeValue_p expr)
{
    return ::eval(expr, m_global);
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
        if(sc_op->is_produce())
        {
            return sc_op->toType<SchemeProduce*>()->apply(next);
        }
    }
}
