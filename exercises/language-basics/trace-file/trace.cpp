#include <systemc>

// sc_trace_file allows for 'Value Change Dump' files

SC_MODULE(Trace)
{
    sc_core::sc_port<sc_core::sc_signal<int> > port;
    
    SC_CTOR(Trace)
    {
        SC_THREAD(writer);
    }

    void writer()
    {
        int value = 0;
        while (true)
        {
            port->write(value++);
            wait(1, sc_core::SC_SEC);
        }
    }
};

int sc_main(int argc, char** argv)
{
    Trace trace("trace");
    sc_core::sc_signal<int> signal;
    trace.port(signal);
    // create and open a file, can be done at any time but before starting tracing
    sc_core::sc_trace_file* file = sc_core::sc_create_vcd_trace_file("trace");
    // trace the signal with label signal, must be done before one delta cycle of opening the file
    sc_core::sc_trace(file, signal, "signal");
    sc_core::sc_start(6, sc_core::SC_SEC);
    // close the file after the simulation, must be closed after the last delta cycle of sim
    sc_core::sc_close_vcd_trace_file(file);
    return 0;
}