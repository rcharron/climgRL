#include "Test_Remplissage.h"

using namespace std;
using namespace DGtal;
using namespace DGtal::Z2i; //We'll only consider Z² digital space on
			    //32bit integers

void Test_Remplissage (){
  MetaImage test1("../database/butterfly-10.pgm");
  Remplissage(test1);
  test1.savePGM("../src/Tests/Remplissage/butterfly-10-rempli.pgm");
  //static_cast<Board2D>(test1).saveEPS("rat-8-inverse.eps");

  MetaImage test2("../database/device9-6.pgm");
  Remplissage(test2);
  test2.savePGM("../src/Tests/Remplissage/device9-6-rempli.pgm");
  //static_cast<Board2D>(test2).saveEPS("rat-9-inverse.eps");
  
  MetaImage test3("../database/pocket-20.pgm");
  Remplissage(test3);
  test3.savePGM("../src/Tests/Remplissage/pocket-20-rempli.pgm");
  
  MetaImage test4("../database/cup-7.pgm");
  Remplissage(test4);
  test4.savePGM("../src/Tests/Remplissage/cup-7-rempli.pgm");

  MetaImage test5("../database/cup-12.pgm");
  Remplissage(test5);
  test5.savePGM("../src/Tests/Remplissage/cup-12-rempli.pgm");    
}