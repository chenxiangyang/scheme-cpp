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

SchemeValue_p SchemePair::clone_only_pair()
{
    if(m_next->is_nil())
    {
        return cons(m_value, nil());
    }
    return cons(m_value, m_next->toType<SchemePair*>()->clone_only_pair());
}

void SchemePair::replace_with(SchemeValue_p src, SchemeValue_p tgt)
{
    if(m_value == src)
        m_value = tgt;
    else if(!m_next->is_nil())
        m_next->toType<SchemePair*>()->replace_with(src, tgt);
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
