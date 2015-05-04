#include "ctest.h"
#include <vector>
#include <string>
#include <sstream>
#include <iostream>
#include "Estimateurs/basicScoreMaker.h"
#include "MetaImage.h"
#include "Estimateurs/Eccentricity.h"
#include <iostream>

using namespace std;

std::string buildmodel(vector<string> listoffiles)
{
  vector<float> res;
  for(string f:listoffiles)
  {
    MetaImage img(f);
//    std::cout << f << std::endl;
    res.push_back(static_cast<float>(Eccentricity(img)));
  }
  
  return model(res);
}

std::string buildmodel(std::string listoffiles)
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

float estim(std::string modelc, std::string pc)
{
  stringstream ss(pc);
  float sc;
  ss>>sc;
  return score(modelc,sc);
  
}

std::string pre_estim(std::string file)
{
  MetaImage img(file);
  stringstream ss;
  ss<<(float)Eccentricity(img)<<" ";
  return ss.str();
}
