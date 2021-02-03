#include "SchemeBoolean.h"

SchemeValue_p sc_true()
{
    static auto b = SchemeValue_p(SchemeBoolean::sc_true());
    return b;
}

SchemeValue_p sc_false()
{
    static auto b = SchemeValue_p(SchemeBoolean::sc_false());
    return b;
}



SchemeValue* SchemeBoolean::sc_true()
{
    return new SchemeBoolean(true);
}

SchemeValue *SchemeBoolean::sc_false()
{
    return new SchemeBoolean(false);
}

SchemeValue_p sc_boolean(bool v)
{
    if(v)
        return sc_true();
    return sc_false();
}
