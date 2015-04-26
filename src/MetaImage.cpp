#include "MetaImage.h"
#include <cmath>

using namespace std;
using namespace DGtal;
using namespace DGtal::Z2i;

MetaImage::MetaImage(string filename):Image(PGMReader<Image>::importPGM(filename))
{
  updateMeta();
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
  static_cast<Board2D>(*this).saveSVG(filename.c_str());
//  PGMWriter<Image>::exportPGM(filename,*this);
}

void MetaImage::updateMeta()
{
  //ComputeCenter();
  //ComputeMean();
}


/*void MetaImage::ComputeCenter()
{
  width=this->domain().upperBound()[0];
  height=this->domain().upperBound()[1];
  centerx=0;
  centery=0;
  int p=0;
  for(int i=0;i<width;i++)
  {
    for (int j=0;j<height;j++)
    {
      if(getValue(i,j)>0)
      {
	centerx+=i;
	centery+=j;
	p++;
      }
    }
  }
  centerx/=p;
  centery/=p;
}*/

/*void MetaImage::ComputeMean()
{
  mean=0;
  int p=0;
  for(int i=0;i<width;i++)
  {
    for (int j=0;j<height;j++)
    {
      if(getValue(i,j))
      {
	mean+=(centerx-i)*(centerx-i)+(centery-j)*(centery-j);
	p++;
      }
    }
  }
  mean/=p;
  mean=sqrt(mean);
}*/

/*int MetaImage::CanonicalValue(float x, float y)
{
  x-=0.5f;
  int x=centerx+x*4*mean;
  int y=centery+y*4*mean;
  return getValue(x,y);
}*/
