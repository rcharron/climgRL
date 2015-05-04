#include "ctest.h"
#include <vector>
#include <string>
#include <sstream>
#include <iostream>
#include "Estimateurs/basicScoreMaker.h"
#include "MetaImage.h"
#include "Estimateurs/Solidity.h"
#include <iostream>

using namespace std;

string buildmodel(vector<string> listoffiles)
{
  vector<float> res;
  for(string f:listoffiles)
  {
    MetaImage img(f);
//    std::cout << f << std::endl;
    res.push_back(static_cast<float>(Solidity(img)));
  }
  
  return model(res);
}

string buildmodel(string listoffiles)
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

float estim(string model, string pc)
{
  stringstream ss(pc);
  float sc;
  ss>>sc;
  return score(model,sc);
  
}

string pre_estim(string file)
{
  MetaImage img(file);
  stringstream ss;
  ss<<(float)Solidity(img)<<" ";
  return ss.str();
}
