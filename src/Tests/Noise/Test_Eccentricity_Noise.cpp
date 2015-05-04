#include "Test_Eccentricity_Noise.h"

using namespace std;
using namespace DGtal;
using namespace DGtal::Z2i; //We'll only consider Z² digital space on
			    //32bit integers

void Test_Eccentricity_Noise (){
  MetaImage test("../src/Tests/Noise/key-6.pgm");
  
  cout <<"\n KEY 6 :\n";
  
  test = MetaImage("../src/Tests/Noise/key-6.pgm");
  cout << "Key 6 (noise 0) : " << Eccentricity(test) << "\n";
  test.iterRemoveNoise();
  cout << "Key 6 (noise 0, debruite) : " << Eccentricity(test) << "\n";
  
  test = MetaImage("../src/Tests/Noise/key-6.3.pgm");
  cout << "Key 6 (noise 0.3) : " << Eccentricity(test) << "\n";
  test.iterRemoveNoise();
  cout << "Key 6 (noise 0.3, debruite) : " << Eccentricity(test) << "\n";
  
  test = MetaImage("../src/Tests/Noise/key-6.5.pgm");
  cout << "Key 6 (noise 0.5) : " << Eccentricity(test) << "\n";
  test.iterRemoveNoise();
  cout << "Key 6 (noise 0.5, debruite) : " << Eccentricity(test) << "\n";
  
  test = MetaImage("../src/Tests/Noise/key-6.8.pgm");
  cout << "Key 6 (noise 0.8) : " << Eccentricity(test) << "\n";
  test.iterRemoveNoise();
  cout << "Key 6 (noise 0.8, debruite) : " << Eccentricity(test) << "\n";
  
  cout <<"\n FLY 6 :\n";
  
  test = MetaImage("../src/Tests/Noise/fly-6.pgm");
  cout << "Fly 6 (noise 0) : " << Eccentricity(test) << "\n";
  test.iterRemoveNoise();
  cout << "Fly 6 (noise 0, debruite) : " << Eccentricity(test) << "\n";
  
  test = MetaImage("../src/Tests/Noise/fly-6.3.pgm");
  cout << "Fly 6 (noise 0.3) : " << Eccentricity(test) << "\n";
  test.iterRemoveNoise();
  cout << "Fly 6 (noise 0.3, debruite) : " << Eccentricity(test) << "\n";
  
  test = MetaImage("../src/Tests/Noise/fly-6.5.pgm");
  cout << "Fly 6 (noise 0.5) : " << Eccentricity(test) << "\n";
  test.iterRemoveNoise();
  cout << "Fly 6 (noise 0.5, debruite) : " << Eccentricity(test) << "\n";
  
  test = MetaImage("../src/Tests/Noise/fly-6.8.pgm");
  cout << "Fly 6 (noise 0.8) : " << Eccentricity(test) << "\n";
  test.iterRemoveNoise();
  cout << "Fly 6 (noise 0.8, debruite) : " << Eccentricity(test) << "\n";
  
  cout <<"\n CHOPPER 4 :\n";
  
  test = MetaImage("../src/Tests/Noise/chopper-4.pgm");
  cout << "Chopper 4 (noise 0) : " << Eccentricity(test) << "\n";
  test.iterRemoveNoise();
  cout << "Chopper 4 (noise 0, debruite) : " << Eccentricity(test) << "\n";
  
  test = MetaImage("../src/Tests/Noise/chopper-4.3.pgm");
  cout << "Chopper 4 (noise 0.3) : " << Eccentricity(test) << "\n";
  test.iterRemoveNoise();
  cout << "Chopper 4 (noise 0.3, debruite) : " << Eccentricity(test) << "\n";
  
  test = MetaImage("../src/Tests/Noise/chopper-4.5.pgm");
  cout << "Chopper 4 (noise 0.5) : " << Eccentricity(test) << "\n";
  test.iterRemoveNoise();
  cout << "Chopper 4 (noise 0.5, debruite) : " << Eccentricity(test) << "\n";
  
  test = MetaImage("../src/Tests/Noise/chopper-4.8.pgm");
  cout << "Chopper 4 (noise 0.8) : " << Eccentricity(test) << "\n";
  test.iterRemoveNoise();
  cout << "Chopper 4 (noise 0.8, debruite) : " << Eccentricity(test) << "\n";
  
  cout <<"\n DEVICE0 7 :\n";
  
  test = MetaImage("../src/Tests/Noise/device0-7.pgm");
  cout << "Device0 7 (noise 0) : " << Eccentricity(test) << "\n";
  test.iterRemoveNoise();
  cout << "Device0 7 (noise 0, debruite) : " << Eccentricity(test) << "\n";
  
  test = MetaImage("../src/Tests/Noise/device0-7.3.pgm");
  cout << "Device0 7 (noise 0.3) : " << Eccentricity(test) << "\n";
  test.iterRemoveNoise();
  cout << "Device0 7 (noise 0.3, debruite) : " << Eccentricity(test) << "\n";
  
  test = MetaImage("../src/Tests/Noise/device0-7.5.pgm");
  cout << "Device0 7 (noise 0.5) : " << Eccentricity(test) << "\n";
  test.iterRemoveNoise();
  cout << "Device0 7 (noise 0.5, debruite) : " << Eccentricity(test) << "\n";
  
  test = MetaImage("../src/Tests/Noise/device0-7.8.pgm");
  cout << "Device0 7 (noise 0.8) : " << Eccentricity(test) << "\n";
  test.iterRemoveNoise();
  cout << "Device0 7 (noise 0.8, debruite) : " << Eccentricity(test) << "\n";
  
  cout <<"\n SEA_SNAKE 20 :\n";
  
  test = MetaImage("../src/Tests/Noise/sea_snake-20.pgm");
  cout << "Sea Snake 20 (noise 0) : " << Eccentricity(test) << "\n";
  test.iterRemoveNoise();
  cout << "Sea Snake 20 (noise 0, debruite) : " << Eccentricity(test) << "\n";
  
  test = MetaImage("../src/Tests/Noise/sea_snake-20.3.pgm");
  cout << "Sea Snake 20 (noise 0.3) : " << Eccentricity(test) << "\n";
  test.iterRemoveNoise();
  cout << "Sea Snake 20 (noise 0.3, debruite) : " << Eccentricity(test) << "\n";
  
  test = MetaImage("../src/Tests/Noise/sea_snake-20.5.pgm");
  cout << "Sea Snake 20 (noise 0.5) : " << Eccentricity(test) << "\n";
  test.iterRemoveNoise();
  cout << "Sea Snake 20 (noise 0.5, debruite) : " << Eccentricity(test) << "\n";
  
  test = MetaImage("../src/Tests/Noise/sea_snake-20.8.pgm");
  cout << "Sea Snake 20 (noise 0.8) : " << Eccentricity(test) << "\n";
  test.iterRemoveNoise();
  cout << "Sea Snake 20 (noise 0.8, debruite) : " << Eccentricity(test) << "\n";  
}