#ifndef _SCHEMEPAIR_H_
#define _SCHEMEPAIR_H_
#include <memory>
#include "SchemeValue.h"

class SchemePair;

class SchemePair: public SchemeValue
{
public:
    SchemePair(SchemeValue_p value, SchemeValue_p next);

    SchemeValue_p car();
    SchemeValue_p cdr();
    bool is_pair() override{return true;}

    SchemeValue_p clone_only_pair();
    void replace_with(SchemeValue_p src, SchemeValue_p tgt);

    std::string to_string() override
    {
        if(m_value->is_pair())
        {
            if(m_next->is_nil())
                return std::string("(") + m_value->to_string() + ")";
            else if(m_next->is_pair())
                return std::string("(") + m_value->to_string() + ")" + m_next->to_string();
            else
                return std::string("(") + m_value->to_string() + ") . " + m_next->to_string();
        }
        if(m_next->is_nil())
            return m_value->to_string();
        else if(m_next->is_pair())
            return m_value->to_string() + " " + m_next->to_string();
        else
            return m_value->to_string() + " . " + m_next->to_string();
    }

    size_t count();
    bool is_list() override;

private:
    SchemeValue_p m_next;
    SchemeValue_p m_value;
};

inline SchemeValue_p car(SchemeValue_p p)
{
    return p->toType<SchemePair*>()->car();
}

inline SchemeValue_p cdr(SchemeValue_p p)
{
    return p->toType<SchemePair*>()->cdr();
}

SchemeValue_p cons(SchemeValue_p first, SchemeValue_p second);

#endif
