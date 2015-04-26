#include "complexe.h"
#include <cmath>

complexe::complexe(double a, double b):re(a),im(b)
{
}

double complexe::norm()
{
  return sqrt(re*re+im*im);
}


complexe complexe::operator+(complexe a)
{
  return complexe(a.re+re,a.im+im);
}

complexe complexe::operator*(complexe a)
{
  return complexe(a.re*re-a.im*im,a.im*re+a.re*im);
}