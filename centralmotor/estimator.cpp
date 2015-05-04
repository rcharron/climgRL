#include "estimator.h"
#include <stdlib.h>
#include <dlfcn.h>
#include <sstream>


using namespace std;


estimator::estimator(const char* library)
{
  handle = dlopen (library, RTLD_LAZY);
    if (!handle) {
        throw string(dlerror());
    }
    char* error;
    buildmodel = (buildmodel_t)( dlsym(handle, "buildmodel"));
    if (( error = dlerror() ) != NULL)  {
        throw string(error);
    }
 
    estim = (estim_t)(dlsym(handle, "estim"));
    if (( error = dlerror() ) != NULL)  {
        throw string(error);
    }
    
    pre_estim = (pre_estim_t)(dlsym(handle, "pre_estim"));
    if (( error = dlerror() ) != NULL)  {
        throw string(error);
    }
    
    name=library;
}

estimator::~estimator()
{
  dlclose(handle);
}


std::string estimator::makemodel(std::vector< std::string > files)
{
  stringstream ss;
  for(string s:files)
    ss<<s<<"\n";
  return buildmodel(ss.str().c_str());
}

float estimator::scoreof(std::string model, std::string pc)
{
  return estim(model.c_str(),pc.c_str());
}

string estimator::pcof(string file)
{
  return string(pre_estim(file.c_str()));
}


string estimator::getName()
{
  return name;
}
