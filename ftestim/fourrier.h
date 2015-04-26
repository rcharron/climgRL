#ifndef FOURRIER_H
#define FOURRIER_H

#include "complexe.h"
#include <vector>

std::vector<std::vector<complexe> > FFT2D(std::vector<std::vector<complexe> >& c, int nx, int ny, int dir);
void FFT1D(int dir, int m, std::vector<double>& x, std::vector<double>& y );


#endif