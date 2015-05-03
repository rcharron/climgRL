#ifndef COMPUTER_H
#define COMPUTER_H
#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>
#include <dirent.h>
#include <functional>
#include <iostream>
#include "estimator.h"
#include <sstream>
#include <fstream>
#include "sqlite3.h"

class computer
{
public:
  computer(std::vector<std::string>& files);
  ~ computer();
  void AddClass(std::string name,std::vector<std::string> files);
  void AddClassLazy(std::string name,std::vector<std::string> files);
  float score(std::string file, std::string classname);
  std::vector<float> score(std::string file);
  std::vector<std::string> guess(std::string file);
  void signature(std::vector<std::string>& classes);
private:
  float score(std::string file, std::string classname, unsigned int estimnb);
  float fastscore(std::string precalc, std::string classname, unsigned int estimnb);
  float fastscore(std::vector<std::string>& precalc, std::string classname);
  std::vector<estimator*> estims;
  sqlite3 *db;
};


#endif