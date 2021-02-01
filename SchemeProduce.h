#ifndef _SCHEMEPRODUCE_H_
#define _SCHEMEPRODUCE_H_
#include "SchemeValue.h"
#include "Frame.h"
class SchemeProduce: public SchemeValue
{
public:
    bool is_produce(){return true;}
    virtual SchemeValue_p apply(SchemeValue_p params, Frame_p env) = 0;
};

#endif
