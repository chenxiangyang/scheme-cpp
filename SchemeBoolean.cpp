#include "SchemeBoolean.h"

SchemeValue_p sc_true()
{
    static SchemeValue_p t = std::make_shared<SchemeBoolean>();
    return t;
}

SchemeValue_p sc_false()
{
    static SchemeValue_p t = std::make_shared<SchemeBoolean>();
    return t;
}
