#ifndef MORPHOLOGY_H
#define MORPHOLOGY_H

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

// Distance = distance manhattan (on ne peut pas se déplacer en diagonale) = norme 1 (parce que le plus simple à coder)

// Dilate à distance 1
void Dilate (MetaImage & image);

// Erode à distance 1
void Erode (MetaImage & image);
// Dilate à distance k
void Dilate_k (MetaImage & image, int k);

// Erode à distance k
void Erode_k (MetaImage & image, int k);

// Closing avec élément structurant = boule rayon k (norme 1)
void Closing_k (MetaImage & image, int k);

// Opening avec élément structurant = boule rayon k (norme 1)
void Opening_k (MetaImage & image, int k);

// Trouve l'élément structurant (= le k) : nombre minimum de pixel contigus (horizontal et vertical) 
int Find_k (MetaImage & image);

    
#endif
    
    
    
    
    
    
    
    
    
    
    
    

    

    

   
