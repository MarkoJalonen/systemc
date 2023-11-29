#include <systemc.h>
#include <stdio.h>

// simple helloworld program to test enviroment
// further explanation in the similar "explicitctr" files

SC_MODULE(hello_world)
{
    SC_CTOR(hello_world)
    {
        //empty constructor
    }
    void print_hello(void)
    {
        cout << "Hello World!\n";
    }
};

int sc_main(int argc, char** argv)
{
    hello_world hello("hello");
    hello.print_hello();
    return 0;
}



