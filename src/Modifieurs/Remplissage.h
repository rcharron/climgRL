#ifndef REMPLISSAGE_H
#define REMPLISSAGE_H

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
#include "../MetaImage.h"
///////////////////////////////////////////////////////////////////////////////

/*
REMPLISSAGE
*/


using namespace std;
using namespace DGtal;
using namespace DGtal::Z2i; //We'll only consider Z² digital space on
			    //32bit integers

/* Fait une liste des huits voisins d'un point */
std::vector<DGtal::Z2i::Point> Remplissage_Make_Voisins(DGtal::Z2i::Point p);

Image Apply_Remplissage (Image & image);

void Remplissage (Image & image);

    
#endif      
    
    
    
    
    
    
    
    
    
    
    
    
    

    

    

   
