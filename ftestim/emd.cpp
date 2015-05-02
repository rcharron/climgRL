#include "emd.h"
#include <cmath>
#include <iostream>

using namespace std;

#define MASK_SIZE 5

/*string intToString(int i)
{
	if (i == 0)return "0";
	string s;
	if (i < 0)
	{
		s += "-";
		i = -i;
	}
	while (i>0)
	{
		s += static_cast<char>('0' + i % 10);
		i /= 10;
	}
	return s;
}*/

//string intsToString(int i,int j,int k,int l)
//{
//	//if (i == 0)return "0";
//	string s="00 00 00 00";
//	s[0] = static_cast<char>('0' + i % 10);
//	s[1] = static_cast<char>('0' + i / 10);
//
//	s[3] = static_cast<char>('0' + j % 10);
//	s[4] = static_cast<char>('0' + j / 10);
//
//	s[6] = static_cast<char>('0' + k % 10);
//	s[7] = static_cast<char>('0' + k / 10);
//
//	s[9] = static_cast<char>('0' + l % 10);
//	s[10] = static_cast<char>('0' + l / 10);
//	return s;
//}

emd::emd()
{

}


int intsToString(int i, int j, int k, int l)
{
	//if (i == 0)return "0";
	return i+100*j+10000*k+1000000*l;
}

double emd::compute(std::vector< std::vector< double > >& histogramme1, std::vector< std::vector< double > >& histogramme2)
{
  if(histogramme1.size()!=64)throw string("wrong size assumption");
  if(histogramme2.size()!=64)throw string("wrong size assumption");
  if(histogramme1[0].size()!=64)throw string("wrong size assumption");
  if(histogramme2[0].size()!=64)throw string("wrong size assumption");
  Dictionary d;
  os=new ofstream("pb.pl");
  cout << "prepare" << endl;
  this->EMDObjective(d.GetObjective());
  cout << "objective fixed" << endl;
//  this->EMDConstraintTransfert1(d.AddNewEntry());
//  cout << "transfert1 fixed" << endl;
  this->EMDConstraintTransfert2(d.AddNewEntry());
  cout << "transfert2 fixed" << endl;
  for(int i=0;i<64;i++)
  {
    for(int j=0;j<64;j++)
    {
		this->EMDConstraintArrival(d.AddNewEntry(),i, j, histogramme2[i][j]);
		this->EMDConstraintDeparture(d.AddNewEntry(),i, j, histogramme1[i][j]);
    }
  }
  *os<<"BOUNDS"<<endl;
  for (int i = 0; i < 64; i++)
	{
		for (int j = 0; j < 64; j++)
		{
			for (int k = 0; k < 64; k++)
			{
				for (int l = 0; l < 64; l++)
				{
					if ((abs(i - k) > MASK_SIZE) || (abs(j - l) > MASK_SIZE))continue;
					//stringstream ss;
					//ss<<k<<" "<<l<<" "<<i<<" "<<j;
					//res+=data[ss.str()]*sqrt((i-k)*(i-k)+(j-l)*(j-l));
					*os<<intsToString(k,l,i,j)<<">=0"<<endl;

				}
			}
		}
	}
  *os<<"VARIABLES"<<endl;
  os->close();
  cout<<"file ready"<<endl;
  d.RunSimplex();
  
  delete os;
  return this->EMDComputeFinalSolution(d.GetSolution());
  
}



void emd::EMDConstraintArrival(DictionaryEntry* de,int arrivali, int arrivalj, double amont)
{
  de->AddConstant(amont);
  
  for(int i=0;i<64;i++)
  {
    for(int j=0;j<64;j++)
    {
		if ((abs(i - arrivali) > MASK_SIZE) || (abs(j - arrivalj) > MASK_SIZE))continue;
      //stringstream ss;
      //ss<<i<<" "<<j<<" "<<arrivali<<" "<<arrivalj;
      //de.AddTerm(ss.str(),-1);
		de->AddTerm(intsToString(i,j,arrivali,arrivalj), -1);
		*os<<"-x"<<intsToString(i,j,arrivali,arrivalj)<<" ";
    }
  } 
  *os<<" +"<<amont<<">=0"<<endl;
}

