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

string pre_estimation(string img)
{
  image i(img);
  stringstream ss;
  ss<<i.getNormMean()<<" "<<i.getNormVar();
  return ss.str();
}


float estimation(string model,string pc)
{
  try
  {
  stringstream ss(pc);
  float n,v;
  ss>>n>>v;
  return score(model,n,v);
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

float estim(const char* modelc, const char* precalc)
{
  string model=modelc;
  string pc=precalc;
  return estimation(modelc,pc);
  
}

const char* pre_estim(const char* file)
{
  return pre_estimation(file).c_str();
}
