#include "DictionaryEntry.h"


DictionaryEntry::DictionaryEntry()
{
}


DictionaryEntry::~DictionaryEntry()
{
}

void DictionaryEntry::AddTerm(std::string variable, double coefficiant)
{
	data[variable] = coefficiant;
}

void DictionaryEntry::AddConstant(double coefficiant)
{
	data["42"] = coefficiant;
}

void DictionaryEntry::SetWord(std::string w)
{
	word = w;
}

void DictionaryEntry::Clear()
{
	data.clear();
}

void DictionaryEntry::Leaves(std::string variableentering)
{
	double coeff = -1/data[variableentering];
	if (coeff==0.0)throw std::string(variableentering+" is not in the dictionnary entry");

	data[word] = -1;
	data.erase(variableentering);
	for (auto it = data.begin(); it != data.end(); ++it)
		it->second *= coeff;
	word = variableentering;
}

void DictionaryEntry::EnterAndLeaves(DictionaryEntry enters)
{
	auto it = data.find(enters.word);
	if (it == data.end())return;
	double coeff = it->second;
	data.erase(it);
	if (coeff==0.0)return;
	for (it = enters.data.begin(); it != enters.data.end(); ++it)
	{
		data[it->first] += it->second*coeff;
	}
}

void DictionaryEntry::Simplify()
{
	for (auto it = data.begin(); it != data.end();)
		if (it->second==0)
		{
			auto itold = it;
			it++;
			data.erase(itold);
		}
		else
			++it;
}



double DictionaryEntry::CoefficientOf(std::string variable)
{
	auto it = data.find(variable);
	if (it == data.end())return 0;
	return it->second;
}

std::string DictionaryEntry::Name()
{
	return word;
}

std::unordered_map<std::string, double>::const_iterator DictionaryEntry::GetInnersValues()
{
	return data.begin();
}
std::unordered_map<std::string, double>::const_iterator DictionaryEntry::GetInnersValuesEnd()
{
	return data.end();
}
