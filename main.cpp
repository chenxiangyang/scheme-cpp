#include <iostream>
#include "SchemeReader.h"
#include "SchemeTokens.h"
#include "SchemeEvaluator.h"
#include <fstream>
#include "produces/SchemeCommProduce.h"
#include "SchemeNumber.h"
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

void test_lambda4()
{
    std::cout<<"test_lambda4"<<std::endl;
    auto reader = std::make_shared<SchemeReader>([](){
        static char test_exp[]=
                "(define a(cons 1 2))"
                "(car a)";
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

void test_quote()
{
    std::cout<<"test_lambda4"<<std::endl;
    auto reader = std::make_shared<SchemeReader>([](){
        static char test_exp[]=
                "(define a(cons 1 2))"
                "(define b (quote a))"
                "(quote (+ 1 1))";
                //"(eval (quote (+ 1 1)))";
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


void test_show_env()
{
    std::cout<<"test_show-env"<<std::endl;
    auto reader = std::make_shared<SchemeReader>([](){
        static char test_exp[]=
                "(define (func x y)"
                " (begin"
                "  (define z 10)"
                "  (define u 20)"
                "  (env)"
                "  (lambda () (+ x y z u))))"
                "(func 10 20)";
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

void read_exec_loop(std::function<char()> f)
{
    std::cout<<"scheme"<<std::endl;
    auto reader = std::make_shared<SchemeReader>(f);

    auto token = std::make_shared<SchemeTokens>(reader);
    SchemeEvaluator e;

    while(1)
    {
        try{
            std::cout<<"scm>";
            auto first = get_line(token);
            //std::cout<<first->to_string()<<std::endl;
            auto result = e.eval(first);
            std::cout<<result->to_string()<<std::endl;
        }
        catch(std::exception& e)
        {
            std::cout<<e.what()<<std::endl;
        }
    }
}

int load(std::string file, SchemeEvaluator* e)
{
    Tracker tracker;
    auto ret = load(file, e->m_global);
    if(ret->is_number())
    {
        auto ret_integer = ret->toType<SchemeInteger*>();
        if(ret_integer)
            return ret_integer->m_value;
    }
    return 0;
}

int main(int argc, char* argv[])
{
    //test_reader();
    //test_token();
    //test_eval();
    //test_eval_def();
    //test_lambda();
    //test_lambda2();
    //test_lambda3();
    //test_lambda4();
    //test_quote();
    //test_show_env();

    if(argc==1)
        read_exec_loop(std::getchar);
    else
    {
        SchemeEvaluator e;
        return load(argv[1], &e);
    }

    return 0;
}
