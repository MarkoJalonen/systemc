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
    input_file.open( "../input", std::ifstream::in );
    if ( !input_file.is_open() )
    {
        sc_core::sc_stop();
        // add logging
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

}

void TB::sink( void )
{

}