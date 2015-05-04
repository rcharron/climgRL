#include "ctest.h"
#include <vector>
#include <string>
#include <sstream>
#include <iostream>
#include "image.h"
#include "basicScoreMaker.h"

using namespace std;


float estimation(string model,string img)
{
  try
  {
  /*image i(img);
  i.write("base"+model+".pgm");
  i.dessinfourier("fourier"+model+".pgm");*/
  return score(model,img);
  }
  catch(string s)
  {
    cout<<s<<endl;
  }
  return 1.0f;
}

const char* buildmodel(const char* listoffiles)
{
  stringstream ss(listoffiles);
  string l;
  vector<string> res;
  while(getline(ss,l))
  {
    if(l!="")
      res.push_back(l);
  }
  
  return model(res).c_str();
}

float estim(const char* modelc, const char* filec)
{
  string model=modelc;
  string file=filec;
  return estimation(modelc,filec);
  
}


const char* pre_estim(const char* filec)
{
  image img(filec);
  stringstream ss;
  for(int i=0;i<64;i++)
  {
    for(int j=0;j<64;j++)
    {
      //cout<<i<<" "<<j<<" "<<endl;
      
      ss<<(*img.getFourier())[i][j]<<" ";
    }
  }
  return ss.str().c_str();
}