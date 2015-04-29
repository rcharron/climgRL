#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>
#include <dirent.h>
#include <functional>
#include <iostream>
#include "estimator.h"
#include <sstream>
#include <regex>
#include "computer.h"


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

vector<string> listclass(string where)
{
  vector<string> res;
  DIR *dir;
  struct dirent *ent;
  regex r("(.*)-.*");
  if ((dir = opendir (where.c_str())) != NULL) 
  {
    while ((ent = readdir (dir)) != NULL) 
    {
      string entry=ent->d_name;
      smatch m;
      if(regex_search(entry,m,r))
      {
	if(find(res.begin(),res.end(),m[1])==res.end())
	  res.push_back(m[1]);
      }
    }
  closedir (dir);
  } 
  return res;
}


vector<string> findfiles(string where, string reg)
{
  regex r(reg);
  vector<string> res;
  DIR *dir;
  struct dirent *ent;
  if ((dir = opendir (where.c_str())) != NULL) 
  {
    while ((ent = readdir (dir)) != NULL) 
    {
      string entry=ent->d_name;
      if(regex_match(entry, r))
      {
	res.push_back(where+entry);
      }
    }
  closedir (dir);
  } 
  return res;
}
 
int main(int argc,char**argv){
  if(argc>1)
  {
    string action=argv[1];
    if(action=="learn")
    {
      if(argc!=4)
      {
	cout<<"Usage ./centralmotor learn nomclass dossier"<<endl;
	return 0;
      }
      string classname=argv[2];
      string directory=argv[3];
      if(directory.back()!='/')
	 directory+='/';
      vector<string> classfiles=findfiles(directory,classname+".*\\.pgm");
      vector<string> l=lookup(".");
      computer c(l);
      c.AddClass(classname,classfiles);
      return 0;
    }
    if(action=="learnall")
    {
      if(argc!=3)
      {
	cout<<"Usage ./centralmotor learnall dossier"<<endl;
	return 0;
      }
      string directory=argv[2];
      if(directory.back()!='/')
	 directory+='/';
      vector<string> lc=listclass("../database/");
      vector<string> l=lookup(".");
      computer c(l);
      unsigned int i,t;
      t=lc.size();
      for(i=0;i<t;i++)//string classname:lc)
      {
	int progress=(50*i)/t;
	cout<<"\r[";
	for(int w=0;w<progress;w++)cout<<"=";
	cout<<">";
	for(int w=0;w<50-progress;w++)cout<<" ";
	cout<<"] ("<<i<<"/"<<t<<")"<<flush;
	vector<string> classfiles=findfiles(directory,lc[i]+".*\\.pgm");
	c.AddClass(lc[i],classfiles);
      }
      cout<<"\r[===================================================] ("<<t<<"/"<<t<<")"<<endl;
      return 0;
    }
  }
  

  
  vector<string> l=lookup(".");
  for(string s:l)
    cout<<s<<endl;
  /*try{
  estimator e("./libftestim.so");
  for(int i=1;i<10;i++)
  {
    stringstream ss,ss2;
    ss<<"../database/bat-"<<i<<".pgm";
    ss2<<i;
    e.scoreof(ss2.str(),ss.str());
  }
  }
  catch(char* err)
  {
    cout<<err<<endl;
  }*/
  computer c(l);
  vector<string> im;
  
  for(int i=1;i<10;i++)
  {
    stringstream ss;
    //ss<<"../database/bat-"<<i<<".pgm";
    ss<<"../database/bat-"<<i<<".pgm";
    im.push_back(ss.str());
  }
  c.AddClass("bat",im);
    return 0;
}
