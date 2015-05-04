#ifndef CTEST_H
#define CTEST_H
 
#ifdef __cplusplus
extern "C" {
#endif
 
const char* buildmodel(const char*);
float estim(const char*,const char*);
const char* pre_estim(const char*);
 
#ifdef __cplusplus
}
#endif
 
#endif
