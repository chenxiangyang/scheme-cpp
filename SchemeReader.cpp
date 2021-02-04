#include "SchemeReader.h"
#include <iostream>
SchemeReader::SchemeReader(std::function<char ()> char_reader)
{
    m_get_char_func = char_reader;
    m_finished = false;
}

SchemeReader::SchemeReader()
{
    m_get_char_func = std::getchar;
}

//a-zA-Z0-9.*!#$%^&*<>/+-_?'
std::string SchemeReader::get_next()
{
    while(1)
    {
        if(m_cached.size())
        {
            std::string ret = m_cached.front();
            m_cached.pop_front();
            return ret;
        }
        parse();
        if(m_cached.size()==0)
            return "";
    }
    return "";
}

std::string char_to_string(char c)
{
    char buf[2]={0};
    buf[0] = c;
    return std::string(buf);
}

void SchemeReader::parse()
{
    while(1)
    {
        char c = get_char();
        if(c == '(' || c==')')
        {
            m_cached.push_back(char_to_string(c));
            break;
        }
        if(c == ' ' || c==0x0a)
        {
            continue;
        }
        if(c == 0)
        {
            m_finished = true;
            break;
        }
        if(c == '\"')
        {
            m_cached.push_back(get_string());
            break;
        }

        revert_char(c);
        auto t = get_symbol();
        //std::cout<<t<<std::endl;
        m_cached.push_back(t);
        break;
    }
}

void SchemeReader::revert_char(char c)
{
    m_char_stack.push_front(c);
}

char SchemeReader::get_char()
{
    if(m_char_stack.size())
    {
        char f = m_char_stack.front();
        m_char_stack.pop_front();
        return f;
    }

    return m_get_char_func();
}

std::string SchemeReader::get_symbol()
{
    std::vector<char> tmp;
    while(1)
    {
        char c = get_char();
        if(c=='(' || c==')' ){
            revert_char(c);
            break;
        }
        if(c==' ' || c==0x0a)
            break;

        if(c == 0)
        {
            m_finished = true;
            break;
        }

        tmp.push_back(c);
    }
    tmp.push_back(0);
    return std::string(tmp.data());
}

std::string SchemeReader::get_string()
{
    std::vector<char> tmp;
    tmp.push_back('\"');
    while(1)
    {
        char c = get_char();
        if(c == '\"')
            break;
        if(c == 0)
        {
            m_finished = true;
            throw std::runtime_error("string not finished.");
        }
        tmp.push_back(c);
    }
    tmp.push_back('\"');
    tmp.push_back(0);
    //std::cout<<"get_string :"<<tmp.data()<<std::endl;;
    return std::string(tmp.data());
}
