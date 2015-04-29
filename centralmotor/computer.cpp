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
   
   string sql="CREATE TABLE IF NOT EXISTS model(estim TEXT,class TEST,model TEXT)";
   
   rc = sqlite3_exec(db, sql.c_str(), 0, 0, &zErrMsg);
   if( rc != SQLITE_OK ){
   	string res="SQL error:";
	res+= zErrMsg;
      sqlite3_free(zErrMsg);
      sqlite3_close(db);
      throw res;
   }
   
}


computer::~computer()
{
  unsigned int i,t;
  t=estims.size();
  for(i=0;i<t;i++)
    delete estims[i];
  
  sqlite3_close(db);
}

static int callback(void *NotUsed, int argc, char **argv, char **azColName){
   int i;
   for(i=0; i<argc; i++){
      printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
   }
   printf("\n");
   return 0;
}


void computer::AddClass(string name, vector< string > files)
{
  unsigned int i,t;
  t=estims.size();
  for(i=0;i<t;i++)
  {
    string sql="DELETE FROM model WHERE estim='"+estims[i]->getName()+"' AND class='"+name+"'";
    sqlite3_exec(db, sql.c_str(), 0, 0, NULL);
    string res=estims[i]->makemodel(files);
    sql="INSERT INTO model(estim,class,model) VALUES('"+estims[i]->getName()+"','"+name+"','"+res+"')";
    char *zErrMsg = 0;
    int rc = sqlite3_exec(db, sql.c_str(), callback, 0, &zErrMsg);
    if( rc != SQLITE_OK ){
      fprintf(stderr, "SQL error: %s\n", zErrMsg);
      sqlite3_free(zErrMsg);
    }
    
  }
}
