#ifndef LIREIMGPGM_H
#define LIREIMGPGM_H

///////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include <vector>
#include <DGtal/base/Common.h>
#include <DGtal/io/boards/Board2D.h>
#include <DGtal/helpers/StdDefs.h>
#include <DGtal/geometry/curves/ArithmeticalDSSComputer.h>
#include <DGtal/io/readers/PGMReader.h>
#include "DGtal/images/imagesSetsUtils/SetFromImage.h"
#include "DGtal/images/ImageContainerBySTLVector.h"
///////////////////////////////////////////////////////////////////////////////


//Image type (image of unsigned int)
typedef DGtal::ImageContainerBySTLVector< DGtal::Z2i::Domain, unsigned int > Image;
  
DGtal::Board2D Pgm_to_Board (std::string filename);

DGtal::Z2i::DigitalSet Pgm_to_DigitalSet (std::string filename);

Image Pgm_to_Image (std::string filename);

DGtal::Z2i::DigitalSet Image_to_DigitalSet (Image image);

DGtal::Board2D Image_to_Board (Image image);

DGtal::Board2D DigitalSet_to_Board (DGtal::Z2i::DigitalSet set2d);


#endif
 
