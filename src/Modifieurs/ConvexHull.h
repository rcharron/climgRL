#ifndef CONVEXHULL_H
#define CONVEXHULL_H

///////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <DGtal/base/Common.h>
#include <DGtal/io/boards/Board2D.h>
#include <DGtal/helpers/StdDefs.h>
#include <DGtal/geometry/curves/ArithmeticalDSSComputer.h>
#include <iostream>
#include <DGtal/io/readers/PGMReader.h>
#include "DGtal/images/imagesSetsUtils/SetFromImage.h"
#include "DGtal/images/ImageContainerBySTLVector.h"
#include "../MetaImage.h"
///////////////////////////////////////////////////////////////////////////////

typedef std::vector<DGtal::Z2i::Point>::const_iterator Iterator;

int Determinant(DGtal::Z2i::Point p, DGtal::Z2i::Point q);

//DGtal::Z2i::Point lepointp;

bool CompOr(DGtal::Z2i::Point a, DGtal::Z2i::Point b);


DGtal::Z2i::DigitalSet Build_ConvexHull(DGtal::Z2i::DigitalSet & s);

void ConvexHull (MetaImage& img);

#endif
