#ifndef FOURRIER_H
#define FOURRIER_H

typedef double real;                 /* can be long double, double, or float */
typedef struct { real Re; real Im; }  complex;         /* for complex number */

void fft2D(complex x[], int n1, int n2, int flag);

#endif