#include "image.h"
#include <cmath>
#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;

image::image(string file)
{
//format P5
  //cout<<"test img : "<<file<<endl;
  ifstream is(file);
  if(is.fail())throw string("échec ouverture "+file);
  string l;
  getline(is,l);
  if(l!="P5")throw string("Format P5 obligé");
  do
  {
    getline(is,l);
  }
  while(l[0]=='#'||l=="");
  
  stringstream ss(l);
  ss>>width>>height;
  //	cout<<"test wh "<<width<<" "<<height<<endl;
  do
  {
    getline(is,l);
  }
  while(l[0]=='#'||l=="");
  
  stringstream ss2(l);
  int vw;
  ss2>>vw;
  //getline(is,l);
  char c=0;
  data=vector<vector<bool> >(width,vector<bool>(height,false));
  
  
  for(int j=0;j<height;j++)
  {
    for(int i=0;i<width;i++)
    {
      is.get(c);
      data[i][j]=(c!=0);
    }
  }
  //cout<<endl;
  updateMeta();
}

/*void image::write(std::string file)
{
  ofstream os(file);
  if(os.fail())throw string("échec écriture "+file);
  os<<"P5"<<endl<<width<<" "<<height<<endl<<1<<endl;
  for(int i=0;i<width;i++)
  {
    for(int j=0;j<height;j++)
    {
      os<<(char)data[i][j];
    }
  }
}*/

void image::write(std::string file)
{
  ofstream os(file);
  if(os.fail())throw string("échec écriture "+file);
  os<<"P5"<<endl<<800<<" "<<800<<endl<<1<<endl;
  for(int j=0;j<800;j++)
  {
    for(int i=0;i<800;i++)
    {
      os<<(char)this->CanonicalValue((1.0f/800.0f)*static_cast<float>(i),(1.0f/800.0f)*static_cast<float>(j));
    }
  }
}

void image::updateMeta()
{
  ComputeCenter();
  ComputeMean();
  ComputeVariance();
}

bool image::getValue(int i, int j)
{
  if(i<0)
    return false;
  if(j<0)return false;
  if(i>=width)return false;
  if(j>=height)return false;
  return data[i][j];
}

void image::ComputeCenter()
{
  centerx=0;
  centery=0;
  int p=0;
  for(int i=0;i<width;i++)
  {
    for (int j=0;j<height;j++)
    {
      if(getValue(i,j))
      {
	centerx+=static_cast<float>(i);
	centery+=static_cast<float>(j);
	p++;
      }
    }
  }
  centerx/=static_cast<float>(p);
  centery/=static_cast<float>(p);
}

void image::ComputeMean()
{
  mean=0;
  extrema=0;
  int p=0;
  float dist;
  for(int i=0;i<width;i++)
  {
    for (int j=0;j<height;j++)
    {
      if(getValue(i,j))
      {
	dist=(centerx-static_cast<float>(i))*(centerx-static_cast<float>(i))+(centery-static_cast<float>(j))*(centery-static_cast<float>(j));
	dist=sqrt(dist);
	if(extrema<dist)extrema=dist;
	mean+=dist;
	p++;
      }
    }
  }
  //cout<<"test !0 "<<p<<endl;
  mean/=static_cast<float>(p);
}

void image::ComputeVariance()
{
  var=0;
  float dist;
  int p=0;
  for(int i=0;i<width;i++)
  {
    for (int j=0;j<height;j++)
    {
      if(getValue(i,j))
      {
	dist=(centerx-static_cast<float>(i))*(centerx-static_cast<float>(i))+(centery-static_cast<float>(j))*(centery-static_cast<float>(j));
	dist=sqrt(dist);
	var+=(dist-mean)*(dist-mean);
	p++;
      }
    }
  }
  var/=static_cast<float>(p);
  var=sqrt(var);
}


int image::CanonicalValue(float x, float y)
{
  x-=0.5f;
  y-=0.5f;
  int i=static_cast<int>(centerx+x*4.0f*mean);
  int j=static_cast<int>(centery+y*4.0f*mean);
  return getValue(i,j);
}


float image::getNormMean()
{
  return mean/extrema;
}

float image::getNormVar()
{
  return var/extrema;
}
