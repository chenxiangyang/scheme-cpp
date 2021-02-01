#include <iostream>
#include "SchemeReader.h"
#include "SchemeTokens.h"
void test_reader()
{
    SchemeReader reader([](){
        static char test_exp[]="(+ 11 12.12 13 aa)";
        static int index = 0;
        return test_exp[index++];
    });

    while(1)
    {
        std::string str = reader.get_next();
        std::cout<<str<<std::endl;
        if(str.empty())
            break;
    }
}

void test_token()
{

    auto reader = std::make_shared<SchemeReader>([](){
        static char test_exp[]="(+ 11 (- 12.12 13) aa)";
        static int index = 0;
        return test_exp[index++];
    });

    auto token = std::make_shared<SchemeTokens>(reader);

    auto tree = get_line(token);
    std::cout<<tree->to_string()<<std::endl;
}


int main(int argc, char* argv[])
{
    test_reader();
    test_token();
    std::cout<<"scheme start"<<std::endl;
    return 0;
}