#include "Test_AntiInversion.h"
#include <vector>

using namespace std;
using namespace DGtal;
using namespace DGtal::Z2i; //We'll only consider Z² digital space on
			    //32bit integers

void Test_AntiInversion (){
  MetaImage test1("../database/rat-8.pgm");
  Traitement_AntiInversion(test1);
  test1.savePGM("../src/Tests/AntiInversion/rat-8-inverse.pgm");
  //static_cast<Board2D>(test1).saveEPS("rat-8-inverse.eps");

  MetaImage test2("../database/rat-9.pgm");
  Traitement_AntiInversion(test2);
  test2.savePGM("../src/Tests/AntiInversion/rat-9-inverse.pgm");
  //static_cast<Board2D>(test2).saveEPS("rat-9-inverse.eps");
  
  MetaImage test3("../database/Glas-11.pgm");
  Traitement_AntiInversion(test3);
  test3.savePGM("../src/Tests/AntiInversion/Glas-11-inverse.pgm");
}