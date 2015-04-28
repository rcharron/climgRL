#include "computer.h"

using namespace std;

computer::computer(vector<string>& files)
{
  for(string f:files)
  {
    try{
      estimator* e=new estimator(("./"+f).c_str());
      estims.push_back(e);
    }
    catch(string s){cout<<s<<endl;}
    //catch(...){}
  }
  
  char *zErrMsg = 0;
   int rc;

   rc = sqlite3_open("estimatormodels.db", &db);

   if( rc )
      throw string("Can't open database: %s\n", sqlite3_errmsg(db));
   
}


computer::~computer()
{
  unsigned int i,t;
  t=estims.size();
  for(i=0;i<t;i++)
    delete estims[i];
  
  sqlite3_close(db);
}


void computer::AddClass(string name, vector< string > files)
{
  unsigned int i,t;
  t=estims.size();
  for(i=0;i<t;i++)
  {
    string res=estims[i]->makemodel(files);
    cout<<estims[i]->getName()<<" : "<<res<<endl;
  }
}
