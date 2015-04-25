
#include "Test_AntiInversion.h"

using namespace std;
using namespace DGtal;
using namespace DGtal::Z2i; //We'll only consider Z² digital space on
			    //32bit integers

void Test_AntiInversion (){
  MetaImage test1("../database/rat-8.pgm");
  Traitement_AntiInversion(test1);
  static_cast<Board2D>(test1).saveEPS("rat-8-inverse.eps");

  MetaImage test2("../database/rat-9.pgm");
  Traitement_AntiInversion(test2);
  static_cast<Board2D>(test2).saveEPS("rat-9-inverse.eps");
}