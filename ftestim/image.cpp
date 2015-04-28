#include "image.h"
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
  data=vector<vector<bool> >(width,vector<bool>(height,false));
  for(int j=0;j<height;j++)
  {
    for(int i=0;i<width;i++)
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
  os<<"P5"<<endl<<500<<" "<<500<<endl<<1<<endl;
  /*for(int i=0;i<width;i++)
  {
    for(int j=0;j<height;j++)
    {
      os<<(char)data[i][j];
    }
  }*/
  for(int j=0;j<500;j++)
  {
    for(int i=0;i<500;i++)
    {
      os<<(char)this->CanonicalValue((1.0f/500)*i,(1.0f/500)*j);
    }
  }

}

void image::updateMeta()
{
  ComputeCenter();
  ComputeMean();
  myfourier();
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
	mean+=sqrt((centerx-i)*(centerx-i)+(centery-j)*(centery-j));
	p++;
      }
    }
  }
  mean/=p;
}

int image::CanonicalValue(float x, float y)
{
  x-=0.5f;
  y-=0.5f;
  int i=centerx+x*4*mean;
  int j=centery+y*4*mean;
  return getValue(i,j);
}


void image::myfourier()
{
  complex d[512*512];
  int val;
  for(int i=0;i<512;i++)
  {
    for(int j=0;j<512;j++)
    {
      val=this->CanonicalValue((1.0f/512)*i,(1.0f/512)*j);
      d[j+512*i]=complex{val,val};
    }
  }
  /*for(int i=0;i<width;i++)
  {
    d.push_back(vector<complexe>(height));
    for(int j=0;j<height;j++)
      d[i][j]=complexe(data[i][j],data[i][j]);
  }*/
  
  
  fft2D(d,512,512,1);
  
  fourier=vector<vector<double> >(64,vector<double>(64,0.0));
  
  double norm=0;
  for(int i=0;i<512;i++)
  {
    for(int j=0;j<512;j++)
    {
      fourier[i/8][j/8]+=sqrt(d[i+j*512].Re*d[i+j*512].Re+d[i+j*512].Im*d[i+j*512].Im);
    }
  }
  for(int i=0;i<64;i++)
  {
    for(int j=0;j<64;j++)
    {
      norm+=fourier[i][j];
    }
  }
  for(int i=0;i<64;i++)
  {
    for(int j=0;j<64;j++)
    {
      fourier[i][j]/=norm;
    }
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
  unsigned int t=fourier.size();
  os<<"P5"<<endl<<t<<" "<<t<<endl<<255<<endl;
  
  float ma=0;
for(int j=0;j<t;j++)
  {
    for(int i=0;i<t;i++)
    {
      if(fourier[i][j]>=ma)ma=fourier[i][j];
    }
  }
  
  for(int j=0;j<t;j++)
  {
    for(int i=0;i<t;i++)
    {
      int n=(fourier[i][j]/ma)*255;
      os<<(char)(n);
    }
  }
}


float image::distanceEMD(image i2)
{
 emd EMD;
 return EMD.compute(fourier,i2.fourier);  
}

vector< vector< double > >* image::getFourier()
{
  return &fourier;
}

