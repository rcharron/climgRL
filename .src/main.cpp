///////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <DGtal/base/Common.h>
#include <DGtal/io/boards/Board2D.h>
#include <DGtal/helpers/StdDefs.h>
//#include <DGtal/io/readers/PGMReader.h>
//#include "DGtal/images/imagesSetsUtils/SetFromImage.h"
#include "DGtal/images/ImageContainerBySTLVector.h"
////////////////////////////////////////////////////////////////////////////////
////////////////////// MODIFIEURS //////////////////////////////////////////////
#include "Modifieurs/Traitement_AntiBruit.h"
#include "Modifieurs/Traitement_AntiInversion.h"
#include "Tests/AntiInversion/Test_AntiInversion.h"
#include "Tests/AntiBruit/Test_AntiBruit.h"
#include "Tests/Remplissage/Test_Remplissage.h"
#include "Tests/ConvexHull/Test_ConvexHull.h"
#include "Tests/Scaling/Test_Solidity_Scale.h"
#include "Tests/Scaling/Test_Eccentricity_Scale.h"
#include "Tests/Scaling/Test_AverageBendingFlexion_Scale.h"
#include "Tests/Rotate/Test_Rotate.h"
#include "Tests/Skelton/Test_Skelton.h"
#include "Tests/Morphology/Test_Morphology.h"
#include "Tests/Eccentricity/Test_Eccentricity.h"
#include "Tests/Noise/Test_Solidity_Noise.h"
#include "Tests/Noise/Test_Eccentricity_Noise.h"
///////////////////////////////////////////////////////////////////////////////

using namespace std;
using namespace DGtal;
using namespace DGtal::Z2i; //We'll only consider Z² digital space on
			    //32bit integers
int main()
{
//  Test_AntiInversion();
//  Test_Remplissage();
//  Test_ConvexHull();
//  Test_AntiBruit();
//  Test_Solidity_Scale();
//  Test_Rotate();
//  Test_Eccentricity_Scale();
//  Test_Skelton();
//  Test_Morphology();
//  Test_AverageBendingFlexion_Scale();
//  Test_Eccentricity();
//  Test_Eccentricity_Noise();
  Test_Solidity_Noise();
  return 0;
}