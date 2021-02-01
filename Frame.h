#ifndef _FRAME_H_
#define _FRAME_H_
#include <memory>
#include <map>
#include "SchemeValue.h"
class Frame
{
public:
    Frame();
    void set_env(std::string k, SchemeValue_p value);
private:
    std::map<std::string, SchemeValue_p> m_env;
};

typedef std::shared_ptr<Frame> Frame_p;

Frame_p create_global_frame();
void scheme_define(std::string str, SchemeValue_p value, Frame_p env);

#endif
