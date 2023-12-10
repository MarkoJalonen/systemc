#include <systemc>

SC_MODULE( FIR )
{
    // inputs for clock and reset
    sc_core::sc_in< bool > clk;
    sc_core::sc_in< bool > rst;

    // data and handshake inputs from TB
    sc_core::sc_in< sc_dt::sc_int< 16 > > input;
    sc_core::sc_in< bool > input_valid;
    sc_core::sc_out< bool > input_ready;

    // data and handshake outputs to TB
    sc_core::sc_out< sc_dt::sc_int< 16 > > output;
    sc_core::sc_out< bool > output_valid;
    sc_core::sc_in< bool > output_ready;

    void fir_main( void );

    SC_CTOR( FIR )
    {
        SC_THREAD( fir_main );
        sensitive << clk.pos();
        dont_initialize();

        // set reset active low
        reset_signal_is(rst, false);
    };
};