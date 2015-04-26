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
  
  stringstream ss(l);
  char white;
  ss>>white;
  do
  {
    getline(is,l);
  }
  while(l[0]=='#');
  char c;
  for(int i=0;i<width;i++)
  {
    for(int j=0;j<height;j++)
    {
      data[i][j]=(l[i*width+j]==white);
    }
  }
  updateMeta();
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
  int x=centerx+x*4*mean;
  int y=centery+y*4*mean;
  return getValue(x,y);
}
