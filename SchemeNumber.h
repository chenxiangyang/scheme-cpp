#ifndef _SCHEMENUMBER_H_
#define _SCHEMENUMBER_H_
#include "SchemeValue.h"
class SchemeNumber: public SchemeValue
{
public:
    bool is_number() override{return true;}
};

class SchemeFloat: public SchemeNumber
{
public:
    SchemeFloat(float f):m_value(f){}

    std::string to_string() override
    {
        char buff[100]={0};
        std::sprintf(buff,"%f",m_value);
        return std::string(buff);
    }
public:
    float m_value;
};

class SchemeInteger: public SchemeNumber
{
public:
    SchemeInteger(int i):m_value(i){}

    std::string to_string() override
    {
        char buff[100]={0};
        std::sprintf(buff,"%d",m_value);
        return std::string(buff);
    }
public:
    int m_value;
};

inline SchemeValue_p scint(int value)
{
    return std::make_shared<SchemeInteger>(value);
}

inline SchemeValue_p scfloat(float value)
{
    return std::make_shared<SchemeFloat>(value);
}

#endif
