#ifndef TRAITEMENT_ANTIBRUIT_H
#define TRAITEMENT_ANTIBRUIT_H

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

			
/* Fait une liste des huits voisins d'un point */
std::vector<DGtal::Z2i::Point> Anti_Bruit_Make_Voisins(DGtal::Z2i::Point p);

MetaImage Apply_AntiBruit (MetaImage & image);

void Traitement_AntiBruit (MetaImage & image);

    
#endif    
    
    
    
    
    
    
    
    
    
    
    
    
    

    

    

   
