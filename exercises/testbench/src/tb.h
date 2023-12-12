#include <systemc>
#include <fstream>
#include <string>

SC_MODULE( TB )
{
    // outputs for clock and reset
    sc_core::sc_in< bool > clk;
    sc_core::sc_out< bool > rst;

    // data and handshake outputs to DUT
    sc_core::sc_out< sc_dt::sc_int< 16 > > input;
    sc_core::sc_out< bool > input_valid;
    sc_core::sc_in< bool > input_ready;

    // data and hanshake inputs from DUT
    sc_core::sc_in< sc_dt::sc_int< 16 > > output;
    sc_core::sc_in< bool > output_valid;
    sc_core::sc_out< bool > output_ready;

    // function for creating stimulus
    void source();
    // function for reading output from the DUT
    void sink();

    // pointer to a trace file
    sc_core::sc_trace_file *trac_file;

    // input and output files
    std::ifstream input_file;
    std::ofstream output_file;

    SC_CTOR( TB )
    {
        SC_THREAD( source );
        sensitive << clk.pos();
        dont_initialize();

        SC_THREAD( sink );
        sensitive << clk.pos();
        dont_initialize();
    }
};