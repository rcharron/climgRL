#include "Test_Rotate.h"

using namespace std;
using namespace DGtal;
using namespace DGtal::Z2i; //We'll only consider Z² digital space on
			    //32bit integers

void Test_Rotate (){
  MetaImage test("../database/deer-6.pgm");
  
  Rotate(test,0);
  test.savePGM("../src/Tests/Rotate/deer-6-rotate-0.pgm");

  MetaImage test1 = Rotate(test,1.04);
  test1.savePGM("../src/Tests/Rotate/deer-6-rotate-1.04.pgm");

  MetaImage test2 = Rotate(test,2.09);
  test2.savePGM("../src/Tests/Rotate/deer-6-rotate-2.09.pgm");
}