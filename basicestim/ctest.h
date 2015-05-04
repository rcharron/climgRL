#ifndef CTEST_H
#define CTEST_H

#include <string>
 
#ifdef __cplusplus
extern "C" {
#endif
 
std::string buildmodel(std::string);
float estim(std::string,std::string);
std::string pre_estim(std::string);
 
#ifdef __cplusplus
}
#endif
 
#endif
