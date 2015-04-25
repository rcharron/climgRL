#ifndef META_IMAGE_H
#define META_IMAGE_H

#include <string>
#include <DGtal/base/Common.h>
#include <DGtal/io/boards/Board2D.h>
#include <DGtal/helpers/StdDefs.h>
#include <DGtal/io/readers/PGMReader.h>
#include <DGtal/io/writers/PGMWriter.h>
#include "DGtal/images/imagesSetsUtils/SetFromImage.h"
#include "DGtal/images/ImageContainerBySTLVector.h"

typedef DGtal::ImageContainerBySTLVector< DGtal::Z2i::Domain, unsigned int > Image;

class MetaImage :public Image
{
public:
  MetaImage(std::string filename);
  operator DGtal::Z2i::DigitalSet() ;
  operator DGtal::Board2D();
  void saveSVG(std::string filename);
  void updateMeta();
  int CanonicalValue(float x,float y);
private:
  void ComputeCenter();
  void ComputeMean();
  int width;
  int height;
  float centerx;
  float centery;
  float mean;
};


#endif