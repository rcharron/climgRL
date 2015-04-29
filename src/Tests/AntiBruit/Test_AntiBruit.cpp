#include "Test_AntiBruit.h"

using namespace std;
using namespace DGtal;
using namespace DGtal::Z2i; //We'll only consider Z² digital space on
			    //32bit integers

void Test_AntiBruit (){
  Domain domain(Point(0,0),Point(3,3));
  
  MetaImage test = MetaImage(domain);
  for (Domain::Iterator it = domain.begin(); it != domain.end();it++){
//    cout << "je suis dans la boucle\n";
    test.setValue(*it,1);  
  }
  test.setValue(Point(1,1),0);
  test.savePGM("../src/Tests/AntiBruit/test.pgm");
  Traitement_AntiBruit(test);
  test.savePGM("../src/Tests/AntiBruit/test-debruite.pgm");

  MetaImage testbis = MetaImage(domain);
  for (Domain::Iterator it = domain.begin(); it != domain.end();it++){
//    cout << "je suis dans la boucle\n";
    testbis.setValue(*it,0);  
  }
  testbis.setValue(Point(1,1),1);
  testbis.savePGM("../src/Tests/AntiBruit/testbis.pgm");
  Traitement_AntiBruit(testbis);
  testbis.savePGM("../src/Tests/AntiBruit/testbis-debruite.pgm");  
  
  
  MetaImage test1("../src/Tests/AntiBruit/turtle-1.pgm");
  Traitement_AntiBruit(test1);
  test1.savePGM("../src/Tests/AntiBruit/turtle-1-debruite.pgm");
  //static_cast<Board2D>(test1).saveEPS("rat-8-inverse.eps");

  MetaImage test2("../src/Tests/AntiBruit/turtle-1-bruit-0.3.pgm");
  Traitement_AntiBruit(test2);
  test2.savePGM("../src/Tests/AntiBruit/turtle-1-bruit-0.3-debruite.pgm");
  //static_cast<Board2D>(test2).saveEPS("rat-9-inverse.eps");
  
  MetaImage test3("../src/Tests/AntiBruit/turtle-1-bruit-0.5.pgm");
  Traitement_AntiBruit(test3);
  test3.savePGM("../src/Tests/AntiBruit/turtle-1-bruit-0.5-debruite.pgm");
  
  MetaImage test4("../src/Tests/AntiBruit/turtle-1-bruit-0.8.pgm");
  Traitement_AntiBruit(test4);
  test4.savePGM("../src/Tests/AntiBruit/turtle-1-bruit-0.8-debruite.pgm");
}