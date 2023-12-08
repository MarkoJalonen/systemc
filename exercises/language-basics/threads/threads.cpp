#include <systemc.h>
#include <iostream>

// threads of a module (as well as methods)
// are triggered once by default and after that 
// by different methods (waits)

SC_MODULE(Threads)
{
    sc_clock clk; // create a clock 

    SC_CTOR(Threads) : clk("clk", 1, SC_SEC) // and set its period to 1 second
    {
        SC_THREAD(thread);          // register a thread
        SC_CTHREAD(cthread, clk);   // register a clocked thread
    }

    void thread()
    {
        while(true) 
        {
            std::cout << "thread at " << sc_time_stamp() << std::endl;
            wait(2, SC_SEC); // wait for 2 seconds of simulation
        }
    }

    void cthread()
    {
        while(true)
        {
            std::cout << "cthread at " << sc_time_stamp() << std::endl;
            wait(); // wait for the next trigger
        }
    }
};

int sc_main(int argc, char** argv)
{
    Threads threads("threads");
    std::cout << "starting at " << sc_time_stamp() << std::endl;
    sc_start(5, SC_SEC); // start simulation for 5 seconds
    std::cout << "ending at " << sc_time_stamp() << std::endl;
    return 0;
}