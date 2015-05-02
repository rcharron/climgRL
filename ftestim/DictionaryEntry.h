#ifndef DICTIONARYENTRY_H
#define DICTIONARYENTRY_H
#include <map>
#include <unordered_map>
#include <string>

#define mymap unordered_map


class DictionaryEntry
{
public:
	DictionaryEntry();
	~DictionaryEntry();
	void AddTerm(int variable, double coefficiant);
	void AddConstant(double coefficiant);
	void SetWord(int word);
	void Clear();
	void Leaves(int variableentering);
	void EnterAndLeaves(DictionaryEntry enters);
	void Simplify();

	double CoefficientOf(int variable);
	int Name();
	std::mymap<int, double>::const_iterator GetInnersValues();
	std::mymap<int, double>::const_iterator GetInnersValuesEnd();


	void osoperator(std::ostream& os);
private:
	std::mymap<int, double> data;//Set name of constant = 42
	int word;
};

std::ostream& operator<<(std::ostream& os, DictionaryEntry);

#endif
