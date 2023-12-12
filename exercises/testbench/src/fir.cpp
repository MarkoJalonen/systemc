#include "fir.h"

// FIR coefficents
static sc_dt::sc_uint< 8 > coefficents[ 5 ] =
{
    18, 77, 107, 77, 18
};

// FIR main thread  
void FIR::fir_main(void)
{
    sc_dt::sc_uint< 16 > shift_reg[ 5 ];

    // reset shift register
    for (int i = 4; i > 0; i--)
    {   
        shift_reg[ i ] = 0;
    }

    // reset handshake and output
    input_ready.write( 0 );
    output_valid.write( 0 );
    output.write( 0 );

    // wait for next clock cycle
    wait();

    while (true)
    {
        sc_dt::sc_int< 16 > input_value;
        sc_dt::sc_int< 16 > output_value;

        // set input ready to receive and wait for valid input
        input_ready.write( 1 );
        do
        {
            wait();
        } while ( !input_valid.read() );

        // when ready, read input and set input ready to not ready
        input_value = input.read();
        input_ready.write( 0 );

        // shift the register and set the write the new input
        for (int i = 4; i > 0; i--)
        {
            shift_reg[ i ] = shift_reg[ i-1 ];
        }
        shift_reg[ 0 ] = input_value;

        // calculate the result
        for (int i = 0; i < 5; i++)
        {
            output_value += coefficents[ i ] * shift_reg[ i ];
        }

        // set output valid, write the value and wait for output ready
        output_valid.write( 1 );
        output.write( output_value );
        do
        {
            wait();
        } while ( !output_ready.read() );
        output_valid.write( 0 );
    }
};
