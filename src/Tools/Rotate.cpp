/**
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU Lesser General Public License as
 *  published by the Free Software Foundation, either version 3 of the
 *  License, or  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 **/
/**
 * @file imgRotate
 * @ingroup converters
 * @author David Coeurjolly (\c david.coeurjolly@liris.cnrs.fr)
 *
 * @date 2015/03/24
 *
 *
 * This file is part of the DGtal library.
 */


#include "Rotate.h"

using namespace std;
using namespace DGtal;
using namespace DGtal::Z2i;


///////////////////////////////////////////////////////////////////////////////
// namespace po = boost::program_options;
MetaImage Rotate (MetaImage & image, double angle)
{

/*  bool parseOK=true;
  po::variables_map vm;
  try{
    po::store(po::parse_command_line(argc, argv, general_opt), vm);  
  }catch(const std::exception& ex){
    trace.info()<< "Error checking program options: "<< ex.what()<< std::endl;
    parseOK=false;
  }
  po::notify(vm);    
  if(vm.count("help")||argc<=1|| !parseOK)
    {
      trace.info()<< "Rotate an image by a given angle a binary object with 0 values as background points and values >0 for the foreground ones." <<std::endl << "Basic usage: "<<std::endl
      << "\t imgRotate [options] --input <imageName> --output <outputImage> --angle 0.3"<<std::endl
      << general_opt << "\n";
      return 0;
    } */
  
  //Parameters
/*  if ( ! ( vm.count ( "input" ) ) ) missingParam ( "--input" );
  const std::string input = vm["input"].as<std::string>();
  if ( ! ( vm.count ( "output" ) ) ) missingParam ( "--output" );
  const std::string  output = vm["output"].as<std::string>();
  const double angle = vm["angle"].as<double>(); */
  
  //typedef functors::IntervalForegroundPredicate<MetaImage> Binarizer;
//  MyImage image = GenericReader<MyImage>::import( input );
//  trace.info() <<"Input image: "<< image<<std::endl;
  
  typedef functors::BackwardRigidTransformation2D<Z2i::Space> RotateFunctor;
  Z2i::RealPoint center = image.domain().upperBound();
  center -= image.domain().lowerBound();
  center /= 2.0;
  
  RotateFunctor rotationFunctor(center,
                                angle,
                                Z2i::RealPoint(0.0,0.0));
  
  functors::Identity idD;
  typedef functors::DomainRigidTransformation2D<MetaImage::Domain, RotateFunctor> MyDomainTransformer;
//cout << "coucou1\n";
  MyDomainTransformer rotDomain(rotationFunctor);
  typedef MyDomainTransformer::Bounds Bounds;
//cout << "coucou2\n";
  Bounds newdomain = rotDomain( image.domain());
//cout << "coucou3\n";
  MetaImage::Domain transformedDomain ( Point(0,0), newdomain.second - newdomain.first);
  typedef ConstImageAdapter<MetaImage, MetaImage::Domain, RotateFunctor, MetaImage::Value, functors::Identity > MetaImageBackwardAdapter;
//cout << "coucou4\n";
  MetaImageBackwardAdapter backwardImageAdapter ( image, transformedDomain , rotationFunctor, idD );
//cout << "coucou5\n";  
  MetaImage new_image = MetaImage( DGtal::ImageContainerBySTLVector< DGtal::Z2i::Domain, unsigned int >(transformedDomain));
//cout << "coucou6\n";
  for (MetaImage::Domain::Iterator it = transformedDomain.begin(); it != transformedDomain.end();it++){
    new_image.setValue(*it,backwardImageAdapter(*it));
  }
  
  return new_image;
//  backwardImageAdapter >> output;
//  return backwardImageAdapter;
}