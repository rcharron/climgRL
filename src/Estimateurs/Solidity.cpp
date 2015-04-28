///////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include <vector>
#include <queue>
#include <DGtal/base/Common.h>
#include <DGtal/io/boards/Board2D.h>
#include <DGtal/helpers/StdDefs.h>
#include <DGtal/geometry/curves/ArithmeticalDSSComputer.h>
#include <iostream>
#include <DGtal/io/readers/PGMReader.h>
#include "DGtal/images/imagesSetsUtils/SetFromImage.h"
#include "DGtal/images/ImageContainerBySTLVector.h"
///////////////////////////////////////////////////////////////////////////////
#include "../MetaImage.h"
#include "../Modifieurs/ConvexHull.h"
#include "../Modifieurs/Remplissage.h"
///////////////////////////////////////////////////////////////////////////////
 
using namespace std;
using namespace DGtal;
using namespace DGtal::Z2i; //We'll only consider Z² digital space on
			    //32bit integers
    

int Solidity_Aire (MetaImage & image){
  int res =0;
  Domain domain = image.domain();  
  for (Domain::Iterator it = domain.begin(); it != domain.end();it++){
    res += image(*it);
  }
  return res;
}

double Solidity (MetaImage & image){
  Remplissage(image);
  int aire = Solidity_Aire(image);
  MetaImage image_convexhull(image);
  ConvexHull(image_convexhull);
  Remplissage(image_convexhull);
  int aire_convexhull = Solidity_Aire(image_convexhull);
  return ((double)aire/(double)aire_convexhull);
}


