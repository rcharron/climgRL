#include "LireImgPgm.h"


using namespace std;
using namespace DGtal;
using namespace DGtal::Z2i; //We'll only consider Z² digital space on
			    //32bit integers

  
Board2D Pgm_to_Board (string filename){
  //We read the PGM file
  Image image = PGMReader<Image>::importPGM(filename);

  trace.info() << "Image read :"<< image <<std::endl;

  //We convert pixels in ]0,255] into a digital set
  DigitalSet set2d( image.domain() );
  SetFromImage<DigitalSet>::append<Image>(set2d, image, 0, 255);

  //We display the set
  Board2D board;
  board << image.domain() << set2d;
  
  return board;
}

DigitalSet Pgm_to_DigitalSet (string filename){
  //We read the PGM file
  Image image = PGMReader<Image>::importPGM(filename);

  trace.info() << "Image read :"<< image <<std::endl;

  //We convert pixels in ]0,255] into a digital set
  DigitalSet set2d( image.domain() );
  SetFromImage<DigitalSet>::append<Image>(set2d, image, 0, 255);
  
  return set2d;
}

Image Pgm_to_Image (string filename){
  //We read the PGM file
  Image image = PGMReader<Image>::importPGM(filename);

  trace.info() << "Image read :"<< image <<std::endl;

  return image;
}

DigitalSet Image_to_DigitalSet (Image image){
  //We convert pixels in ]0,255] into a digital set
  DigitalSet set2d( image.domain() );
  SetFromImage<DigitalSet>::append<Image>(set2d, image, 0, 255);
  
  return set2d;
}

Board2D Image_to_Board (Image image){
  //We convert pixels in ]0,255] into a digital set
  DigitalSet set2d( image.domain() );
  SetFromImage<DigitalSet>::append<Image>(set2d, image, 0, 255);

  //We display the set
  Board2D board;
  board << image.domain() << set2d;
  
  return board;
}

Board2D DigitalSet_to_Board (DigitalSet set2d){
  //We display the set
  Board2D board;
  board << set2d.domain() << set2d;
  
  return board;
}



 
