#include <systemc.h>
#include <iostream>

SC_MODULE(threads)
{
    sc_clock clk; // create a clock 

    SC_CTOR(threads) : clk("clk", 1, SC_SEC) // and set its period to 1 second
    {
        SC_THREAD(thread);
        SC_CTHREAD(cthread, clk);
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
    threads threads("threads");
    std::cout << "starting at " << sc_time_stamp() << std::endl;
    sc_start(5, SC_SEC); // start simulation for 5 seconds
    std::cout << "ending at " << sc_time_stamp() << std::endl;
    return 0;
}