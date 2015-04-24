#include "Traitement_AntiInversion.h"

using namespace std;
using namespace DGtal;
using namespace DGtal::Z2i; //We'll only consider Z² digital space on
			    //32bit integers


bool To_Inverse (Image & image){
  Domain domain = image.domain();
  Image new_image = Image(domain);
  int blancs = 0;			//variable contant le nombre de points blancs sur le bord
  int noirs = 0;			//variable contant le nombre de points noirs sur le bord  
  for (Domain::Iterator it = domain.begin(domain.lowerBound()); domain.isInside(*it);(*it)[0]++){ //itère sur les points en bas
    if (image(*it)) { blancs++; } else { noirs++; }  
  }
  for (Domain::Iterator it = domain.begin(domain.lowerBound()); domain.isInside(*it);(*it)[1]++){ //itère sur les points à gauche
    if (image(*it)) { blancs++; } else { noirs++; }  
  }
  for (Domain::Iterator it = domain.begin(domain.upperBound()); domain.isInside(*it);(*it)[0]++){ //itère sur les points en haut
    if (image(*it)) { blancs++; } else { noirs++; }  
  }
  for (Domain::Iterator it = domain.begin(domain.upperBound()); domain.isInside(*it);(*it)[1]++){ //itère sur les points à droite
    if (image(*it)) { blancs++; } else { noirs++; }  
  } 
  return (blancs > noirs);
}

Image Inverse (Image & image){
  Domain domain = image.domain();
  Image new_image = Image(domain);
  for (Domain::Iterator it = domain.begin(); it != domain.end();it++){
    new_image.setValue(*it,(1+image(*it)) %2);
  }
  return new_image;
}
    
Image Apply_AntiInversion (Image & image){
  Domain domain = image.domain();
  Image new_image = Image(domain);
  if (To_Inverse) { return Inverse(image); } else { return image; }
}


Image Traitement_AntiInversion (string filename){
  Image image = Pgm_to_Image(filename);
  image = Apply_AntiInversion(image);
  return image;
} 
