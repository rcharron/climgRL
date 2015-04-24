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
#include "../Tools/LireImgPgm.h"
///////////////////////////////////////////////////////////////////////////////

bool To_Inverse (Image & image);

Image Inverse (Image & image);
    
Image Apply_AntiInversion (Image & image);

Image Traitement_AntiInversion (std::string filename);


#endif 
