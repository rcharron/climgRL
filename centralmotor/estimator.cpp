#include "estimator.h"
#include <stdlib.h>
#include <dlfcn.h>
#include <sstream>


using namespace std;


estimator::estimator(char* library)
{
  handle = dlopen (library, RTLD_LAZY);
    if (!handle) {
        throw dlerror();
    }
    char* error;
    buildmodel = (buildmodel_t)( dlsym(handle, "buildmodel"));
    if (( error = dlerror() ) != NULL)  {
        throw error;
    }
 
    estim = (estim_t)(dlsym(handle, "estim"));
    if (( error = dlerror() ) != NULL)  {
        throw error;
    }
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
  buildmodel(ss.str().c_str());
}

float estimator::scoreof(std::string model, std::string file)
{
  return estim(model.c_str(),file.c_str());
}
