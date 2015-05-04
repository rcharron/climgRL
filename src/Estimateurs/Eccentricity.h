#ifndef SOLIDITY_H
#define SOLIDITY_H

///////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include <vector>
#include <queue>
#include <utility>
#include <math.h>
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
#include "../Tools/Rotate.h"
///////////////////////////////////////////////////////////////////////////////


double Eccentricity_Dist (DGtal::Z2i::Point A, DGtal::Z2i::Point B);

std::pair<std::pair<DGtal::Z2i::Point,DGtal::Z2i::Point>,int> Find_PlusEloignes (DGtal::Z2i::DigitalSet & s);

int Dist_Max_Vert (MetaImage & image);
    
double Eccentricity (MetaImage & image);

#endif

