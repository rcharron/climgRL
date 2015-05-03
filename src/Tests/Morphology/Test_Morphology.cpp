#include "Test_Morphology.h"

using namespace std;
using namespace DGtal;
using namespace DGtal::Z2i; //We'll only consider Z² digital space on
			    //32bit integers

void Test_Morphology (){
  int k;
  
  MetaImage test1("../database/butterfly-10.pgm");
  k = Find_k(test1);
  Closing_k(test1,k);
  test1.savePGM("../src/Tests/Morphology/butterfly-10-rempli.pgm");
  //static_cast<Board2D>(test1).saveEPS("rat-8-inverse.eps");

  MetaImage test2("../database/device9-6.pgm");
  k = Find_k(test2);
  Closing_k(test2,k);
  test2.savePGM("../src/Tests/Morphology/device9-6-rempli.pgm");
  //static_cast<Board2D>(test2).saveEPS("rat-9-inverse.eps");
  
  MetaImage test3("../database/pocket-20.pgm");
  k = Find_k(test3);
  Closing_k(test3,k);
  test3.savePGM("../src/Tests/Morphology/pocket-20-rempli.pgm");
  
  MetaImage test4("../database/cup-7.pgm");
  k = Find_k(test4);
  Closing_k(test4,k);
  test4.savePGM("../src/Tests/Morphology/cup-7-rempli.pgm");

  MetaImage test5("../database/cup-12.pgm");
  k = Find_k(test5);
  Closing_k(test5,k);
  test5.savePGM("../src/Tests/Morphology/cup-12-rempli.pgm");    
}