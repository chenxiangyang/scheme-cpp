#ifndef _FRAME_H_
#define _FRAME_H_
#include <memory>
#include <map>
#include "SchemeValue.h"
class Frame;
typedef std::shared_ptr<Frame> Frame_p;
class Frame: public std::enable_shared_from_this<Frame>
{
public:
    Frame();
    void set_env(std::string k, SchemeValue_p value);
    void change_env(std::string k, SchemeValue_p value);
    SchemeValue_p get(std::string k);

    Frame_p getptr();
    Frame_p create_child();

    std::string to_string(bool recursive);
private:
    std::map<std::string, SchemeValue_p> m_env;
    Frame_p m_parent;
};

Frame_p create_frame();
void scheme_define(std::string str, SchemeValue_p value, Frame_p env);

#endif
