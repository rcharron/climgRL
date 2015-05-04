#ifndef TANGENTE_H
#define TANGENTE_H

///////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include <vector>
#include <DGtal/base/Common.h>
#include <DGtal/io/boards/Board2D.h>
#include <DGtal/helpers/StdDefs.h>
#include <DGtal/geometry/curves/ArithmeticalDSSComputer.h>
#include "../MetaImage.h"
///////////////////////////////////////////////////////////////////////////////




typedef std::vector<DGtal::Z2i::Point>::const_iterator Iterator;

/*
std::vector<DGtal::Z2i::Point> Voisins(DGtal::Z2i::Point p);

DGtal::Z2i::Point Suivant (DGtal::Z2i::Domain & domain, DGtal::Z2i::DigitalSet & set, std::vector<DGtal::Z2i::Point> & bord);

std::vector<DGtal::Z2i::Point> ExtractBorder(DGtal::Z2i::DigitalSet & set, DGtal::Z2i::Point p);
*/

DGtal::ArithmeticalDSSComputer< Iterator, DGtal::Z2i::Integer, 4> Tangent (std::vector<DGtal::Z2i::Point> & bord, DGtal::Z2i::Point p);

DGtal::ArithmeticalDSSComputer< Iterator, DGtal::Z2i::Integer, 4> Left_Tangent (std::vector<DGtal::Z2i::Point> & bord, DGtal::Z2i::Point p);

DGtal::ArithmeticalDSSComputer< Iterator, DGtal::Z2i::Integer, 4> Right_Tangent (std::vector<DGtal::Z2i::Point> & bord, DGtal::Z2i::Point p);


#endif