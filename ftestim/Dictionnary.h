#ifndef DICTIONARY_H
#define DICTIONARY_H
#include <vector>
#include "DictionaryEntry.h"

class Dictionary
{
public:
	Dictionary();
	~Dictionary();
	void SetObjective(DictionaryEntry objective);
	void AddEntry(DictionaryEntry entry);

	void RunSimplex();

	void Clear();

	enum Status{ UNBOUNDED, EMPTY, UNDERMINE, ONEPOINT };
	std::map<std::string, double> GetSolution();
	std::map<std::string, double> GetAsymptote();//If status is unbounded
	Status GetStatus();
private:
	//private:
	bool Step();

	std::string infvar;

	Status status;
	std::pair<double, std::vector<DictionaryEntry>::iterator> FindConstraintOn(std::string variable);
	std::vector<DictionaryEntry> data;
	DictionaryEntry objective;
};



#endif