#include "MetaImage.h"

using namespace std;
using namespace DGtal;
using namespace DGtal::Z2i;

MetaImage::MetaImage(string filename):Image(PGMReader<Image>::importPGM(filename))
{
  //this=(PGMReader<Image>::importPGM(filename));
}
 
MetaImage::operator DigitalSet()
{
  DigitalSet set2d( this->domain() );
  SetFromImage<DigitalSet>::append<Image>(set2d, *this, 0, 255);
  
  return set2d;
}

MetaImage::operator Board2D()
{
  DigitalSet set2d( this->domain() );
  SetFromImage<DigitalSet>::append<Image>(set2d, *this, 0, 255);
  
  Board2D board;
  board << set2d.domain() << set2d;
  return board;
}

void MetaImage::saveSVG(string filename)
{
  static_cast<Board2D>(*this).saveSVG("rat-9-inverse.scg");
//  PGMWriter<Image>::exportPGM(filename,*this);
}
