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
  MetaImage(Image img);  
  operator DGtal::Z2i::DigitalSet() ;
  operator DGtal::Board2D();
  void savePGM(std::string filename);
  void updateMeta();
  bool CanonicalValue(float x,float y);
  bool removeNoise();
  void iterRemoveNoise();//Pour la terminaison, il n'y aura pas plus de 10 itérations
  MetaImage getNormalized();
  void Open();
  void Skelton();
  void Skelton(std::string file);
  void Fill();
private:
  vector<Point> TheVoisins(Point p);
  void ComputeCenter();
  void ComputeMean();
  int width;
  int height;
  float centerx;
  float centery;
  float mean;
};


#endif