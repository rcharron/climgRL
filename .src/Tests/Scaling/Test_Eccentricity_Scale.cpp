#include "Test_Eccentricity_Scale.h"

using namespace std;
using namespace DGtal;
using namespace DGtal::Z2i; //We'll only consider Z² digital space on
			    //32bit integers

void Test_Eccentricity_Scale (){
  cout << "BAT 2 :\n";
  
  MetaImage test1_1("../src/Tests/Scaling/bat-2.pgm");
//  test1_1 = Eccentricity(test1_1);
//  test1_1 = Rotate(test1_1,1.04);
//  test1_1.savePGM("../src/Tests/Scaling/bat-2-test-eccentricity.pgm");
//  Remplissage(test1_1);
  cout << "Bat 2 (scale 1) : excentricité = " << Eccentricity(test1_1) << "\n";
  
  MetaImage test1_2("../src/Tests/Scaling/bat-2-scale-0.5.pgm"); 
//  Remplissage(test1_2);
  cout << "Bat 2 (scale 0.5) : excentricité = " << Eccentricity(test1_2) << "\n"; 

  MetaImage test1_3("../src/Tests/Scaling/bat-2-scale-2.pgm");
//  Remplissage(test1_3);
  cout << "Bat 2 (scale 2) : excentricité = " << Eccentricity(test1_3) << "\n";
  
  MetaImage test1_4("../src/Tests/Scaling/bat-2-scale-5.pgm");
//  Remplissage(test1_4);
  cout << "Bat 2 (scale 5) : excentricité = " << Eccentricity(test1_4) << "\n\n";

  cout << "HAMMER 20 :\n";
  
  MetaImage test2_1("../src/Tests/Scaling/hammer-20.pgm");
//  Remplissage(test2_1);
  cout << "Hammer 20 (scale 1) : excentricité = " << Eccentricity(test2_1) << "\n";
  
  MetaImage test2_2("../src/Tests/Scaling/hammer-20-scale-0.5.pgm");
//  Remplissage(test2_2);
  cout << "Hammer 20 (scale 0.5) : excentricité = " << Eccentricity(test2_2) << "\n";

  MetaImage test2_3("../src/Tests/Scaling/hammer-20-scale-2.pgm");
//  Remplissage(test2_3);
  cout << "Hammer 20 (scale 2) : excentricité = " << Eccentricity(test2_3) << "\n";
  
  MetaImage test2_4("../src/Tests/Scaling/hammer-20-scale-5.pgm");
//  Remplissage(test2_4);
  cout << "Hammer 20 (scale 5) : excentricité = " << Eccentricity(test2_4) << "\n\n";  

  cout << "DEVICE9-9 :\n";
  
  MetaImage test3_1("../src/Tests/Scaling/device9-9.pgm");
//  Remplissage(test3_1);
  cout << "Device9 9 (scale 1) : excentricité = " << Eccentricity(test3_1) << "\n";
  
  MetaImage test3_2("../src/Tests/Scaling/device9-9-scale-0.5.pgm");
//  Remplissage(test3_2);
  cout << "Device9 9 (scale 0.5) : excentricité = " << Eccentricity(test3_2) << "\n";

  MetaImage test3_3("../src/Tests/Scaling/device9-9-scale-2.pgm");
//  Remplissage(test3_3);
  cout << "Device9 9 (scale 2) : excentricité = " << Eccentricity(test3_3) << "\n";
  
  MetaImage test3_4("../src/Tests/Scaling/device9-9-scale-5.pgm");
//  Remplissage(test3_4);
  cout << "Device9 9 (scale 5) : excentricité = " << Eccentricity(test3_4) << "\n\n"; 

}