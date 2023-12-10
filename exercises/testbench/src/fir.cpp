#include "fir.h"

// FIR coefficents
static sc_dt::sc_uint< 8 > coefficents[ 5 ] =
{
    18, 77, 107, 77, 18
};

// FIR main thread  
void FIR::fir_main(void)
{
    sc_dt::sc_uint< 16 > shift_reg;

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
        /* code */
    }
    


    
};

