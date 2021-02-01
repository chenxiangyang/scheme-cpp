#ifndef _SCHEMETOKENS_H_
#define _SCHEMETOKENS_H_
#include "SchemeReader.h"
#include "SchemeValue.h"
#include <list>
class SchemeTokens
{
public:
    SchemeTokens(SchemeReader_p reader);
    std::string get_token();
    void revert(std::string s);
private:
    std::list<std::string> m_stack;
    SchemeReader_p m_reader;
};

typedef std::shared_ptr<SchemeTokens> SchemeTokens_p;
SchemeValue_p get_line(SchemeTokens_p t);

#endif
