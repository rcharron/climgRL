#include "Dictionnary.h"
#include <limits>
#include <iostream>



Dictionary::Dictionary()
{
	status = Status::UNDERMINE;
	cnumber = -3;
}


Dictionary::~Dictionary()
{
}

void Dictionary::SetObjective(DictionaryEntry& obj)
{
	objective = obj;
}

void Dictionary::AddEntry(DictionaryEntry entry)
{
	entry.SetWord(this->cnumber);
	this->cnumber++;
	data.push_back(entry);
}


std::pair<double, std::vector<DictionaryEntry>::iterator> Dictionary::FindConstraintOn(int variable)
{
	double c=1;
	auto pos = data.begin();
	for (auto it = data.begin(); it != data.end(); it++)
	{
		double l = it->CoefficientOf(-1);
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
		if (itvar->first!=-1&&(itvar->second>=0.0) && !(itvar->second==0.0))
		{
			auto c = FindConstraintOn(itvar->first);
			if (c.first=std::numeric_limits<double>::infinity())
			{
				//TODO
				status = Status::UNBOUNDED;
				std::cout<<"Problème non borné"<<std::endl;
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
	std::cout<<"Tout va bien"<<std::endl;
	//fini
	return false;
}


std::map<int, double> Dictionary::GetSolution()
{
	std::map<int, double> r;
	if (status != Status::UNBOUNDED)
	{
		r[-1] = objective.CoefficientOf(-1);
		for (auto it = data.begin(); it != data.end(); it++)
		{
			r[it->Name()] = it->CoefficientOf(-1);
		}
	}
	else
	{
		r[-1] = std::numeric_limits<double>::infinity();;
		for (auto it = data.begin(); it != data.end(); it++)
		{
			if (it->Name() != this->infvar)
				r[it->Name()] = it->CoefficientOf(-1);
			else
				r[this->infvar] = 0;
		}
	}
	return r;
}

std::map<int, double> Dictionary::GetAsymptote()
{
	std::map<int, double> r;
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
	this->infvar = 0;
	cnumber = -3;
}

Dictionary::Status Dictionary::GetStatus()
{
	return this->status;
}


bool Dictionary::FirstSolve()
{
	DictionaryEntry RealObjective = objective;
	objective.Clear();
	objective.AddTerm(-2, -1);
	for (auto it = data.begin(); it != data.end(); it++)
	{
		it->AddTerm(-2, 1);
		it->Simplify();
	}
	//Solve
	std::cout << "READy" << std::endl;
	StrangeFirstStep();
	std::cout<<"f->"<<objective.CoefficientOf(-1)<<std::endl;
	//std::cout << *this << std::endl;
	while (Step())
		std::cout<<"f->"<<objective.CoefficientOf(-1)<<std::endl;
		//std::cout << *this << std::endl;
	
	if (!(objective.CoefficientOf(-1)>=0))
	{
		//TODO
		status = Status::EMPTY;
		//SOLUTION IS EMPTY
		std::cout<<"Problème vide"<<std::endl;
		return false;
	}

	//Projection
	objective = RealObjective;
	for (auto it = data.begin(); it != data.end(); it++)
	{
		it->AddTerm(-2, 0);
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
		if (it->CoefficientOf(-1) < c)
		{
			c = it->CoefficientOf(-1);
			pos = it;
		}
	}
	std::cout<<"coucou"<<std::endl;
	if (c==0.0)return;
	pos->Leaves(-2);
	unsigned int i,t;
	i=0;
	t=data.size();
	for (auto it = data.begin(); it != data.end(); it++)
	{
	  std::cout<<"\r("<<i<<"/"<<t<<")"<<std::flush;
		if (it == pos)continue;
		it->EnterAndLeaves(*pos);
		it->Simplify();
		i++;
	}
	objective.EnterAndLeaves(*pos);
}


DictionaryEntry* Dictionary::GetObjective()
{
	return &objective;
}

DictionaryEntry* Dictionary::AddNewEntry()
{
	data.push_back(DictionaryEntry());
	DictionaryEntry* de = &data[data.size() - 1];
	de->SetWord(this->cnumber);
	this->cnumber++;
	return de;
}