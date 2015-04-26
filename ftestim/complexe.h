#ifndef COMPLEXE_H
#define COMPLEXE_H

class complexe 
{
public:
  complexe(double a,double b);
  complexe operator+(complexe a);
  complexe operator*(complexe a);
  complexe& operator+=(complexe a);
  complexe& operator*=(complexe a);
  double norm();
private:
  double re;
  double im;
};


#endif