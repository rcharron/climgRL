#ifndef SOLIDITY_H
#define SOLIDITY_H

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

int Solidity_Aire (MetaImage & image);

double Solidity (MetaImage & image);

#endif
