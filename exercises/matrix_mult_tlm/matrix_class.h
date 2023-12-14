#ifndef MATRIX_CLASS_H
#define MATRIX_CLASS_H

#include "matrix_mult.h"
#include "nextpow2.h"

template< typename element_t, int N > class Matrix
{
    private:
        element_t matrix[N][N]; 
    
    public:
        Matrix()
        {
            for ( int i = 0; i < N; i++ )
            {
                for ( int j = 0; j < N; j++ )
                {
                    matrix[i][j] = 0;
                }
            }

        }

        Matrix( element_t input_vals[N][N] )
        {
            for ( int i = 0; i < N; i++ )
            {
                for ( int j = 0; j < N; j++ )
                {
                    matrix[i][j] = input_vals[i][j];
                }
            }
        }

        void set_element
            ( 
                sc_dt::sc_uint< NEXTPOW2<N>::val > i, 
                sc_dt::sc_uint< NEXTPOW2<N>::val > j,
                element_t value
            )
        {
            matrix[i][j] = val;
        }

        void get_element
            ( 
                sc_dt::sc_uint< NEXTPOW2<N>::val > i, 
                sc_dt::sc_uint< NEXTPOW2<N>::val > j
            )
        const
        {
            return matrix[i][j];
        }

        void transpose()
        {
            for(int i = 0; i < N; i++)
            {
                for(int j = 0; j < N; j++)
                { 
                    matrix[i][j] = matrix[i][j] + matrix[j][i];
                    matrix[j][i] = matrix[i][j] - matrix[j][i];
                    matrix[i][j] = matrix[i][j] - matrix[j][i];
                }
            }
        }

        struct return_matrix
        {
            typedef Matrix< tlm_result_t, N > mult_result_t;
        };

        typename return_matrix::mult_result_t operator * ( const Matrix &param )
        {
            typename return_matrix::mult_result_t result_matrix;

            for ( int i = 0; i < N; i++ )
            {
                for ( int j = 0; j < N; j++ )
                {
                    hls_result_t C_temp = 0;
                    for ( int k = 0; k < N; k++ )
                    {
                        C_temp += getElement( i, k ) * param.getElement( k, j );
                    }
                    return_matrix.setElement( i, j, C_temp );
                }
            }            
            return return_matrix;
        }
};

#endif