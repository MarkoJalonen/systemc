#include <systemc>
#include "fir.h"
#include "tb.h"

SC_MODULE( TOP )
{
    // modules
    TB *tb;
    FIR *fir;

    // local signals
    sc_core::sc_signal< bool > rst_signal;
    sc_core::sc_signal< sc_dt::sc_int< 16 > > input_signal;
    sc_core::sc_signal< sc_dt::sc_int< 16 > > output_signal;
    sc_core::sc_clock clk_signal;

    // handshake signals
    sc_core::sc_signal< bool > input_valid_signal;
    sc_core::sc_signal< bool > input_ready_signal;
    sc_core::sc_signal< bool > output_valid_signal;
    sc_core::sc_signal< bool > output_ready_signal;

    SC_CTOR( TOP ) : clk_signal("clk_signal", 10, sc_core::SC_NS)
    {
        // tb connections
        tb = new TB("tb");
        tb->clk( clk_signal );
        tb->rst( rst_signal );
        tb->input( input_signal );
        tb->input_valid( input_valid_signal );
        tb->input_ready( input_ready_signal );
        tb->output( output_signal );
        tb->output_valid( output_valid_signal );
        tb->output_ready( output_ready_signal );

        // fir connections
        fir = new FIR("fir");
        fir->clk( clk_signal );
        fir->rst( rst_signal );
        fir->input( input_signal );
        fir->input_valid( input_valid_signal );
        fir->input_ready( input_ready_signal );
        fir->output( output_signal );
        fir->output_valid( output_valid_signal );
        fir->output_ready( output_ready_signal );
    }   

    ~TOP() 
    {
        delete tb;
        delete fir;
    }
};

TOP *top = NULL;

int sc_main(int argc, char** argv)
{
    // open report files
    sc_core::sc_trace_file *trace_file = sc_core::sc_create_vcd_trace_file("trace");
    sc_core::sc_report_handler::set_log_file_name("report.log");

    top = new TOP("top");

    // trace file signals
    sc_trace(trace_file, top->clk_signal, "clk");

    sc_trace(trace_file, top->input_signal, "input");
    sc_trace(trace_file, top->input_valid_signal, "input_valid");
    sc_trace(trace_file, top->input_ready_signal, "input_ready");
    
    sc_trace(trace_file, top->output_signal, "output");
    sc_trace(trace_file, top->output_valid_signal, "output_valid");
    sc_trace(trace_file, top->output_ready_signal, "output_ready");



    // start simulation
    SC_REPORT_INFO("main", "simulation starts");
    sc_core::sc_start();

    // end simulation
    sc_core::sc_close_vcd_trace_file(trace_file);
    SC_REPORT_INFO("main", "simulation ends");
    return 0;
}