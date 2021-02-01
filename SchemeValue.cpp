#include "SchemeValue.h"

SchemeValue_p nil()
{
    static SchemeValue_p value = std::make_shared<SchemeNil>();
    return value;
}
