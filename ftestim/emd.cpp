#include "emd.h"
#include <cmath>

using namespace std;

double emd::compute(std::vector< std::vector< double > >& histogramme1, std::vector< std::vector< double > >& histogramme2)
{
  if(histogramme1.size()!=64)throw string("wrong size assumption");
  if(histogramme2.size()!=64)throw string("wrong size assumption");
  if(histogramme1[0].size()!=64)throw string("wrong size assumption");
  if(histogramme2[0].size()!=64)throw string("wrong size assumption");
  Dictionary d;
  d.SetObjective(this->EMDObjective());
  d.AddEntry(this->EMDConstraintTransfert1());
  d.AddEntry(this->EMDConstraintTransfert2());
  for(int i=0;i<64;i++)
  {
    for(int j=0;j<64;j++)
    {
      d.AddEntry(this->EMDConstraintArrival(i,j,histogramme2[i][j]));
      d.AddEntry(this->EMDConstraintDeparture(i,j,histogramme1[i][j]));
    }
  }
  d.RunSimplex();
  return this->EMDComputeFinalSolution(d.GetSolution());
  
}



DictionaryEntry emd::EMDConstraintArrival(int arrivali, int arrivalj,double amont)
{
  DictionaryEntry de;
  de.AddConstant(amont);
  
  for(int i=0;i<64;i++)
  {
    for(int j=0;j<64;j++)
    {
      stringstream ss;
      ss<<i<<" "<<j<<" "<<arrivali<<" "<<arrivalj;
      de.AddTerm(ss.str(),-1);
    }
  } 
  return de;
}

DictionaryEntry emd::EMDConstraintDeparture(int arrivali, int arrivalj, double amont)
{
  DictionaryEntry de;
  de.AddConstant(amont);
  
  for(int i=0;i<64;i++)
  {
    for(int j=0;j<64;j++)
    {
      stringstream ss;
      ss<<arrivali<<" "<<arrivalj<<" "<<i<<" "<<j;
      de.AddTerm(ss.str(),-1);
    }
  } 
  return de;

}

DictionaryEntry emd::EMDConstraintTransfert1()
{
  DictionaryEntry de;
  de.AddConstant(1);
  
  for(int i=0;i<64;i++)
  {
    for(int j=0;j<64;j++)
    {
      for(int k=0;k<64;k++)
      {
	for(int l=0;l<64;l++)
	{
	  stringstream ss;
	  ss<<k<<" "<<l<<" "<<i<<" "<<j;
	  de.AddTerm(ss.str(),-1);
	}
      }
    }
  } 
  return de;
}

DictionaryEntry emd::EMDConstraintTransfert2()
{
  DictionaryEntry de;
  de.AddConstant(1);
  
  for(int i=0;i<64;i++)
  {
    for(int j=0;j<64;j++)
    {
      for(int k=0;k<64;k++)
      {
	for(int l=0;l<64;l++)
	{
	  stringstream ss;
	  ss<<k<<" "<<l<<" "<<i<<" "<<j;
	  de.AddTerm(ss.str(),1);
	}
      }
    }
  } 
  return de;
}

DictionaryEntry emd::EMDObjective()
{
  DictionaryEntry de;
  for(int i=0;i<64;i++)
  {
    for(int j=0;j<64;j++)
    {
      for(int k=0;k<64;k++)
      {
	for(int l=0;l<64;l++)
	{
	  stringstream ss;
	  ss<<k<<" "<<l<<" "<<i<<" "<<j;
	  de.AddTerm(ss.str(),-sqrt((i-k)*(i-k)+(j-l)*(j-l)));
	}
      }
    }
  } 
  return de;
}

double emd::EMDComputeFinalSolution(map< string, double > data)
{
  double res=0.0;
  for(int i=0;i<64;i++)
  {
    for(int j=0;j<64;j++)
    {
      for(int k=0;k<64;k++)
      {
	for(int l=0;l<64;l++)
	{
	  stringstream ss;
	  ss<<k<<" "<<l<<" "<<i<<" "<<j;
	  res+=data[ss.str()]*sqrt((i-k)*(i-k)+(j-l)*(j-l));
	}
      }
    }
  } 
  return res;
}
