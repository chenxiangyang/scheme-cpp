#include "Frame.h"



Frame_p create_global_frame()
{

}

void scheme_define(std::string str, SchemeValue_p value, Frame_p env)
{
    env->set_env(str, value);
}

Frame::Frame()
{

}

void Frame::set_env(std::string k, SchemeValue_p value)
{
    m_env[k] = value;
}
