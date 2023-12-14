#ifndef MATRIX_MULT_H
#define MATRIX_MULT_H

#include <systemc>

// matrix size NxN
const int N = 8;

// bit accurate datatype widths
const int WIDTH         = 6;    // input width
const int RESULT_WIDTH  = 15;   // result width
const int TRANS_WIDTH   = 2;    // transpose selection width

// datatypes for golden reference
typedef int data_t;
typedef int result_t;
// and bit accurate
typedef sc_dt::sc_int< WIDTH >          tlm_data_t;
typedef sc_dt::sc_int< RESULT_WIDTH >   tlm_result_t;
typedef sc_dt::sc_uint< TRANS_WIDTH >   tlm_trans_t;

// golden reference function declaration
void matrix_multiplication
( 
    data_t A[N][N], data_t B[N][N], 
    result_t C[N][N], int transpose 
);

// template for a fifo datatype
template< typename T > struct channel_t
{
    T array[N][N];
};

#endif