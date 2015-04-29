#ifndef TRAITEMENT_ANTIINVERSION_H
#define TRAITEMENT_ANTIINVERSION_H

///////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include <vector>
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

bool To_Inverse (MetaImage& image);

void Inverse (MetaImage& image);
    
void Apply_AntiInversion (MetaImage& image);

void Traitement_AntiInversion (MetaImage& image);


#endif 
