#include "fourrier.h"
#include <cmath>

using namespace std;

vector<vector<complexe> > FFT2D(vector<vector<complexe> >& c, int nx, int ny, int dir)
{
            int i,j;
            int m;//Power of 2 for current number of points
            vector<double> real(nx);
            vector<double> imag(nx);
            vector<vector<complexe> > output;//=new COMPLEX [nx,ny];
            output = c; // Copying Array
            // Transform the Rows 
            
            for (j=0;j<ny;j++) 
            {
              for (i=0;i<nx;i++) 
               {
                 real[i] = c[i][j].re;
                 imag[i] = c[i][j].im;
               }
            // Calling 1D FFT Function for Rows
            m = (int)log2((double)nx);//Finding power of 2 for current number of points e.g. for nx=512 m=9
            FFT1D(dir,m,real,imag);

              for (i=0;i<nx;i++) 
               {
               //  c[i,j].real = real[i];
               //  c[i,j].imag = imag[i];
                   output[i][j].re = real[i];
                   output[i][j].im = imag[i];
               }
            }
            // Transform the columns  
            real = vector<double>(ny);
            imag = vector<double>(ny);
                  
            for (i=0;i<nx;i++) 
            {
              for (j=0;j<ny;j++) 
               {
                //real[j] = c[i,j].real;
                //imag[j] = c[i,j].imag;
                   real[j] = output[i][j].re;
                   imag[j] = output[i][j].im;
               }
           // Calling 1D FFT Function for Columns
           m = (int)log2((double)ny);//Finding power of 2 for current number of points e.g. for nx=512 m=9
           FFT1D(dir,m,real,imag);
             for (j=0;j<ny;j++) 
               {
                //c[i,j].real = real[j];
                //c[i,j].imag = imag[j];
                output[i][j].re = real[j];
                output[i][j].im = imag[j];
               }
            }
          
           // return(true);
            return(output);
}
        /*-------------------------------------------------------------------------
            This computes an in-place complex-to-complex FFT
            x and y are the real and imaginary arrays of 2^m points.
            dir = 1 gives forward transform
            dir = -1 gives reverse transform
            Formula: forward
                     N-1
                      ---
                    1 \         - j k 2 pi n / N
            X(K) = --- > x(n) e                  = Forward transform
                    N /                            n=0..N-1
                      ---
                     n=0
            Formula: reverse
                     N-1
                     ---
                     \          j k 2 pi n / N
            X(n) =    > x(k) e                  = Inverse transform
                     /                             k=0..N-1
                     ---
                     k=0
            */
        void FFT1D(int dir, int m, vector<double>& x, vector<double>& y )
            {
                long nn, i, i1, j, k, i2, l, l1, l2;
                double c1, c2, tx, ty, t1, t2, u1, u2, z;
                /* Calculate the number of points */
                nn = 1;
                for (i = 0; i < m; i++)
                    nn *= 2;
                /* Do the bit reversal */
                i2 = nn >> 1;
                j = 0;
                for (i = 0; i < nn - 1; i++)
                {
                    if (i < j)
                    {
                        tx = x[i];
                        ty = y[i];
                        x[i] = x[j];
                        y[i] = y[j];
                        x[j] = tx;
                        y[j] = ty;
                    }
                    k = i2;
                    while (k <= j)
                    {
                        j -= k;
                        k >>= 1;
                    }
                    j += k;
                }
                /* Compute the FFT */
                c1 = -1.0;
                c2 = 0.0;
                l2 = 1;
                for (l = 0; l < m; l++)
                {
                    l1 = l2;
                    l2 <<= 1;
                    u1 = 1.0;
                    u2 = 0.0;
                    for (j = 0; j < l1; j++)
                    {
                        for (i = j; i < nn; i += l2)
                        {
                            i1 = i + l1;
                            t1 = u1 * x[i1] - u2 * y[i1];
                            t2 = u1 * y[i1] + u2 * x[i1];
                            x[i1] = x[i] - t1;
                            y[i1] = y[i] - t2;
                            x[i] += t1;
                            y[i] += t2;
                        }
                        z = u1 * c1 - u2 * c2;
                        u2 = u1 * c2 + u2 * c1;
                        u1 = z;
                    }
                    c2 = sqrt((1.0 - c1) / 2.0);
                    if (dir == 1)
                        c2 = -c2;
                    c1 = sqrt((1.0 + c1) / 2.0);
                }
                /* Scaling for forward transform */
                if (dir == 1)
                {
                    for (i = 0; i < nn; i++)
                    {
                        x[i] /= (double)nn;
                        y[i] /= (double)nn;
                       
                    }
                }
                


              //  return(true) ;
                return;
            }