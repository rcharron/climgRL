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
#include <thread>
#include <mutex>


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

mutex accessliste;

void learnClassThread(unsigned int *thei, string directory,vector<string>* lc,computer* c)
{
  unsigned int i,t;
  t=static_cast<unsigned int >(lc->size());
  
  accessliste.lock();
  i=*thei;
  (*thei)++;
  int progress=(50*i)/t;
  cout<<"\r[";
  for(int w=0;w<progress;w++)cout<<"=";
  cout<<">";
  for(int w=0;w<50-progress;w++)cout<<" ";
  cout<<"] ("<<i<<"/"<<t<<") "<<flush;
  accessliste.unlock();
  while(i<t)
  {
	vector<string> classfiles=findfiles(directory,(*lc)[i]+"-.*\\.pgm");
	c->AddClassLazy((*lc)[i],classfiles);
	accessliste.lock();
	i=*thei;
	(*thei)++;
	progress=(50*i)/t;
	cout<<"\r[";
	for(int w=0;w<progress;w++)cout<<"=";
	cout<<">";
	for(int w=0;w<50-progress;w++)cout<<" ";
	cout<<"] ("<<i<<"/"<<t<<") "<<flush;
	accessliste.unlock();
  }
}
 
void launchThreadPoll(unsigned int thnum, string directory)
{
  if(directory.back()!='/')
	 directory+='/';
      vector<string> lc=listclass(directory);
      vector<string> l=lookup(".");
      computer c(l);
      unsigned int i=0;
      c.signature(lc);
      vector<std::thread> t(thnum);
      for(unsigned int ind=0;ind<thnum;ind++)
      {
	t[ind]=thread(learnClassThread,&i,directory,&lc,&c);
      }
      for(unsigned int ind=0;ind<thnum;ind++)
	t[ind].join();
      cout<<"\r[===================================================] (c'est fini)"<<endl;
      
}
 
