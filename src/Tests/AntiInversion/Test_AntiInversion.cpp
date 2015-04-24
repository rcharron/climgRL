
#include "Test_AntiInversion.h"

using namespace std;
using namespace DGtal;
using namespace DGtal::Z2i; //We'll only consider Z² digital space on
			    //32bit integers

void Test_AntiInversion (){
  Image test1 = Traitement_AntiInversion("rat-8.pgm");
  Board2D board1 = Image_to_Board(test1);
  board1.saveEPS("rat-8-inverse.eps");

  Image test2 = Traitement_AntiInversion("rat-9.pgm");
  Board2D board2 = Image_to_Board(test1);
  board2.saveEPS("rat-9-inverse.eps");
}