#ifndef BASICSCOREMAKER_H
#define BASICSCOREMAKER_H

#include <vector>
#include <string>
#include <sstream>

std::string model(std::vector<float>& mean,std::vector<float>& var);

float score(std::string model, float mean,float var);

#endif