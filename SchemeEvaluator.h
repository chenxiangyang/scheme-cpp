#ifndef _SCHEME_EVALUATOR_H_
#define _SCHEME_EVALUATOR_H_
#include "SchemeValue.h"
#include "Frame.h"
class Evaluator
{
public:
    Evaluator();
    SchemeValue_p eval(SchemeValue_p expr, Frame_p env);

    Frame_p m_global;
};

#endif
