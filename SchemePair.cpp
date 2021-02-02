#include "SchemePair.h"

SchemePair::SchemePair(SchemeValue_p value, SchemeValue_p next)
{
    m_value = value;
    m_next = next;
}

SchemeValue_p SchemePair::car()
{
    return m_value;
}

SchemeValue_p SchemePair::cdr()
{
    return m_next;
}

size_t SchemePair::count()
{
    if(m_next->is_nil())
        return 1;
    else
    {
        if(m_next->is_pair())
            return m_next->toType<SchemePair*>()->count()+1;
        throw std::runtime_error("count: target obj is not list.");
    }
}

bool SchemePair::is_list()
{
    if(m_next->is_nil())
        return true;
    if(m_next->is_pair())
        return m_next->is_list();
    return false;
}

SchemeValue_p cons(SchemeValue_p first, SchemeValue_p second)
{
    return std::make_shared<SchemePair>(first, second);
}
