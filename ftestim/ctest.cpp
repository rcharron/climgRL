#include "ctest.h"
#include <vector>
#include <string>
#include <sstream>
#include <iostream>
#include "image.h"


using namespace std;

string buildmodel(vector<string> images)
{
  return "";
}

float estimation(string model,string img)
{
  try
  {
  image i(img);
  i.write("base"+model+".pgm");
  i.dessinfourier("fourier"+model+".pgm");
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
  
  return buildmodel(res).c_str();
}

float estim(const char* modelc, const char* filec)
{
  string model=modelc;
  string file=filec;
  return estimation(modelc,filec);
  
}
