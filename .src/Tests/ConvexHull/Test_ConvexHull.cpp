#include "Test_ConvexHull.h"

using namespace std;
using namespace DGtal;
using namespace DGtal::Z2i; //We'll only consider Z² digital space on
			    //32bit integers

void Test_ConvexHull (){
  MetaImage test1("../database/bat-4.pgm");
  ConvexHull(test1);
  test1.savePGM("../src/Tests/ConvexHull/bat-4-convexHull.pgm");
  //static_cast<Board2D>(test1).saveEPS("rat-8-inverse.eps");

  MetaImage test2("../database/beetle-7.pgm");
  ConvexHull(test2);
  test2.savePGM("../src/Tests/ConvexHull/beetle-7-convexHull.pgm");
  //static_cast<Board2D>(test2).saveEPS("rat-9-inverse.eps");

  MetaImage test3("../database/bottle-8.pgm");
  ConvexHull(test3);
  test3.savePGM("../src/Tests/ConvexHull/bottle-8-convexHull.pgm");
  
  MetaImage test4("../database/brick-2.pgm");
  ConvexHull(test4);
  test4.savePGM("../src/Tests/ConvexHull/brick-2-convexHull.pgm");

  MetaImage test5("../database/camel-12.pgm");
  ConvexHull(test5);
  test5.savePGM("../src/Tests/ConvexHull/camel-12-convexHull.pgm");
}