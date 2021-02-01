#ifndef _SCHEMESTRING_H_
#define _SCHEMESTRING_H_
#include "SchemeValue.h"
class SchemeString: public SchemeValue
{
public:
    SchemeString(std::string str);

    std::string to_string() override
    {
        return m_value;
    }
private:
    std::string m_value;
};

#endif
