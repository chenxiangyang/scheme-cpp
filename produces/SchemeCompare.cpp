#include "SchemeCompare.h"
#include "../SchemePair.h"
#include "../SchemeNumber.h"
#include "../SchemeBoolean.h"

SchemeValue_p compare_gt(SchemeValue_p first, SchemeValue_p second)
{
    if(!first->is_number() || !second->is_number())
        throw std::runtime_error(std::string("invalid param:")+first->to_string()+" "+second->to_string());

    if(first->toType<SchemeFloat*>())
    {
        float value = first->toType<SchemeFloat*>()->m_value;
        if(second->toType<SchemeFloat*>())
            return sc_boolean(value > second->toType<SchemeFloat*>()->m_value);
        else if(second->toType<SchemeInteger*>())
            return sc_boolean(value > second->toType<SchemeInteger*>()->m_value);
    }
    else if(first->toType<SchemeInteger*>())
    {
        int value = first->toType<SchemeInteger*>()->m_value;
        if(second->toType<SchemeFloat*>())
            return sc_boolean(value > second->toType<SchemeFloat*>()->m_value);
        else if(second->toType<SchemeInteger*>())
            return sc_boolean(value > second->toType<SchemeInteger*>()->m_value);
    }
    throw std::runtime_error(std::string("invalid param type:")+first->to_string()+" "+second->to_string());
}

SchemeValue_p compare_number_eq(SchemeValue_p first, SchemeValue_p second)
{
    if(!first->is_number() || !second->is_number())
        throw std::runtime_error(std::string("invalid param:")+first->to_string()+" "+second->to_string());

    if(first->toType<SchemeFloat*>())
    {
        float value = first->toType<SchemeFloat*>()->m_value;
        if(second->toType<SchemeFloat*>())
            return sc_boolean(value == second->toType<SchemeFloat*>()->m_value);
        else if(second->toType<SchemeInteger*>())
            return sc_boolean(value == second->toType<SchemeInteger*>()->m_value);
    }
    else if(first->toType<SchemeInteger*>())
    {
        int value = first->toType<SchemeInteger*>()->m_value;
        if(second->toType<SchemeFloat*>())
            return sc_boolean(value == second->toType<SchemeFloat*>()->m_value);
        else if(second->toType<SchemeInteger*>())
            return sc_boolean(value == second->toType<SchemeInteger*>()->m_value);
    }
    throw std::runtime_error(std::string("invalid param type:")+first->to_string()+" "+second->to_string());
}


SchemeValue_p SchemeCompareGT::apply(SchemeValue_p params, Frame_p env, Tracker &tracker)
{
    if(!params->is_list())
        throw std::runtime_error(std::string("invalid param:")+params->to_string());

    auto first = car(params);
    auto second = car(cdr(params));

    return compare_gt(first, second);
}

SchemeValue_p SchemeCompareLT::apply(SchemeValue_p params, Frame_p env, Tracker &tracker)
{
    if(!params->is_list())
        throw std::runtime_error(std::string("invalid param:")+params->to_string());

    auto first = car(params);
    auto second = car(cdr(params));

    return compare_gt(second, first);
}

SchemeValue_p SchemeCompareEQ::apply(SchemeValue_p params, Frame_p env, Tracker &tracker)
{
    if(!params->is_list())
        throw std::runtime_error(std::string("invalid param:")+params->to_string());

    auto first = car(params);
    auto second = car(cdr(params));

    return compare_number_eq(first, second);
}



SchemeValue_p SchemeCompareObjectEQ::apply(SchemeValue_p params, Frame_p env, Tracker &tracker)
{
    if(!params->is_list())
        throw std::runtime_error(std::string("invalid param:")+params->to_string());

    auto first = car(params);
    auto second = car(cdr(params));

    return sc_boolean(first.get() == second.get());
}
