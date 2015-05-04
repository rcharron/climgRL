#ifndef BASICSCOREMAKER_H
#define BASICSCOREMAKER_H

#include <vector>
#include <string>
#include <sstream>

std::string model(std::vector<std::string> files);

float score(std::string model, std::string file);

#endif