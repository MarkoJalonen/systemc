#include <systemc.h>
#include <iostream>

// simple helloworld program to test enviroment
// further explanation in the similar "explicitctr" files

SC_MODULE(HelloWorld)
{
    SC_CTOR(HelloWorld)
    {
        //empty constructor
    }
    void print_hello(void)
    {
        std::cout << "Hello World!\n";
    }
};

int sc_main(int argc, char** argv)
{
    HelloWorld hello("hello");
    hello.print_hello();
    return 0;
}



