#ifndef _SCHEMEBOOLEAN_H_
#define _SCHEMEBOOLEAN_H_
#include "SchemeValue.h"
class SchemeBoolean: public SchemeValue
{
    SchemeBoolean(bool v):m_value(v){}
public:
    std::string to_string() override
    {
        if(m_value)
            return "#t";
        return "#f";
    }
    bool is_boolean() override
    {
        return true;
    }

    static SchemeValue* sc_true();
    static SchemeValue* sc_false();
private:
    bool m_value;

};

SchemeValue_p sc_true();
SchemeValue_p sc_false();
SchemeValue_p sc_boolean(bool v);

#endif