void emd::EMDConstraintDeparture(DictionaryEntry* de,int arrivali, int arrivalj, double amont)
{
  de->AddConstant(amont);
  
  for(int i=0;i<64;i++)
  {
    for(int j=0;j<64;j++)
    {
		if ((abs(i - arrivali) > MASK_SIZE) || (abs(j - arrivalj) > MASK_SIZE))continue;
      //stringstream ss;
      //ss<<arrivali<<" "<<arrivalj<<" "<<i<<" "<<j;
      //de.AddTerm(ss.str(),-1);
		de->AddTerm(intsToString(arrivali,arrivalj,i,j), -1);
		*os<<"-x"<<intsToString(arrivali,arrivalj,i,j)<<" ";
    }
  } 
  *os <<">="<<-amont<<endl;
}

void emd::EMDConstraintTransfert1(DictionaryEntry* de)
{
	de->AddConstant(1);

	for (int i = 0; i < 64; i++)
	{
		for (int j = 0; j < 64; j++)
		{
			for (int k = 0; k < 64; k++)
			{
				for (int l = 0; l < 64; l++)
				{
					if ((abs(i - k) > MASK_SIZE) || (abs(j - l) > MASK_SIZE))continue;
					//stringstream ss;
					//ss<<k<<" "<<l<<" "<<i<<" "<<j;
					//de.AddTerm(ss.str(),-1);
					de->AddTerm(intsToString(k,l,i,j), -1);
					*os<<"-x"<<intsToString(k,l,i,j)<<" ";
				}
			}
		}
	}
	*os<<" >=-1"<<endl;
}

void emd::EMDConstraintTransfert2(DictionaryEntry* de)
{
	de->AddConstant(-1);

	for (int i = 0; i < 64; i++)
	{
		for (int j = 0; j < 64; j++)
		{
			for (int k = 0; k < 64; k++)
			{
				for (int l = 0; l < 64; l++)
				{
					if ((abs(i - k) > MASK_SIZE) || (abs(j - l) > MASK_SIZE))continue;
					//stringstream ss;
					//ss<<k<<" "<<l<<" "<<i<<" "<<j;
					//de.AddTerm(ss.str(),1);
					de->AddTerm(intsToString(k, l, i, j), 1);
					*os<<"+x"<<intsToString(k,l,i,j)<<" ";
				}
			}
		}
	}
	*os<<" >=1"<<endl;
}


void emd::EMDObjective(DictionaryEntry* de)
{
  *os<<"MINIMIZE "<<endl;
	for (int i = 0; i < 64; i++)
	{
		for (int j = 0; j < 64; j++)
		{
			for (int k = 0; k < 64; k++)
			{
				for (int l = 0; l < 64; l++)
				{
					if ((abs(i - k) > MASK_SIZE) || (abs(j - l) > MASK_SIZE))continue;
					//stringstream ss;
					//ss << k << " " << l << " " << i << " " << j;
					//de.AddTerm(ss.str(), -sqrt((i - k)*(i - k) + (j - l)*(j - l)));
					de->AddTerm(intsToString(k, l, i, j), -sqrt((i - k)*(i - k) + (j - l)*(j - l)));
					*os<<-sqrt((i - k)*(i - k) + (j - l)*(j - l))<<"x"<<intsToString(k,l,i,j)<<" ";
				}
			}
		}
	}
	*os<<endl<<"SUBJECT TO"<<endl;
}

double emd::EMDComputeFinalSolution(map< int, double > data)
{
	double res = 0.0;
	for (int i = 0; i < 64; i++)
	{
		for (int j = 0; j < 64; j++)
		{
			for (int k = 0; k < 64; k++)
			{
				for (int l = 0; l < 64; l++)
				{
					if ((abs(i - k) > MASK_SIZE) || (abs(j - l) > MASK_SIZE))continue;
					//stringstream ss;
					//ss<<k<<" "<<l<<" "<<i<<" "<<j;
					//res+=data[ss.str()]*sqrt((i-k)*(i-k)+(j-l)*(j-l));
					res += data[intsToString(k, l, i, j)] * sqrt((i - k)*(i - k) + (j - l)*(j - l));

				}
			}
		}
	}
	return res;
}
