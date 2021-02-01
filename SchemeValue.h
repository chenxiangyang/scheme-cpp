
#ifndef _SCHEME_VALUE_H_
#define _SCHEME_VALUE_H_
#include <memory>

class SchemeValue
{
public:
    virtual ~SchemeValue(){}

    virtual bool is_pair(){return false;}
    virtual bool is_symbol(){return false;}
    virtual bool is_number(){return false;}
    virtual bool is_boolean(){return false;}
    virtual bool is_produce(){return false;}
    virtual bool is_nil(){return false;}

    virtual std::string to_string() = 0;
};

class SchemeNil: public SchemeValue
{
public:
    bool is_nil() override
    {
        return true;
    }

    std::string to_string() override
    {
        return "nil";
    }
};

typedef std::shared_ptr<SchemeValue> SchemeValue_p;
SchemeValue_p nil();

#endif
