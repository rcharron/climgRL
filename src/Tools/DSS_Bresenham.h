#ifndef DSS_BRESENHAM_H
#define DSS_BRESENHAM_H

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
///////////////////////////////////////////////////////////////////////////////


DGtal::Z2i::DigitalSet ConstructLineFstOctant(DGtal::Z2i::Domain & domain, DGtal::Z2i::Point p1, DGtal::Z2i::Point p2);

DGtal::Z2i::DigitalSet ConstructLineFstQuart(DGtal::Z2i::Domain & domain, DGtal::Z2i::Point p1, DGtal::Z2i::Point p2);

DGtal::Z2i::DigitalSet ConstructLine(DGtal::Z2i::Domain & domain, DGtal::Z2i::Point p1, DGtal::Z2i::Point p2);


#endif