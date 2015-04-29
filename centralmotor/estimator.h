#ifndef ESTIMATOR_H
#define ESTIMATOR_H
#include <vector>
#include <string>

typedef const char* (*buildmodel_t)(const char*);
typedef const char* (*pre_estim_t)(const char*);
typedef float (*estim_t)(const char*,const char*);

class estimator
{
public:
  estimator(const char* library);
  ~estimator();
  std::string makemodel(std::vector<std::string> files);
  float scoreof(std::string model,std::string pc);
  std::string pcof(std::string file);
  std::string getName();
private:
  std::string name;
  void *handle;
  buildmodel_t buildmodel;
  estim_t estim;
  pre_estim_t pre_estim;
};


#endif