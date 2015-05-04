#ifndef COMPLEXE_H
#define COMPLEXE_H

class complexe 
{
public:
  complexe(double a,double b);
  complexe(double phase);
  complexe();
  complexe operator+(const complexe& a);
  complexe operator*(const complexe& a);
  complexe& operator+=(const complexe& a);
  complexe& operator*=(const complexe& a);
  complexe& operator/=(const double& a);
  double norm();
  double re;
  double im;
};


#endif