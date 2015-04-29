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


float computer::score(string file, string classname, unsigned int i)
{
  sqlite3_stmt * stmt;
    string sql="SELECT model FROM model WHERE estim='"+estims[i]->getName()+"' AND class='"+classname+"'";
    sqlite3_prepare( db, sql.c_str(), -1, &stmt, NULL );
    int result = sqlite3_step( stmt );
    
    float res=0.0f;
    
    if(result == SQLITE_ROW)
    {
      string str = (char *)(sqlite3_column_text( stmt, 0 ));
      res=estims[i]->scoreof(str,file);
    }
    else
    {
      throw string("no model provided for estimator "+estims[i]->getName()+"on class "+classname);
    }
    sqlite3_finalize(stmt);
    return res;
}
