#ifndef _SCHEME_EVALUATOR_H_
#define _SCHEME_EVALUATOR_H_
#include "SchemeValue.h"
#include "Frame.h"
#include "SchemeProduce.h"
#include <functional>
#include <tuple>
class SchemeEvaluator
{
public:
    SchemeEvaluator();
    SchemeValue_p eval(SchemeValue_p expr, Frame_p env);
    SchemeValue_p eval(SchemeValue_p expr);

    Frame_p m_global;
};

SchemeValue_p eval(SchemeValue_p expr, Frame_p env, Continuation continuation=default_cont);
SchemeValue_p eval_params(SchemeValue_p params, Frame_p env, Continuation continuation=default_cont);
SchemeValue_p apply(SchemeValue_p op, SchemeValue_p param, Frame_p env);

#endif
