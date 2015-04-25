#include "Traitement_AntiInversion.h"

using namespace std;
using namespace DGtal;
using namespace DGtal::Z2i; //We'll only consider Z² digital space on
			    //32bit integers


bool To_Inverse (MetaImage & image){
  Domain domain = image.domain();
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

void Inverse (MetaImage & image){
  Domain domain = image.domain();
  for (Domain::Iterator it = domain.begin(); it != domain.end();it++){
    image.setValue(*it,(1+image(*it)) %2);
  }
}
    
void Apply_AntiInversion (MetaImage & image){
  Domain domain = image.domain();
  if (To_Inverse) Inverse(image);
}


void Traitement_AntiInversion (MetaImage& img){
  Apply_AntiInversion(img);
} 
