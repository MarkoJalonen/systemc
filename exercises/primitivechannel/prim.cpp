#include <systemc>
#include <iostream>

// sc_prim_channel is a base class for all primitive channels
// has unique access to the schedulers update phase
// has no ports, hierarchy or simulation processes
// has following member functions:
// request_update() scheduler queues an update req for the channel
// async_request_update() same as request_update but thread safe
// allows realiable calling from outside the systemc kernel aka the os
// not recommended inside the systemc kernel
// update() which is called by the scheduler in the update phase
// after an update request, definition does nothing, needs to be overwritten
// next_trigger()
// wait();

class GeneratorInterface : public sc_core::sc_interface 
{
    public: 
        virtual void notify() = 0;
};

class ReceiverInterface : public sc_core::sc_interface 
{
    public:
        virtual const sc_core::sc_event& default_event() const = 0;
};

class Interrupt : public sc_core::sc_prim_channel, public GeneratorInterface, public ReceiverInterface
{
    public:
        Interrupt(sc_core::sc_module_name name) : sc_core::sc_prim_channel(name) {}
        void notify() 
        {
            event.notify();
        }

        const sc_core::sc_event& default_event() const
        {
            return event;
        }

    private:
        sc_core::sc_event event;
};

SC_MODULE(Generator) 
{
    sc_core::sc_port<GeneratorInterface> port;
    SC_CTOR(Generator)
    {
        SC_THREAD(generateInterrupt);
    }

    void generateInterrupt() 
    {
        while (true)
        {
            port->notify();
            wait(1, sc_core::SC_SEC);
        }
    }
};

SC_MODULE(Receiver)
{
    sc_core::sc_port<ReceiverInterface> port;

    SC_CTOR(Receiver)
    {
        SC_THREAD(receiveInterrupt);
        sensitive << port;
        dont_initialize();
    }

    void receiveInterrupt()
    {
        while (true)
        {
            std::cout << sc_core::sc_time_stamp()
                << " : interrupt received\n";
            wait();
        }
        
    }
};

int sc_main(int argc, char** argv)
{
    Generator gen("gen");
    Receiver rec("rec");
    Interrupt r("r");

    gen.port(r);
    rec.port(r);
    
    sc_start(3, sc_core::SC_SEC);
    return 0;
}