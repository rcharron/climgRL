#include "Test_Eccentricity.h"

using namespace std;
using namespace DGtal;
using namespace DGtal::Z2i; //We'll only consider Z² digital space on
			    //32bit integers

void Test_Eccentricity (){
  MetaImage test("../database/bat-2.pgm");
  
  test = MetaImage("../database/bat-2.pgm");
  cout << "Bat 2 : " << Eccentricity(test) << "\n";
  
  test = MetaImage("../database/bat-3.pgm");
  cout << "Bat 3 : " << Eccentricity(test) << "\n";
  
  test = MetaImage("../database/Bone-1.pgm");
  cout << "Bone 1 : " << Eccentricity(test) << "\n";
  
  test = MetaImage("../database/device9-9.pgm");
  cout << "Device9 9 : " << Eccentricity(test) << "\n";
  
  test = MetaImage("../database/hammer-20.pgm");
  cout << "Hammer 20 : " << Eccentricity(test) << "\n";
  
  test = MetaImage("../database/teddy-2.pgm");
  cout << "Teddy 2 : " << Eccentricity(test) << "\n";
  
  test = MetaImage("../database/HCircle-1.pgm");
  cout << "HCircle 1 : " << Eccentricity(test) << "\n";
}