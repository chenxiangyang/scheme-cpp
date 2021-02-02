#include <iostream>
#include "SchemeReader.h"
#include "SchemeTokens.h"
#include "SchemeEvaluator.h"
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

void test_eval()
{
    auto reader = std::make_shared<SchemeReader>([](){
        static char test_exp[]="(+ 11 (- 12 13) 12 (+ 12 12))";
        static int index = 0;
        return test_exp[index++];
    });

    auto token = std::make_shared<SchemeTokens>(reader);

    auto tree = get_line(token);
    std::cout<<tree->to_string()<<std::endl;

    SchemeEvaluator e;
    auto result = e.eval(tree);
    std::cout<<result->to_string()<<std::endl;
}

void test_eval_def()
{
    auto reader = std::make_shared<SchemeReader>([](){
        static char test_exp[]=
                "(define aa 3)"
                "(+ 11 (- 12 13) 12 (+ aa 12) aa)";
        static int index = 0;
        return test_exp[index++];
    });

    auto token = std::make_shared<SchemeTokens>(reader);
    SchemeEvaluator e;

    auto first = get_line(token);
    auto result = e.eval(first);
    std::cout<<result->to_string()<<std::endl;

    auto second = get_line(token);
    result = e.eval(second);
    std::cout<<result->to_string()<<std::endl;
}

void test_lambda()
{
    auto reader = std::make_shared<SchemeReader>([](){
        static char test_exp[]=
                "(define func (lambda (x) (+ x x x)))"
                "(+ 11 (func 10))";
        static int index = 0;
        return test_exp[index++];
    });

    auto token = std::make_shared<SchemeTokens>(reader);
    SchemeEvaluator e;

    auto first = get_line(token);
    auto result = e.eval(first);
    std::cout<<result->to_string()<<std::endl;

    auto second = get_line(token);
    result = e.eval(second);
    std::cout<<result->to_string()<<std::endl;
}

void test_lambda2()
{
    std::cout<<"test_lambda2"<<std::endl;
    auto reader = std::make_shared<SchemeReader>([](){
        static char test_exp[]=
                "(define (func x) (+ x x x))"
                "(+ 11 (func 10))";
        static int index = 0;
        return test_exp[index++];
    });

    auto token = std::make_shared<SchemeTokens>(reader);
    SchemeEvaluator e;

    auto first = get_line(token);
    auto result = e.eval(first);

    auto second = get_line(token);
    result = e.eval(second);
    std::cout<<result->to_string()<<std::endl;
}

void test_lambda3()
{
    std::cout<<"test_lambda3"<<std::endl;
    auto reader = std::make_shared<SchemeReader>([](){
        static char test_exp[]=
                "(define (func x) (lambda (y) (+ x y)))"
                "(define f10 (func 10))"
                "(f10 30)";
        static int index = 0;
        return test_exp[index++];
    });

    auto token = std::make_shared<SchemeTokens>(reader);
    SchemeEvaluator e;

    auto first = get_line(token);
    auto result = e.eval(first);

    auto second = get_line(token);
    result = e.eval(second);
    std::cout<<result->to_string()<<std::endl;

    auto third = get_line(token);
    result = e.eval(third);
    std::cout<<result->to_string()<<std::endl;
}

int main(int argc, char* argv[])
{
    test_reader();
    test_token();
    test_eval();
    test_eval_def();
    test_lambda();
    test_lambda2();
    test_lambda3();
    std::cout<<"scheme start"<<std::endl;
    return 0;
}
