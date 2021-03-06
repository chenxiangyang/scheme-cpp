#ifndef _SCHEMESTRING_H_
#define _SCHEMESTRING_H_
#include "SchemeValue.h"
class SchemeString: public SchemeValue
{
public:
    SchemeString(std::string str);

    std::string to_string() override
    {
        return std::string("\"")+m_value+"\"";
    }
    std::string value()
    {
        return m_value;
    }

    bool is_string() override{return true;}
private:
    std::string m_value;
};

#endif
