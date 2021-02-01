#include "SchemeEvaluator.h"
#include "SchemeProduce.h"


Evaluator::Evaluator()
{
    m_global = create_global_frame();
    m_global->set_env("define", SchemeValue_p(new SchemeDefine()));
}
