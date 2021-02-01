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

SchemeValue_p cons(SchemeValue_p first, SchemeValue_p second)
{
    return std::make_shared<SchemePair>(first, second);
}
