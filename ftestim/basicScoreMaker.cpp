#include "basicScoreMaker.h"
#include <cmath>
#include "image.h"

using namespace std;

string model(vector< string > files)
{
  unsigned int t,i;
  t=files.size();
  vector<vector<double> > histref(64,vector<double>(64));
  for(i=0;i<t;i++)
  {
    image img(files[i]);
    for(int i=0;i<64;i++)
    {
      for(int j=0;j<64;j++)
      {
	histref[i][j]+=(*img.getFourier())[i][j];
      }
    }
  }
  stringstream ss;
  for(int i=0;i<64;i++)
  {
    for(int j=0;j<64;j++)
    {
      ss<<(histref[i][j]/t)<<" ";
    }
  }
  return ss.str();
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
  return EMD.compute(histref,*img.getFourier());
}
