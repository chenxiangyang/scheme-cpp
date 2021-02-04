#ifndef _SCHEME_READER_H_
#define _SCHEME_READER_H_

#include <string>
#include <functional>
#include <vector>
#include <list>
#include <memory>
class SchemeReader
{
public:
    SchemeReader(std::function<char()> char_reader);
    SchemeReader();
    std::string get_next();
private:

    void parse();
    std::list<std::string> m_cached;

    std::list<char> m_char_stack;
    void revert_char(char c);
    char get_char();
    std::string get_symbol();
    std::string get_string();

    std::function<char()> m_get_char_func;
    bool m_finished;
};

typedef std::shared_ptr<SchemeReader> SchemeReader_p;

#endif
