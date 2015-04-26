#ifndef DICTIONARYENTRY_H
#define DICTIONARYENTRY_H
#include <map>
#include <unordered_map>
#include <string>


class DictionaryEntry
{
public:
	DictionaryEntry();
	~DictionaryEntry();
	void AddTerm(std::string variable, double coefficiant);
	void AddConstant(double coefficiant);
	void SetWord(std::string word);
	void Clear();
	void Leaves(std::string variableentering);
	void EnterAndLeaves(DictionaryEntry enters);
	void Simplify();

	double CoefficientOf(std::string variable);
	std::string Name();
	std::unordered_map<std::string, double>::const_iterator GetInnersValues();
	std::unordered_map<std::string, double>::const_iterator GetInnersValuesEnd();


	void osoperator(std::ostream& os);
private:
	std::unordered_map<std::string, double> data;//Set name of constant = 42
	std::string word;
};

std::ostream& operator<<(std::ostream& os, DictionaryEntry);

#endif
