#include "ctest.h"
#include <vector>
#include <string>
#include <sstream>
#include <iostream>
#include "basicScoreMaker.h"
#include "MetaImage.h"
#include <iostream>

using namespace std;

int SpineLong(string file)
{
  MetaImage i(file);
  MetaImage i2=i.getNormalized();
  i2.iterRemoveNoise();
  i2.Fill();
  return i2.spineLength();
}

string buildmodel(vector<string> listoffiles)
{
  vector<float> res;
  for(string f:listoffiles)
  {
    try{
      int l=SpineLong(f);
      //cout<<f<<" "<<l<<endl;
//    std::cout << f << std::endl;
      res.push_back(static_cast<float>(l));
    }
    catch(std::string s)
    {
      cout<<"fichier "<<f<<" "<<s<<endl;
    }
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
  int sc;
  ss>>sc;
  return score(model,static_cast<float>(sc));
  
}

string pre_estim(string file)
{
  stringstream ss;
  ss<<SpineLong(file)<<" ";
  return ss.str();
}
