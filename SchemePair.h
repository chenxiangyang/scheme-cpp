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


    std::string to_string() override
    {
        if(m_value->is_pair())
        {
            return std::string("(") + m_value->to_string() + ") " + m_next->to_string();
        }
        return m_value->to_string() + " " + m_next->to_string();
    }

private:
    SchemeValue_p m_next;
    SchemeValue_p m_value;
};

SchemeValue_p cons(SchemeValue_p first, SchemeValue_p second);

#endif
