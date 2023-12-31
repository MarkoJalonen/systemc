#include <systemc.h>
#include <iostream>

SC_MODULE(HelloWorld)
{
    // SC_HAS_PROCESS(name)
    // to enable SC_METHOD/SC_THREAD/SC_CTHREAD with SC_CURRENT_USER_MODULE definition
    // SC_CTOR enables them as well but also generates the default constructor with
    // only one parameter (the name of the module)
    SC_HAS_PROCESS(HelloWorld); 

    const int n;

    // explicit constructor with the required name as well as custom parameter
    HelloWorld(sc_module_name name, int n) : sc_module(name), n(n)
    {
        // register the method for simulation
        SC_METHOD(print_hello);
    }
    void print_hello(void)
    {
        int i = n;
        while(i-- > 0)
        {
            std::cout << "Hello World!\n";    
        }
    }
};

int sc_main(int argc, char** argv)
{
    HelloWorld hello("hello", 5);
    hello.print_hello();
    return 0;
}



