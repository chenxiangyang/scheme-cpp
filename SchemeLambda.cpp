#include "SchemeLambda.h"
#include "SchemePair.h"
#include "SchemeSymbol.h"
#include "SchemeEvaluator.h"
SchemeValue_p SchemeLambda::apply(SchemeValue_p params, Frame_p env)
{
    if(!params->is_pair())
        throw std::runtime_error("lambda param is not list.");

    auto func = std::make_shared<SchemeLambdaExpr>(env);
    func->m_body = car(cdr(params));
    func->m_formal_parameters = car(params);
    return func;
}

SchemeValue_p SchemeLambdaExpr::apply(SchemeValue_p params, Frame_p env)
{
    auto param_env = m_env->create_child();
    auto formal_params = m_formal_parameters;

    if(!params->is_list())
        throw std::runtime_error(std::string("params is not list"));

    while(1)
    {
        if(formal_params->is_nil() && params->is_nil())
            break;
        if(formal_params->is_nil() || params->is_nil())
            throw std::runtime_error(std::string("function param count is not correct."));

        auto param_name = car(formal_params);
        auto param_value = car(params);

        if(!param_name->is_symbol())
            throw std::runtime_error(std::string("formal param type invalid:")+param_name->to_string());

        param_env->set_env(param_name->toType<SchemeSymbol*>()->value(), param_value);

        formal_params = cdr(formal_params);
        params = cdr(params);
    }

    return eval(m_body, param_env);
}
