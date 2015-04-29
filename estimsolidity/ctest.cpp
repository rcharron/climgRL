#include "ctest.h"
#include <vector>
#include <string>
#include <sstream>
#include <iostream>
#include "Estimateurs/basicScoreMaker.h"
#include "MetaImage.h"
#include "Estimateurs/Solidity.h"

using namespace std;

const char* buildmodel(vector<string> listoffiles)
{
  vector<float> res;
  for(string f:listoffiles)
  {
    MetaImage img(f);
    res.push_back(Solidity(img));
  }
  
  return model(res).c_str();
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
  
  return buildmodel(res);
}

float estim(const char* modelc, const char* pcc)
{
  string model=modelc;
  string pc=pcc;
  stringstream ss(pc);
  float sc;
  ss>>sc;
  return score(modelc,sc);
  
}

const char* pre_estim(const char* filec)
{
  string file=filec;
  MetaImage img(filec);
  stringstream ss;
  ss<<(float)Solidity(img);
  return ss.str().c_str();
}