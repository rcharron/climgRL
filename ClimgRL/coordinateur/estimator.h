#ifndef ESTIMATOR_H
#define ESTIMATOR_H
#include <vector>
#include <string>

typedef std::string (*buildmodel_t)(std::string);
typedef std::string (*pre_estim_t)(std::string);
typedef float (*estim_t)(std::string,std::string);

class estimator
{
public:
  estimator(std::string library);
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
