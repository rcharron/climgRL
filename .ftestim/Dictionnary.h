#ifndef DICTIONARY_H
#define DICTIONARY_H
#include <vector>
#include "DictionaryEntry.h"

class Dictionary
{
public:
	Dictionary();
	~Dictionary();
	void SetObjective(DictionaryEntry& objective);
	void AddEntry(DictionaryEntry entry);

	DictionaryEntry* GetObjective();
	DictionaryEntry* AddNewEntry();


	void RunSimplex();

	void Clear();

	enum Status{ UNBOUNDED, EMPTY, UNDERMINE, ONEPOINT };
	std::map<int, double> GetSolution();
	std::map<int, double> GetAsymptote();//If status is unbounded
	Status GetStatus();
private:
	bool Step();
	bool FirstSolve();
	void StrangeFirstStep();
	int infvar;
	int cnumber;

	Status status;
	std::pair<double, std::vector<DictionaryEntry>::iterator> FindConstraintOn(int variable);
	std::vector<DictionaryEntry> data;
	DictionaryEntry objective;
};



#endif