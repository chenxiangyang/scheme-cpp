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
private:
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
private:
    int m_value;
};

#endif
