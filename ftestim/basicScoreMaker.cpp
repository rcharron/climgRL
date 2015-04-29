#include "basicScoreMaker.h"
#include <cmath>
#include "image.h"
#include <iostream>

using namespace std;

string model(vector< string > files)
{
  unsigned int t,i;
  t=files.size();
  vector<vector<double> > histref(64,vector<double>(64));
  string res;
  string fl;
  for(i=0;i<t;i++)
  {
    //cout<<files[i]<<endl;
    image img(files[i]);
    for(int i=0;i<64;i++)
    {
      for(int j=0;j<64;j++)
      {
	histref[i][j]+=(*img.getFourier())[i][j];
      }
    }
  }
  
  for(int i=0;i<64;i++)
  {
    for(int j=0;j<64;j++)
    {
      //cout<<i<<" "<<j<<" "<<endl;
      stringstream ss;
      ss<<(histref[i][j]/t);
      ss>>fl;
      res+=fl+" ";
    }
  }
  return res;
}

float score(string model, string file)
{
  image img(file);
  vector<vector<double> > histref(64,vector<double>(64));
  stringstream ss(model);
  for(int i=0;i<64;i++)
  {
    for(int j=0;j<64;j++)
    {
      ss>>histref[i][j];
    }
  }
  emd EMD;
  return 1-(EMD.compute(histref,*img.getFourier())/sqrt(50*50+50*50));
}
