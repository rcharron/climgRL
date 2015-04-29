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
#include "sqlite3.h"

class computer
{
public:
  computer(std::vector<std::string>& files);
  ~ computer();
  void AddClass(std::string name,std::vector<std::string> files);
  float score(std::string file, std::string classname);
private:
  float score(std::string file, std::string classname, unsigned int estimnb);
  std::vector<estimator*> estims;
  sqlite3 *db;
};


#endif