#include <systemc.h>
#include <iostream>

// systemc simulates the processes in parrallel in regards to simulation time
// in real time the processes are evaluated one by one for each event

SC_MODULE(Concurrency)
{
    SC_CTOR(Concurrency)
    {
        SC_THREAD(thread1);
        SC_THREAD(thread2);
    }
    
    void thread1()
    {
        while(true)
        {
            std::cout << sc_time_stamp() << " : thread1\n";
            wait(2, SC_SEC);
        }
    }

    void thread2()
    {
        while(true)
        {
            std::cout << sc_time_stamp() << " : thread2\n";
            wait(3, SC_SEC);
        }
    }
};

int sc_main(int argc, char** argv)
{
    Concurrency concurrency("concurrency");
    sc_start(7, SC_SEC);
    return 0;
}
