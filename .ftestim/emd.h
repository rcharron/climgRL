#ifndef EMD_H
#define EMD_H
#include <vector>
//#include <sstream>
#include <string>
#include <map>
#include "Dictionnary.h"
#include <fstream>

class emd 
{
public:
  emd();
  double compute(std::vector<std::vector<double> >& histogramme1,std::vector<std::vector<double> >& histogramme2);
private:
	void EMDConstraintArrival(DictionaryEntry* de,int arrivali, int arrivalj, double amont);
	void EMDConstraintDeparture(DictionaryEntry* de, int departurei, int departurej, double amont);
	void EMDConstraintTransfert1(DictionaryEntry* de);
	void EMDConstraintTransfert2(DictionaryEntry* de);
	void EMDObjective(DictionaryEntry* de);
  double EMDComputeFinalSolution(std::map<int, double> data);
  std::ofstream* os;
};

#endif