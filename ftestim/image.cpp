#include "image.h"
#include "complexe.h"
#include "fourrier.h"
#include <cmath>
#include <fstream>
#include <sstream>
#include <iostream>
using namespace std;

image::image(string file)
{
//format P5
  ifstream is(file);
  if(is.fail())throw string("échec ouverture "+file);
  string l;
  getline(is,l);
  if(l!="P5")throw string("Format P5 obligé");
  bool begin=false;
  do
  {
    getline(is,l);
  }
  while(l[0]=='#'||l=="");
  
  stringstream ss(l);
  ss>>width>>height;
  
  do
  {
    getline(is,l);
  }
  while(l[0]=='#'||l=="");
  
  stringstream ss2(l);
  int vw;
  char white;
  ss2>>vw;
  white=vw;
  //getline(is,l);
  char c=0;
  
  for(int i=0;i<width;i++)
  {
    data.push_back(vector< bool>(height));
    for(int j=0;j<height;j++)
    {
      is.get(c);
      data[i][j]=(/*l[i*width+j]*/c==white);
    }
  }
  updateMeta();
}

void image::write(std::string file)
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
}

void image::updateMeta()
{
  ComputeCenter();
  ComputeMean();
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
	centerx+=i;
	centery+=j;
	p++;
      }
    }
  }
  centerx/=p;
  centery/=p;
}

void image::ComputeMean()
{
  mean=0;
  int p=0;
  for(int i=0;i<width;i++)
  {
    for (int j=0;j<height;j++)
    {
      if(getValue(i,j))
      {
	mean+=(centerx-i)*(centerx-i)+(centery-j)*(centery-j);
	p++;
      }
    }
  }
  mean/=p;
  mean=sqrt(mean);
}

int image::CanonicalValue(float x, float y)
{
  x-=0.5f;
  int i=centerx+x*4*mean;
  int j=centery+y*4*mean;
  return getValue(i,j);
}


void image::myfourier()
{
  vector<vector<complexe> > d;
  for(int i=0;i<width;i++)
  {
    d.push_back(vector<complexe>(height));
    for(int j=0;j<height;j++)
      d[i][j]=complexe(data[i][j],data[i][j]);
  }
  
  
  std::vector<std::vector<complexe> > r=FFT2D(d,width,height,1);
  
  fourier.clear();
  for(int i=0;i<width;i++)
  {
    fourier.push_back(vector<double>(height));
    for(int j=0;j<height;j++)
      fourier[i][j]=r[i][j].norm();
  }
  /*fourier.clear();
   * 
  for(int i=0;i<width;i++)
  {
    fourier.push_back(vector<double>(height));
    for(int j=0;j<height;j++)
    {
      complexe c(0,0);
      for(int k=0;k<width;k++)
      {
	for(int l=0;l<height;l++)
	{
	  if(data[k][l])
	    c+=complexe(-2.0*M_PI*((k*i)/width+(l*j)/width));
	}
      }
      c/=(width*height);
      fourier[i][j]=c.norm();
      cout<<i<<" "<<j<<endl;
    }
  }*/
}

void image::dessinfourier(string file)
{
  ofstream os(file);
  if(os.fail())throw string("échec écriture "+file);
  os<<"P5"<<endl<<width<<" "<<height<<endl<<255<<endl;
  for(int i=0;i<width;i++)
  {
    for(int j=0;j<height;j++)
    {
      os<<(char)(1-exp(-fourier[i][j])*255);
    }
  }
}
