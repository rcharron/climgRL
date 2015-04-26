#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>
#include <dirent.h>
#include <functional>
#include <iostream>
#include "estimator.h"


using namespace std;

bool hasEnding (std::string &fullString, std::string ending) {
    if (fullString.length() >= ending.length()) {
        return (0 == fullString.compare (fullString.length() - ending.length(), ending.length(), ending));
    } else {
        return false;
    }
}
 
vector<string> lookup(string where)
{
  vector<string> res;
  DIR *dir;
  struct dirent *ent;
  if ((dir = opendir (where.c_str())) != NULL) 
  {
    while ((ent = readdir (dir)) != NULL) 
    {
      string entry=ent->d_name;
      if(hasEnding(entry,".so"))
	res.push_back(entry);
    }
  closedir (dir);
  } 
  return res;
}
 
int main(int argc,char**argv){
  vector<string> l=lookup(".");
  for(string s:l)
    cout<<s<<endl;
  try{
  estimator e("./libftestim.so");
  e.scoreof("","../database/bat-1.pgm");
  }
  catch(char* err)
  {
    cout<<err<<endl;
  }
    return 0;
}