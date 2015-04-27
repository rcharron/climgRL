#include "ctest.h"
#include <vector>
#include <string>
#include <sstream>
#include <iostream>
#include <limits>
#include "image.h"
#include "basicScoreMaker.h"


using namespace std;

string buildmodel(vector<string> images)
{
  vector<float> mean;
  vector<float> var;
  for(string f:images)
  {
    image i(f);
    mean.push_back(i.getNormMean());
    var.push_back(i.getNormVar());
  }
  return model(mean,var);
}

float estimation(string model,string img)
{
  try
  {
  image i(img);
  return score(model,i.getNormMean(),i.getNormVar());
  //return i.getDiam();
  }
  catch(string s)
  {
    cout<<s<<endl;
    return std::numeric_limits<float>::infinity();
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
  
  return buildmodel(res).c_str();
}

float estim(const char* modelc, const char* filec)
{
  string model=modelc;
  string file=filec;
  return estimation(modelc,filec);
  
}
