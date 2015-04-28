#include "basicScoreMaker.h"
#include <cmath>


std::string model(std::vector< float >& score)
{
  float m,v;//moyenne, écart-type
  unsigned int t=score.size();
  unsigned int i;
  m=v=0;
  
  for(i=0;i<t;i++)
  {
    m+=score[i];
  }
  
  
  m/=t;
  
  for(i=0;i<t;i++)
  {
    v+=(score[i]-m)*(score[i]-m);
  }
  v/=t;
  
  v=sqrt(v);
  
  std::stringstream ss;
  ss<<m<<" "<<v;
  return ss.str();
}

float score(float my,float m,float v)
{
  float t=(my-m);
  v=2*v;
  t=-t*t*t*t;
  t/=v*v*v*v;
  return exp(t);
}

float score(std::string model, float solidite)
{
  std::stringstream ss(model);
  float m,v;
  ss>>m>>v;
  return score(solite,m,v);
}
