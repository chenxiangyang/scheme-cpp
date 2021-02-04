#include "Frame.h"

Frame_p create_frame()
{
    return std::make_shared<Frame>();
    //return (new Frame)->getptr();
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

void Frame::change_env(std::string k, SchemeValue_p value)
{
    if(m_env.find(k) == m_env.end())
    {
        if(this->m_parent)
        {
            this->m_parent->change_env(k, value);
            return;
        }
        throw std::runtime_error(std::string("can't set! value with key ")+k);
    }
    m_env[k] = value;
}

SchemeValue_p Frame::get(std::string k)
{
    if(m_env.find(k) == m_env.end())
    {
        if(this->m_parent)
        {
            auto ret = this->m_parent->get(k);
            if(ret.get()==NULL)
                throw std::runtime_error(std::string("can't find value with key ")+k);
            return ret;
        }
        throw std::runtime_error(std::string("can't find value with key ")+k);
    }
    return m_env[k];
}

Frame_p Frame::getptr()
{
    return shared_from_this();
}

Frame_p Frame::create_child()
{
    auto child = std::make_shared<Frame>();
    child->m_parent = this->getptr();
    return child;
}

std::string Frame::to_string(bool recursive)
{
    std::string result="{";
    for(auto itor:m_env)
    {
        result+="[";
        result+=itor.first;
        result+="]";
    }
    result+="}";
    if(m_parent)
        result += m_parent->to_string(recursive);
    return result;
}
