#include "SchemeReader.h"

SchemeReader::SchemeReader(std::function<char ()> char_reader)
{
    m_get_char_func = char_reader;
    parse();
}

SchemeReader::SchemeReader()
{
    m_get_char_func = std::getchar;
    parse();
}

//a-zA-Z0-9.*!#$%^&*<>/+-_?'
std::string SchemeReader::get_next()
{
    if(m_cached.size())
    {
        std::string ret = m_cached.front();
        m_cached.pop_front();
        return ret;
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
            continue;
        }
        if(c == ' ')
        {
            continue;
        }
        if(c == 0)
            break;
        if(c == '\"')
            m_cached.push_back(get_string());

        revert_char(c);
        m_cached.push_back(get_symbol());
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
        if(c==' ')
            break;

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
        tmp.push_back(c);
    }
    tmp.push_back('\"');
    tmp.push_back(0);
    return std::string(tmp.data());
}
