#include "SchemeSymbol.h"

SchemeSymbol::SchemeSymbol(std::string symbol)
{
    m_symbol=symbol;
}

SchemeValue_p symbol(std::string str)
{
    return std::make_shared<SchemeSymbol>(str);
}
