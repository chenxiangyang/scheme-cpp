#ifndef _SCHEMEBOOLEAN_H_
#define _SCHEMEBOOLEAN_H_
#include "SchemeValue.h"
class SchemeBoolean: public SchemeValue
{
public:
};

SchemeValue_p sc_true();
SchemeValue_p sc_false();

#endif
