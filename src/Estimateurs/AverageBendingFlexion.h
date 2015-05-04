#ifndef AVERAGE_BENDING_FLEXION_H
#define AVERAGE_BENDING_FLEXION_H

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
#include "../Tools/Tangente.h"
#include "../Tools/DSS_Bresenham.h"
///////////////////////////////////////////////////////////////////////////////

double dist (DGtal::Z2i::Point A, DGtal::Z2i::Point B);

double aire (DGtal::Z2i::Domain & domain, DGtal::Z2i::Point A, DGtal::Z2i::Point B, DGtal::Z2i::Point C);

double Curvature (DGtal::Z2i::Domain & domain, std::vector<DGtal::Z2i::Point> & bord, DGtal::Z2i::Point P);


double AverageBendingFlexion (MetaImage & image);

#endif
