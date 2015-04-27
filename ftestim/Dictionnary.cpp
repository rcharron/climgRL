#include "Dictionnary.h"
#include <limits>



Dictionary::Dictionary()
{
	status = Status::UNDERMINE;
}


Dictionary::~Dictionary()
{
}

void Dictionary::SetObjective(DictionaryEntry obj)
{
	objective = obj;
}

void Dictionary::AddEntry(DictionaryEntry entry)
{
	data.push_back(entry);
}


std::pair<double, std::vector<DictionaryEntry>::iterator> Dictionary::FindConstraintOn(std::string variable)
{
	double c=1;
	auto pos = data.begin();
	for (auto it = data.begin(); it != data.end(); it++)
	{
		double l = it->CoefficientOf("42");
		double d = it->CoefficientOf(variable);
		if (l>=0 && d>=0)continue;
		if (l<0)throw std::string("First step not implemented yet");//SHOULD NEVER OCCURS
		l = -l / d;
		if (l < c)
		{
			c = l;
			pos = it;
		}
	}
	return std::make_pair(c,pos);
}

bool Dictionary::Step()
{
	for (auto itvar = objective.GetInnersValues(); itvar != objective.GetInnersValuesEnd(); itvar++)
	{
		if (itvar->first!="42"&&(itvar->second>=0.0) && !(itvar->second==0.0))
		{
			auto c = FindConstraintOn(itvar->first);
			if (c.first=std::numeric_limits<double>::infinity())
			{
				//TODO
				status = Status::UNBOUNDED;
				infvar = c.second->Name();
				//FINI AVEC LE STATUS UNBOUNDED
				return false;
			}
			c.second->Leaves(itvar->first);
			for (auto it = data.begin(); it != data.end(); it++)
			{
				if (it == c.second)continue;
				it->EnterAndLeaves(*c.second);
				it->Simplify();
			}
			objective.EnterAndLeaves(*c.second);
			return true;
		}
		continue;
	}
	//TODO
	status = Status::ONEPOINT;
	//fini
	return false;
}


std::map<std::string, double> Dictionary::GetSolution()
{
	std::map<std::string, double> r;
	if (status != Status::UNBOUNDED)
	{
		r["42"] = objective.CoefficientOf("42");
		for (auto it = data.begin(); it != data.end(); it++)
		{
			r[it->Name()] = it->CoefficientOf("42");
		}
	}
	else
	{
		r["42"] = std::numeric_limits<double>::infinity();;
		for (auto it = data.begin(); it != data.end(); it++)
		{
			if (it->Name() != this->infvar)
				r[it->Name()] = it->CoefficientOf("42");
			else
				r[this->infvar] = 0;
		}
	}
	return r;
}

std::map<std::string, double> Dictionary::GetAsymptote()
{
	std::map<std::string, double> r;
	if (status == Status::UNBOUNDED)
	{
		for (auto it = data.begin(); it != data.end(); it++)
		{
			if (it->Name() != this->infvar)
				r[it->Name()] = it->CoefficientOf(this->infvar);
		}
	}
	return r;
}



void Dictionary::RunSimplex()
{
	if (FirstSolve())
		while (Step());
}


void Dictionary::Clear()
{
	status = Status::UNDERMINE;
	data.clear();
	this->infvar = "";
}

Dictionary::Status Dictionary::GetStatus()
{
	return this->status;
}


bool Dictionary::FirstSolve()
{
	DictionaryEntry RealObjective = objective;
	objective.Clear();
	objective.AddTerm("\\aleph", -1);
	for (auto it = data.begin(); it != data.end(); it++)
	{
		it->AddTerm("\\aleph", 1);
		it->Simplify();
	}

	//Solve
	//std::cout << *this << std::endl;
	StrangeFirstStep();
	//std::cout << *this << std::endl;
	while (Step());
		//std::cout << *this << std::endl;
	
	if (!objective.CoefficientOf("42")>=0)
	{
		//TODO
		status = Status::EMPTY;
		//SOLUTION IS EMPTY
		return false;
	}

	//Projection
	objective = RealObjective;
	for (auto it = data.begin(); it != data.end(); it++)
	{
		it->AddTerm("\\aleph", 0);
		it->Simplify();
		objective.EnterAndLeaves(*it);
	}
	return true;
}

void Dictionary::StrangeFirstStep()
{
	double c=0;
	auto pos = data.begin();
	for (auto it = data.begin(); it != data.end(); it++)
	{
		if (it->CoefficientOf("42") < c)
		{
			c = it->CoefficientOf("42");
			pos = it;
		}
	}
	if (c==0.0)return;
	pos->Leaves("\\aleph");
	for (auto it = data.begin(); it != data.end(); it++)
	{
		if (it == pos)continue;
		it->EnterAndLeaves(*pos);
		it->Simplify();
	}
	objective.EnterAndLeaves(*pos);
}
