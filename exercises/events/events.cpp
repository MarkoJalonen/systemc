#include <systemc.h>
#include <iostream>

SC_MODULE(Events)
{
    sc_event event; // create an event object

    SC_CTOR(Events)
    {
        SC_THREAD(trigger);
        SC_THREAD(catcher);
    }

    void trigger()
    {
        while (true)
        {
            event.notify(2, SC_SEC); // trigger at 2, 4, 10
            
            if (sc_time_stamp() == sc_time(4, SC_SEC))
            {
                event.cancel();
                event.notify(1, SC_SEC); // trigger @ 4+1
            } 
            else if (sc_time_stamp() == sc_time(6, SC_SEC))
            {
                event.cancel();
                event.notify(SC_ZERO_TIME); // trigger @ 6
            }
            std::cout << sc_time_stamp() << " : event triggered\n";
            wait(2, SC_SEC);
        }
        
    }

    void catcher()
    {
        while (true)
        {
            wait(event);
            std::cout << sc_time_stamp() << " : event catched\n";
        }
        
    }
};

int sc_main(int argc, char** argv)
{
    Events events("events");
    sc_start(13, SC_SEC);
    return 0;
}