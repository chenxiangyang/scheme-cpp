#ifndef _SCHEME_EVALUATOR_H_
#define _SCHEME_EVALUATOR_H_
#include "SchemeValue.h"
#include "Frame.h"
class SchemeEvaluator
{
public:
    SchemeEvaluator();
    SchemeValue_p eval(SchemeValue_p expr, Frame_p env);
    SchemeValue_p eval(SchemeValue_p expr);

    Frame_p m_global;
};

SchemeValue_p eval(SchemeValue_p expr, Frame_p env);

#endif
