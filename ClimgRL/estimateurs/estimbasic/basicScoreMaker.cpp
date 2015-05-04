#include "basicScoreMaker.h"
#include <cmath>


std::string model(std::vector< float >& mean, std::vector< float >& var)
{
  float m1,m2,v1,v2;
  unsigned int t1=static_cast<unsigned int >(mean.size());
  unsigned int t2=static_cast<unsigned int >(var.size());
  unsigned int i;
  m1=m2=v1=v2=0;
  
  for(i=0;i<t1;i++)
  {
    m1+=mean[i];
  }
  for(i=0;i<t2;i++)
  {
    m2+=var[i];
  }
  
  m1/=static_cast<float>(t1);
  m2/=static_cast<float>(t2);
  
  for(i=0;i<t1;i++)
  {
    v1+=(mean[i]-m1)*(mean[i]-m1);
  }
  for(i=0;i<t2;i++)
  {
    v2+=(var[i]-m2)*(var[i]-m2);
  }
  v1/=static_cast<float>(t1);
  v2/=static_cast<float>(t2);
  
  v1=static_cast<float>(sqrt(v1));
  v2=static_cast<float>(sqrt(v2));
  
  std::stringstream ss;
  ss<<m1<<" "<<m2<<" "<<v1<<" "<<v2<<" ";
  return ss.str();
}

float score(float my,float m,float v)
{
  float t=(my-m);
  v=2*v;
  t=-t*t*t*t;
  t/=v*v*v*v;
  return static_cast<float>(sqrt(sqrt(exp(t))));
}

float score(std::string model, float mean, float var)
{
  std::stringstream ss(model);
  float m1,m2,v1,v2;
  ss>>m1>>m2>>v1>>v2;
  return score(mean,m1,v1)*score(var,m2,v2);
}