int main(int argc,char**argv){
  if(argc>1)
  {
    string action=argv[1];
    if(action=="learn")
    {
      if(argc!=4)
      {
	cout<<"Usage ./ClimgRL learn nomclass dossier"<<endl;
	return 0;
      }
      string classname=argv[2];
      string directory=argv[3];
      if(directory.back()!='/')
	 directory+='/';
      vector<string> classfiles=findfiles(directory,classname+"-.*\\.pgm");
      vector<string> l=lookup(".");
      computer c(l);
      c.AddClass(classname,classfiles);
      return 0;
    }
    if(action=="learnall")
    {
      if(argc!=3)
      {
	cout<<"Usage ./ClimgRL learnall dossier"<<endl;
	return 0;
      }
      string directory=argv[2];
      if(directory.back()!='/')
	 directory+='/';
      vector<string> lc=listclass(directory);
      vector<string> l=lookup(".");
      computer c(l);
      unsigned int i,t;
      t=static_cast<unsigned int >(lc.size());
      c.signature(lc);
      for(i=0;i<t;i++)
      {
	int progress=(50*i)/t;
	cout<<"\r[";
	for(int w=0;w<progress;w++)cout<<"=";
	cout<<">";
	for(int w=0;w<50-progress;w++)cout<<" ";
	cout<<"] ("<<i<<"/"<<t<<")"<<flush;
	vector<string> classfiles=findfiles(directory,lc[i]+"-.*\\.pgm");
	c.AddClass(lc[i],classfiles);
      }
      cout<<"\r[===================================================] ("<<t<<"/"<<t<<")"<<endl;
      return 0;
    }

    if(action=="learnlazy")
    {
      if(argc!=3)
      {
	cout<<"Usage ./ClimgRL learnlazy dossier"<<endl;
	return 0;
      }
      string directory=argv[2];
      if(directory.back()!='/')
	 directory+='/';
      vector<string> lc=listclass(directory);
      vector<string> l=lookup(".");
      computer c(l);
      unsigned int i,t;
      t=static_cast<unsigned int >(lc.size());
      c.signature(lc);
      for(i=0;i<t;i++)
      {
	int progress=(50*i)/t;
	cout<<"\r[";
	for(int w=0;w<progress;w++)cout<<"=";
	cout<<">";
	for(int w=0;w<50-progress;w++)cout<<" ";
	cout<<"] ("<<i<<"/"<<t<<") : "<<lc[i]<<"          "<<flush;
	vector<string> classfiles=findfiles(directory,lc[i]+"-.*\\.pgm");
	c.AddClassLazy(lc[i],classfiles);
      }
      cout<<"\r[===================================================] ("<<t<<"/"<<t<<")"<<endl;
      return 0;
    }
    
    if(action=="multilearnlazy")
    {
      if(argc!=4)
      {
	cout<<"Usage ./ClimgRL multilearnlazy nbthreads dossier"<<endl;
	return 0;
      }
      string directory=argv[3];
      stringstream ss(argv[2]);
      unsigned int i;
      ss>>i;
      if(!(i>0&&i<24))
      {
	cout<<"le nombre de threads devrait être entre 1 et 23"<<endl;
	return -1;
      }
      launchThreadPoll(i,directory);
      return 0;
    }
    
    if(action=="estim")
    {
      if(argc>4)
      {
	cout<<"Usage ./ClimgRL estim nomclass fichier"<<endl;
	return 0;
      }
      if(argc==4)
      {
	string classname=argv[2];
	string file=argv[3];
	
	float res;
	
	vector<string> l=lookup(".");
	computer c(l);
	try{
	  res=c.score(file,classname);
	}
	catch(string s){cout<<s<<endl;return -1;}
	cout<<"Le score est "<<res<<endl;
	return 0;
      }
      if(argc==3)
      {
	string file=argv[2];
      
	vector<string> res;
	
	vector<string> l=lookup(".");
	computer c(l);
	try{
	  res=c.match(file);
	}
	catch(string s){cout<<s<<endl;return -1;}
	cout<<"Les correspondances trouvées sont : "<<endl;
	for(string s:res)
	  cout<<s<<endl;
	return 0;
      }
    }
    if(action=="guess")
    {
      if(argc!=3)
      {
	cout<<"Usage ./ClimgRL guess fichier"<<endl;
	return 0;
      }
      string file=argv[2];
      
	string res;
	
	vector<string> l=lookup(".");
	computer c(l);
	try{
	  res=c.guess(file);
	}
	catch(string s){cout<<s<<endl;return -1;}
	cout<<res<<endl;
	return 0;
      
    }

    if(action=="sign")
    {
      if(argc!=3)
      {
	cout<<"Usage ./ClimgRL sign fichier"<<endl;
	return 0;
      }
      if(argc==3)
      {
	string file=argv[2];
      
	vector<float> res;
	
	vector<string> l=lookup(".");
	computer c(l);
	try{
	  res=c.score(file);
	}
	catch(string s){cout<<s<<endl;return -1;}
	cout<<"La signauture est (";
	for(float s:res)
	  cout<<s<<"|";
	cout<<"\b)"<<endl;
	return 0;
      }
    }
    
    if(action=="simil")
    {
      if(argc!=4)
      {
	cout<<"Usage ./ClimgRL simil fichier1 fichier2"<<endl;
	return 0;
      }
      if(argc==4)
      {
	string file=argv[2];
	string file2=argv[3];
      
	vector<float> res,res2;
	
	vector<string> l=lookup(".");
	computer c(l);
	try{
	  res=c.score(file);
	  res2=c.score(file2);
	}
	catch(string s){cout<<s<<endl;return -1;}
	if(res.size()!=res2.size())
	{
	  cout<<"Erreur de signature"<<endl;
	  return -1;
	}
	unsigned int i,t;
	t=res.size();
	float diff=0.0f;
	for(i=0;i<t;i++)
	  diff+=abs(res[i]-res2[i]);
	diff/=t;
	cout<<(1.0f-diff)<<endl;
	return 0;
      }
    }
  }
  

  /*-
  vector<string> l=lookup(".");
  for(string s:l)
    cout<<s<<endl;
  try{
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
  }
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
   / return 0;*/
  cout<<"      ___           ___                   ___           ___           ___           ___  "<<endl;
  cout<<"     /\\  \\         /\\__\\      ___        /\\__\\         /\\  \\         /\\  \\         /\\__\\ "<<endl;
  cout<<"    /::\\  \\       /:/  /     /\\  \\      /::|  |       /::\\  \\       /::\\  \\       /:/  / "<<endl;
  cout<<"   /:/\\:\\  \\     /:/  /      \\:\\  \\    /:|:|  |      /:/\\:\\  \\     /:/\\:\\  \\     /:/  /  "<<endl;
  cout<<"  /:/  \\:\\  \\   /:/  /       /::\\__\\  /:/|:|__|__   /:/  \\:\\  \\   /::\\~\\:\\  \\   /:/  /   "<<endl;
  cout<<" /:/__/ \\:\\__\\ /:/__/     __/:/\\/__/ /:/ |::::\\__\\ /:/__/_\\:\\__\\ /:/\\:\\ \\:\\__\\ /:/__/    "<<endl;
  cout<<" \\:\\  \\  \\/__/ \\:\\  \\    /\\/:/  /    \\/__/~~/:/  / \\:\\  /\\ \\/__/ \\/_|::\\/:/  / \\:\\  \\    "<<endl;
  cout<<"  \\:\\  \\        \\:\\  \\   \\::/__/           /:/  /   \\:\\ \\:\\__\\      |:|::/  /   \\:\\  \\   "<<endl;
  cout<<"   \\:\\  \\        \\:\\  \\   \\:\\__\\          /:/  /     \\:\\/:/  /      |:|\\/__/     \\:\\  \\  "<<endl;
  cout<<"    \\:\\__\\        \\:\\__\\   \\/__/         /:/  /       \\::/  /       |:|  |        \\:\\__\\ "<<endl;
  cout<<"     \\/__/         \\/__/                 \\/__/         \\/__/         \\|__|         \\/__/ "<<endl;
  cout<<endl;
  cout<<"     ==============================================================================="<<endl;
  cout<<"          ========    ©  Laureline Pinault & Raphaël Charrondière      ========     "<<endl;
  cout<<"               ===========================================================          "<<endl;
  cout<<endl<<endl;
  cout<<"Usage :"<<endl<<endl;
  cout<<"Apprendre les classes d'images :"<<endl;
  cout<<"--> Juste une classe : ./ClimgRL learn nomClasse cheminVersDossierImage"<<endl;
  cout<<"--> Toute les classes : ./ClimgRL learnall cheminVersDossierImage"<<endl;
  cout<<"--> Tout ce qui n'a pas été appris : ./ClimgRL learnlazy cheminVersDossierImage"<<endl<<endl;
  cout<<"Estimer :"<<endl;
  cout<<"--> Score pour une clase : ./ClimgRL estim nomClasse fichier"<<endl;
  cout<<"--> Correspondances vraisemblables : ./ClimgRL estim fichier"<<endl;
  cout<<"--> Meilleure correspondance : ./ClimgRL guess fichier"<<endl<<endl;
  cout<<"Signer :"<<endl;
  cout<<"--> Signature : ./ClimgRL sign fichier"<<endl<<endl;
  cout<<"Comparer :"<<endl;
  cout<<"--> Facteur de similarité: ./ClimgRL simil fichier1 fichier2"<<endl<<endl;
  
  
  
  return 0;
}
