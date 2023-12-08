#include <systemc.h>
#include <iostream>

// each process has a sensitivity list, 
// similar to HDL

SC_MODULE(Sensitivity)
{
    sc_event event;

    SC_CTOR(Sensitivity)
    {
        SC_THREAD(trigger);
    
        SC_THREAD(catchStatic);
        // adding the event to the catchStatic sensitivity list 
        // via overloaded operator <<
        sensitive << event; 
        
        SC_THREAD(catchDynamic);
    }

    void trigger()
    {
        // wait for catcher to be ready
        // by waiting a delta cycle
        wait(SC_ZERO_TIME);
        while (true)
        {
            event.notify();
            wait(2, SC_SEC);
        }
    }

    void catchStatic()
    {
        while (true)
        {
            wait(); // notice no event
            std::cout << sc_time_stamp() << " : static catch\n";
        }
        
    }

    void catchDynamic()
    {
        while (true)
        {
            wait(event);
            std::cout << sc_time_stamp() << " : dynamic catch\n";
        }
        
    }
};

int sc_main(int argc, char** argv)
{
    Sensitivity sensitivity("sensitivity");
    sc_start(7, SC_SEC);
    return 0;
}