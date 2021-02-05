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
    auto new_next = m_next->is_pair()? m_next->toType<SchemePair*>()->clone_only_pair():m_next;
    auto new_value = m_value->is_pair()? m_value->toType<SchemePair*>()->clone_only_pair():m_value;

    return cons(new_value, new_next);
}

bool SchemePair::replace_with(SchemeValue_p src, SchemeValue_p tgt)
{
    if(m_value==src)
    {
        m_value = tgt;
        return true;
    }
    if(m_next==src)
    {
        m_next=tgt;
        return true;
    }

    bool ret = false;
    if(m_value->is_pair())
        ret = ret || m_value->toType<SchemePair*>()->replace_with(src, tgt);

    if(m_next->is_pair())
        ret = ret || m_next->toType<SchemePair*>()->replace_with(src, tgt);

    return ret;
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
