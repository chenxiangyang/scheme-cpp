#include "SchemeTokens.h"
#include "SchemeValue.h"
#include "SchemePair.h"
#include <regex>
#include <iostream>
#include "SchemeBoolean.h"
#include "SchemeString.h"
#include "SchemeNumber.h"
#include "SchemeSymbol.h"
bool is_number(std::string v)
{
    std::regex r("^[0-9]+.{0,1}[0-9]{0,2}$");
    return std::regex_match(v, r);
}

bool is_boolean(std::string v)
{
    return (v == "#f" || v == "#t");
}

bool is_string(std::string v)
{
    return (v[0]=='\"' && v[v.size()-1]=='\"');
}

SchemeValue_p get_value_from_string(std::string str)
{
    if(is_boolean(str))
    {
        if(str == "#f")
            return sc_false();
        if(str == "#t")
            return sc_true();
    }
    else if(is_number(str))
    {
        float v = std::atof(str.c_str());
        return std::make_shared<SchemeFloat>(v);
    }
    else if(is_string(str))
    {
        std::string s = str.substr(1,str.size()-2);
        return std::make_shared<SchemeString>(s);
    }
    return std::make_shared<SchemeSymbol>(str);
}

SchemeValue_p get_item(SchemeTokens_p t)
{
    std::string token = t->get_token();

    //std::cout<<"token:"<<token<<std::endl;

    if(token.empty())
    {
        //throw std::runtime_error("token empty.");
        return nil();
    }

    if(token=="(")
    {
        SchemeValue_p ret = get_item(t);
        std::string tail = t->get_token();
        //std::cout<<"tail:"<<tail<<std::endl;
        if(tail == ")")
            return cons(ret, get_item(t));
        else
        {
            //std::cout<<ret->to_string()<<std::endl;
            throw std::runtime_error(std::string("invalid tail:")+tail);
        }
    }

    if(token==")")
    {
        t->revert(token);
        return nil();
    }

    //return get_value_from_string(token);
    return cons(get_value_from_string(token), get_item(t));
}

SchemeValue_p get_line(SchemeTokens_p t)
{
    std::string token = t->get_token();
    if(token == "(")
    {
        auto result = get_item(t);
        std::string tail = t->get_token();
        if(tail==")")
            return result;
        else
            throw std::runtime_error("");
    }
    return get_value_from_string(token);
}

SchemeTokens::SchemeTokens(SchemeReader_p reader)
{
    m_reader = reader;
}

std::string SchemeTokens::get_token()
{
    if(m_stack.size())
    {
        auto result = m_stack.front();
        m_stack.pop_front();
        return result;
    }
    return m_reader->get_next();
}

void SchemeTokens::revert(std::string s)
{
    m_stack.push_front(s);
}
