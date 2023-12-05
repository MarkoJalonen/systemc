#include <systemc>
#include <iostream>

// for communication there are three main concepts
// interface: declares communication services
// channel: defines communication services
// port: pointer to the channel for access from outside of the module
// where the channel is initialized

// good practise to always call communication functions via a port if
// they are outside of the module
// calling member functions belonging to a child module's channel instance
// should be made through an export of the child module
// calling comm functions inside the same channel init module
// without a port is allowed (known as portless channel access)

SC_MODULE(ModuleOne)
{
    sc_core::sc_signal<int> signal;
    // a port with signal inout interface of type int 
    sc_core::sc_port<sc_core::sc_signal_inout_if<int> > port;

    SC_CTOR(ModuleOne)
    {
        SC_THREAD(insideRead);
        sensitive << signal;
        dont_initialize();
        SC_THREAD(insideWrite);
        SC_THREAD(outsideWrite);
    }

    void insideRead(){
        while (true)
        {
            std::cout << sc_core::sc_time_stamp() 
                << " : inside read : " << signal.read()
                << std::endl;
            wait(); 
        }
    }

    void insideWrite()
    {
        int value = 0;
        while (true)
        {
            signal.write(value++);
            wait(1, sc_core::SC_SEC);
        }
    }

    void outsideWrite()
    {
        int value = 0;
        while (true)
        {
            port->write(value++); // a pointer
            wait(1, sc_core::SC_SEC);
        }
    }   
};

SC_MODULE(ModuleTwo)
{
    // a port with signal in interface of type int 
    sc_core::sc_port<sc_core::sc_signal_in_if<int> > port;

    SC_CTOR(ModuleTwo)
    {
        SC_THREAD(outsideRead);
        sensitive << port;
        dont_initialize();
    }

    void outsideRead()
    {
        while (true)
        {
            std::cout << sc_core::sc_time_stamp() 
                << " : outside read : " << port->read()
                << std::endl;
            wait(); 
        }
        
    }

    
};

int sc_main(int argc, char** argv)
{
    ModuleOne moduleOne("moduleOne");
    ModuleTwo moduleTwo("moduleTwo");

    sc_core::sc_signal<int> signal;
    moduleOne.port(signal);
    moduleTwo.port(signal);

    sc_start(3, sc_core::SC_SEC);

    return 0;
}