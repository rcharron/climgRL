#include "Test_Eccentricity.h"

using namespace std;
using namespace DGtal;
using namespace DGtal::Z2i; //We'll only consider Z² digital space on
			    //32bit integers

void Test_Eccentricity_Scale (){
  cout << "HORSE-20 :\n";
  
  MetaImage test1_1("../src/Tests/Scaling/horse-20.pgm");
  Remplissage(test1_1);
  cout << "Horse (scale 1) : excentricité = " << Eccentricity(test1_1) << "\n";
  
  MetaImage test1_2("../src/Tests/Scaling/horse-20-scale-0.5.pgm");
  Remplissage(test1_2);
  cout << "Horse (scale 0.5) : excentricité = " << Eccentricity(test1_2) << "\n";

  MetaImage test1_3("../src/Tests/Scaling/horse-20-scale-2.pgm");
  Remplissage(test1_3);
  cout << "Horse (scale 2) : excentricité = " << Eccentricity(test1_3) << "\n";
  
  MetaImage test1_4("../src/Tests/Scaling/horse-20-scale-5.pgm");
  Remplissage(test1_4);
  cout << "Horse (scale 5) : excentricité = " << Eccentricity(test1_4) << "\n\n";

  cout << "APPLE-3 :\n";
  
  MetaImage test2_1("../src/Tests/Scaling/apple-3.pgm");
  Remplissage(test2_1);
  cout << "Apple (scale 1) : excentricité = " << Eccentricity(test2_1) << "\n";
  
  MetaImage test2_2("../src/Tests/Scaling/apple-3-scale-0.5.pgm");
  Remplissage(test2_2);
  cout << "Apple (scale 0.5) : excentricité = " << Eccentricity(test2_2) << "\n";

  MetaImage test2_3("../src/Tests/Scaling/apple-3-scale-2.pgm");
  Remplissage(test2_3);
  cout << "Apple (scale 2) : excentricité = " << Eccentricity(test2_3) << "\n";
  
  MetaImage test2_4("../src/Tests/Scaling/apple-3-scale-5.pgm");
  Remplissage(test2_4);
  cout << "Apple (scale 5) : excentricité = " << Eccentricity(test2_4) << "\n\n";  

  cout << "DEVICE7-1 :\n";
  
  MetaImage test3_1("../src/Tests/Scaling/device7-1.pgm");
  Remplissage(test3_1);
  cout << "Device7 (scale 1) : excentricité = " << Eccentricity(test3_1) << "\n";
  
  MetaImage test3_2("../src/Tests/Scaling/device7-1-scale-0.5.pgm");
  Remplissage(test3_2);
  cout << "Device7 (scale 0.5) : excentricité = " << Eccentricity(test3_2) << "\n";

  MetaImage test3_3("../src/Tests/Scaling/device7-1-scale-2.pgm");
  Remplissage(test3_3);
  cout << "Device7 (scale 2) : excentricité = " << Eccentricity(test3_3) << "\n";
  
  MetaImage test3_4("../src/Tests/Scaling/device7-1-scale-5.pgm");
  Remplissage(test3_4);
  cout << "Device7 (scale 5) : excentricité = " << Eccentricity(test3_4) << "\n\n"; 

  cout << "LIZZARD-13 :\n";
  
  MetaImage test4_1("../src/Tests/Scaling/lizzard-13.pgm");
  Remplissage(test4_1);
  cout << "Lizzard (scale 1) : excentricité = " << Eccentricity(test4_1) << "\n";
  
  MetaImage test4_2("../src/Tests/Scaling/lizzard-13-scale-0.5.pgm");
  Remplissage(test4_2);
  cout << "Lizzard (scale 0.5) : excentricité = " << Eccentricity(test4_2) << "\n";

  MetaImage test4_3("../src/Tests/Scaling/lizzard-13-scale-2.pgm");
  Remplissage(test4_3);
  cout << "Lizzard (scale 2) : excentricité = " << Eccentricity(test4_3) << "\n";
  
  MetaImage test4_4("../src/Tests/Scaling/lizzard-13-scale-5.pgm");
  Remplissage(test4_4);
  cout << "Lizzard (scale 5) : excentricité = " << Eccentricity(test4_4) << "\n\n";    
}