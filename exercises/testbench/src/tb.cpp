#include "tb.h"

void TB::source( void )
{
    // reset input
    input.write( 0 );
    input_valid.write( 0 );
    
    // send reset
    rst.write( 0 );
    wait();
    rst.write( 1 );
    wait();

    // open the input file
    input_file.open( "input.txt" );
    if ( !input_file.is_open() )
    {
        SC_REPORT_ERROR("TB::source", "cannot open input file");
        sc_core::sc_stop();
    }
    // read lines from the input file and write them to the output
    std::string line;
    while ( std::getline( input_file, line ) )
    {
        line.erase( std::remove( line.begin(), line.end(), '\n' ), line.end() );
        input_valid.write( 1 );
        input.write( std::stoi( line ) );
        do
        {
            wait();
        } while ( !input_ready.read() );
        input_valid.write( 0 );
    }
    
    input_file.close();
    sc_core::sc_stop();
}

void TB::sink( void )
{
    sc_dt::sc_int< 16 > result;

    // open the output file
    output_file.open( "output.txt" );
    if ( !output_file.is_open() )
    {
        SC_REPORT_ERROR("TB::sink", "cannot open output file");
        sc_core::sc_stop();
    }
    
    // read values from output
    output_ready.write( 0 );
    for (int i = 0; i < 64; i++)
    {
        output_ready.write( 1 );
        do
        {
            wait();
        } while ( !output_valid.read() );

        result = output.read();
        output_ready.write( 0 );
        
        output_file << result << std::endl;
        
    }
}