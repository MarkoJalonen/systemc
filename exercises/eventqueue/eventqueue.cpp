#include <systemc.h>
#include <iostream>

// events may be notified only once
// event queues can be multiple times

SC_MODULE(Eventqueue)
{
    sc_event_queue queue;

    SC_CTOR(Eventqueue)
    {
        SC_THREAD(trigger);
        
        SC_THREAD(catcher);
        // queues only work with static sensitivity
        sensitive << queue;
        // to make the catcher not to run during init
        dont_initialize();
    }

    void trigger()
    {
        // stack triggers once
        queue.notify(1, SC_SEC);
        queue.notify(2, SC_SEC);
        queue.notify(4, SC_SEC);
    }

    void catcher()
    {
        while (true)
        {
            std::cout << sc_time_stamp() << " : event catched\n";
            wait();
        }
        
    }
};

int sc_main(int argc, char** argv)
{
    Eventqueue eventqueue("eventqueue");
    sc_start(5, SC_SEC);
    return 0;
}