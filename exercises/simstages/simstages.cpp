#include <systemc.h>
#include <iostream>

// three stages of systemc simulation:
// elaboration: data structs and connections, 
// execution: processes identified and placed into runnable set (or waiting), 
// and then the simulation is run: first evaluation of all processes one by one
// until wait() or return() then the time is advanced and evaluation repeated
// cleanup: when either max time, sc_stop(), or all processes have exited
// destroy objects, release memory and close opened files etc

// there are different callback functions called during these stages (explained below)

SC_MODULE(Stages)
{
    SC_CTOR(Stages)
    {
        std::cout << sc_time_stamp() << " : elaboration : constructor" << std::endl;
        SC_THREAD(thread);
    }

    ~Stages()
    {
        std::cout << sc_time_stamp() << " : cleanup : destructor" << std::endl;
    }

    void thread()
    {
        std::cout << sc_time_stamp() << " : execution : init" << std::endl;
        int i = 0;
        while(true)
        {
            wait(1, SC_SEC);
            std::cout << sc_time_stamp() << " : execution : simulation" << std::endl;
            if(++i >= 3)
            {
                sc_stop();
            }
        }
    }

    // the callback funtions
    void before_end_of_elaboration() 
    {
        std::cout << sc_time_stamp() << " : before end of elaboration" << std::endl;
    }
    void end_of_elaboration() 
    {
        std::cout << sc_time_stamp() << " : end of elaboration" << std::endl;
    }
    void start_of_simulation() 
    {
        std::cout << sc_time_stamp() << " : start of simulation" << std::endl;
    }
    void end_of_simulation() 
    {
        std::cout << sc_time_stamp() << " : end of simulation" << std::endl;
    }
};

int sc_main(int argc, char** argv)
{
    Stages stages("stages");
    sc_start();
    return 0;
}