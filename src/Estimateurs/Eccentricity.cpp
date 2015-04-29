///////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include <vector>
#include <queue>
#include <utility>
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
    
pair<pair<Point,Point>,int> Find_PlusEloignes (vector<Point> ListePoints){
  Point p1 = ListePoints[0];
  Point p2 = ListePoints[1];
  int distance = 0;
  for (int i = 0; i < ListePoints.size(); i++){
    for (int j = i+1; j < ListePoints.size(); j++){
      int distance_temp, abs, ord;
      abs = ListePoints[j][0] - ListePoints[i][0];
      ord = ListePoints[j][1] - ListePoints[i][1];
      distance_temp = abs*abs + ord*ord;
      if (distance_temp > distance){
	distance = distance_temp;
	p1 = ListePoints[0];
	p1 = ListePoints[1];
      }
    }
  }
  return make_pair(make_pair(p1,p2),distance);
}
    
    
double Eccentricity (MetaImage & image){
  return 0;
}

