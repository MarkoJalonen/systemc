#include <systemc>
#include <iostream>

// sc_signal is an another primitive channel modelling a single wire
// that's carrying a digital signal
// has read(), write() and implements the sc_signal_inout_if interface
// has different events, for example event() returns true if the value has changed in the 
// delta cycle before the current one and it was at the same simulation time
// the value is updated only if the new value is different and read() won't remove the value
// if multiple values are written during the same delta cycle the newest remains
// sc_signal<int, sc_core::SC_MANY_WRITERS> x allows for multiple prosesses to write to signal
// by default only one process may write to the signal at all

// a class derived from sc_signal is sc_signal_resolved, which allows for different signal states
// aka 1, 0, Z, X of type sc_dt::sc_logic

// sc_signal<bool> allows for the use of posedge_event(), negedge_event() as well as posedge() and negedge()


SC_MODULE(Signal)
{
    sc_core::sc_signal<int> signal;
    sc_core::sc_buffer<int> buffer;

    SC_CTOR(Signal)
    {
        SC_THREAD(rw);
        SC_THREAD(signalDetector);
        sensitive << signal;
        dont_initialize();
        SC_THREAD(bufferDetector);
        sensitive << buffer;
        dont_initialize();
    }

    void rw()
    {
        signal.write(1);
        buffer.write(1);
        std::cout << sc_core::sc_time_stamp() 
            << " : value before first delta cycle : " 
            << signal.read() << std::endl;

        sc_core::wait(sc_core::SC_ZERO_TIME);
        std::cout << sc_core::sc_time_stamp() 
            << " : value after first delta cycle : " 
            << signal.read() << std::endl;

        signal.write(500);
        signal.write(2);
        buffer.write(2);
        std::cout << sc_core::sc_time_stamp() 
            << " : value after two writes but before new delta cycle : " 
            << signal.read() << std::endl;

        sc_core::wait(sc_core::SC_ZERO_TIME);
        std::cout << sc_core::sc_time_stamp() 
            << " : value after second delta cycle : " 
            << signal.read() << std::endl;

        // only the buffer should trigger
        signal.write(2);
        buffer.write(2);
        std::cout << sc_core::sc_time_stamp() << " : rewriting the value 2\n";
        sc_core::wait(sc_core::SC_ZERO_TIME);
    }

    void signalDetector()
    {
        while (true)
        {
            if (signal.event())
            {
                std::cout << "\t" << sc_core::sc_time_stamp() 
                    << " : signal event catched!" << std::endl;
            }
            wait();            
        }
    }

    void bufferDetector()
    {
        while (true)
        {
            if (buffer.event())
            {
                std::cout << "\t" << sc_core::sc_time_stamp() 
                    << " : buffer event catched!" << std::endl;
            }
            wait();            
        }
    }
};

int sc_main(int argc, char** argv)
{
    Signal signal("signal");
    sc_start(2, sc_core::SC_SEC);
    return 0;
}