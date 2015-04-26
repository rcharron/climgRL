#include "image.h"
#include <cmath>
#include <fstream>
#include <sstream>
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
  while(l[0]=='#');
  
  stringstream ss(l);
  ss>>width>>height;
  
  do
  {
    getline(is,l);
  }
  while(l[0]=='#');
  
  stringstream ss2(l);
  char white;
  ss2>>white;
  getline(is,l);

  
  for(int i=0;i<width;i++)
  {
    for(int j=0;j<height;j++)
    {
      data[i][j]=(l[i*width+j]==white);
    }
  }
  updateMeta();
}

void image::write(std::string file)
{
  ofstream os(file);
  if(os.fail())throw string("échec écriture "+file);
  os<<"P5"<<endl<<width<<""<<height<<endl<<1<<endl;
  for(int i=0;i<width;i++)
  {
    for(int j=0;j<height;j++)
    {
      os<<data[i][j];
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
