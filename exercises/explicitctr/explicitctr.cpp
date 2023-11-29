#include <systemc.h>
#include <stdio.h>

SC_MODULE(hello_world)
{
    SC_CTOR(hello_world);
    const int n;
    hello_world(sc_module_name name, int n) : sc_module(name), n(n)
    {
        SC_METHOD(print_hello);
    }
    void print_hello(void)
    {
        int i = n;
        while(i-- > 0)
        {
            cout << "Hello World!\n";    
        }
    }
};

int sc_main(int argc, char** argv)
{
    hello_world hello("hello", 5);
    hello.print_hello();
    return 0;
}



