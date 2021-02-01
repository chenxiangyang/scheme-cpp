#ifndef _SCHEMESYMBOL_H_
#define _SCHEMESYMBOL_H_
#include <string>
#include "SchemeValue.h"
class SchemeSymbol: public SchemeValue
{
public:
    SchemeSymbol(std::string symbol);
    bool is_symbol(){return true;}

    std::string to_string() override
    {
        return m_symbol;
    }

private:
    std::string m_symbol;
};

#endif
