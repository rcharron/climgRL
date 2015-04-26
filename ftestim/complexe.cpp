#include "complexe.h"
#include <cmath>

complexe::complexe():re(0),im(0)
{
}


complexe::complexe(double a, double b):re(a),im(b)
{
}

complexe::complexe(double phase):re(cos(phase)),im(sin(phase))
{
}


double complexe::norm()
{
  return sqrt(re*re+im*im);
}


complexe complexe::operator+(const complexe& a)
{
  return complexe(a.re+re,a.im+im);
}

complexe complexe::operator*(const complexe& a)
{
  return complexe(a.re*re-a.im*im,a.im*re+a.re*im);
}

complexe& complexe::operator*=(const complexe& a)
{
  double r=a.re*re-a.im*im;
  double i=a.im*re+a.re*im;
  re=r;
  im=i;
  return *this;

}

complexe& complexe::operator+=(const complexe& a)
{
  re+=a.re;
  im+=im;
  return *this;
}


complexe& complexe::operator/=(const double& a)
{
  re/=a;
  im/=a;
  return *this;
}
