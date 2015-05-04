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
  t=static_cast<unsigned int >(estims.size());
  for(i=0;i<t;i++)
    delete estims[i];
  
  sqlite3_close(db);
}



void computer::AddClass(string name, vector< string > files)
{
  unsigned int i,t;
  t=static_cast<unsigned int >(estims.size());
  for(i=0;i<t;i++)
  {
    string sql="DELETE FROM model WHERE estim='"+estims[i]->getName()+"' AND class='"+name+"'";
    sqlite3_exec(db, sql.c_str(), 0, 0, NULL);
    string res=estims[i]->makemodel(files);
    //if(res=="") throw string(name + "res is empty");
    sql="INSERT INTO model(estim,class,model) VALUES('"+estims[i]->getName()+"','"+name+"','"+res+"')";
    char *zErrMsg = 0;
    int rc = sqlite3_exec(db, sql.c_str(), NULL, 0, &zErrMsg);
    if( rc != SQLITE_OK ){
      cout<< "SQL error: "<< zErrMsg<<endl;
      sqlite3_free(zErrMsg);
    }
    
  }
}

void computer::AddClassLazy(string name, vector< string > files)
{
  unsigned int i,t;
  t=static_cast<unsigned int >(estims.size());
  for(i=0;i<t;i++)
  {
    sqlite3_stmt * stmt;
    string sql="SELECT model FROM model WHERE estim='"+estims[i]->getName()+"' AND class='"+name+"'";
    sqlite3_prepare( db, sql.c_str(), -1, &stmt, NULL );
    int result = sqlite3_step( stmt );
    sqlite3_finalize(stmt);
    if(result == SQLITE_ROW)
    {
      continue;
    }
    string res=estims[i]->makemodel(files);
    sql="INSERT INTO model(estim,class,model) VALUES('"+estims[i]->getName()+"','"+name+"','"+res+"')";
    char *zErrMsg = 0;
    int rc = sqlite3_exec(db, sql.c_str(), NULL, 0, &zErrMsg);
    if( rc != SQLITE_OK ){
      cout<< "SQL error: "<< zErrMsg<<endl;
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
      string str=reinterpret_cast<const char*>(sqlite3_column_text( stmt, 0 ));
      string pc=estims[i]->pcof(file);
      res=estims[i]->scoreof(str,pc);
    }
    else
    {
      throw string("Aucun modèle connu de l'estimateur "+estims[i]->getName()+" pour la classe "+classname);
    }
    sqlite3_finalize(stmt);
    return res;
}

float computer::fastscore(string precalc, string classname, unsigned int i)
{
sqlite3_stmt * stmt;
    string sql="SELECT model FROM model WHERE estim='"+estims[i]->getName()+"' AND class='"+classname+"'";
    sqlite3_prepare( db, sql.c_str(), -1, &stmt, NULL );
    int result = sqlite3_step( stmt );
    
    float res=0.0f;
    
    if(result == SQLITE_ROW)
    {
      string str = reinterpret_cast<const char*>(sqlite3_column_text( stmt, 0 ));
      res=estims[i]->scoreof(str,precalc);
    }
    else
    {
      throw string("Aucun modèle connu de l'estimateur "+estims[i]->getName()+" pour la classe "+classname);
    }
    sqlite3_finalize(stmt);
    return res;
}

float computer::score(string file, string classname)
{
  unsigned int i,t,m;
  t=static_cast<unsigned int>(estims.size());
  m=t;
  if(t==0)throw string("Aucun estimateur ne connait cette classe");
  
  float sc=0.0;
  for(i=0;i<t;i++)
  {
    try
    {
      float v=score(file,classname,i);
      sc+=v;
      cout<<"estim"<<i<<" ("<<estims[i]->getName()<<"): "<<v<<endl;
    }
    catch(string s){cout<<s<<endl;m--;}
  }
  
  if(m==0)throw string("Le résultat ne peut pas être calculé");
  
  return sc/static_cast<float>(m);
}

float computer::fastscore(vector< std::string >& precalc, string classname)
{
  unsigned int i,t,m;
  t=static_cast<unsigned int>(estims.size());
  m=t;
  if(t==0)throw string("Aucun estimateur ne connait cette classe");
  
  float sc=0.0;
  for(i=0;i<t;i++)
  {
    try
    {
      float v=fastscore(precalc[i],classname,i);
      sc+=v;
      //cout<<"estim"<<i<<" ("<<estims[i]->getName()<<"): "<<v<<endl;
    }
    catch(string s){cout<<s<<endl;m--;}
  }
  
  if(m==0)throw string("Le résultat ne peut pas être calculé");
  
  return sc/static_cast<float>(m);
}


void computer::signature(vector< string >& classes)
{
  string sign;
  ofstream os("signature.sgn");
  if(os.fail())throw string("La signature n'a pas pu être écrite");
  for(string c:classes)
    os<<c<<" ";
  os.close();
}

vector< float > computer::score(string file)
{
  ifstream is("signature.sgn");
  if(is.fail())string("La signature n'a pas pu être lue");
  
  vector<string> precalc;
  unsigned int i,t;
  t=static_cast<unsigned int>(estims.size());
  for(i=0;i<t;i++)
  {
    precalc.push_back(estims[i]->pcof(file));
  }
  
  string classname;
  vector< float > res;
  try
  {
    while(is>>classname)
    {
      float s=fastscore(precalc,classname);
      res.push_back(s);
    }
  }
  catch(string s){cout<<s<<endl;}
  return res;
}


vector< string > computer::match(string file)
{
  ifstream is("signature.sgn");
  if(is.fail())string("La signature n'a pas pu être lue");
  
  vector<string> precalc;
  unsigned int i,t;
  t=static_cast<unsigned int>(estims.size());
  for(i=0;i<t;i++)
  {
    precalc.push_back(estims[i]->pcof(file));
  }
  
  string classname;
  vector< string > res;
  try
  {
    while(is>>classname)
    {
      float s=fastscore(precalc,classname);
      if(s>0.9f)
      {
	stringstream ss;
	ss<<classname<<" : "<<s;
	res.push_back(ss.str());
      }
      
      
    }
  }
  catch(string s){cout<<s<<endl;}
  return res;

}


string computer::guess(string file)
{
  ifstream is("signature.sgn");
  if(is.fail())string("La signature n'a pas pu être lue");
  
  vector<string> precalc;
  unsigned int i,t;
  t=static_cast<unsigned int>(estims.size());
  for(i=0;i<t;i++)
  {
    string e=estims[i]->pcof(file);
    precalc.push_back(e);
  }
  
  string classname;
  string res;
  float sc=0.0f;
  try
  {
    while(is>>classname)
    {
      float s=fastscore(precalc,classname);
      if(s>sc)
      {
	sc=s;
	res=classname;
      }
      
      
    }
  }
  catch(string s){cout<<s<<endl;}
  return res;

}
