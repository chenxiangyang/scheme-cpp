#include <iostream>
#include "SchemeContinuation.h"
#include "SchemePair.h"
#include "SchemeEvaluator.h"
std::string SchemeContinuation::to_string()
{
    return SchemeProduce::to_string()+
            "continuation:"+
            m_env->to_string(true)+
            m_proc->to_string();
}

SchemeValue_p SchemeContinuation::apply(SchemeValue_p params, Frame_p env)
{
    if(!params->is_list() || params->toType<SchemePair*>()->count()!=1)
        throw std::runtime_error(std::string() + "invalid continuation param:" + params->to_string());

    auto new_pair_list = m_proc->toType<SchemePair*>()->clone_only_pair();

    //std::cout<<"a:"<<new_pair_list->to_string()<<std::endl;
    new_pair_list->toType<SchemePair*>()->replace_with(m_holder_place, car(params));

    auto ret = eval(new_pair_list, env, default_cont/*, check_proc*/);
    return ret;
}
