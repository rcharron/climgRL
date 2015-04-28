#ifndef EMD_H
#define EMD_H
#include <vector>
#include <sstream>
#include <string>
#include <map>
#include "Dictionnary.h"

class emd 
{
public:
  double compute(std::vector<std::vector<double> >& histogramme1,std::vector<std::vector<double> >& histogramme2);
private:
  DictionaryEntry EMDConstraintArrival(int arrivali,int arrivalj,double amont);
  DictionaryEntry EMDConstraintDeparture(int departurei,int departurej,double amont);
  DictionaryEntry EMDConstraintTransfert1();
  DictionaryEntry EMDConstraintTransfert2();
  DictionaryEntry EMDObjective();
  double EMDComputeFinalSolution(std::map<std::string, double> data);
};

#endif