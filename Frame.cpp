#include "Frame.h"



Frame_p create_global_frame()
{
    return std::make_shared<Frame>();
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

SchemeValue_p Frame::get(std::string k)
{
    if(m_env.find(k) == m_env.end())
        throw std::runtime_error(std::string("can't find value with key ")+k);
    return m_env[k];
}
