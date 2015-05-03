#include "Morphology.h"

using namespace std;
using namespace DGtal;
using namespace DGtal::Z2i; //We'll only consider Z² digital space on
			    //32bit integers

// Distance = distance manhattan (on ne peut pas se déplacer en diagonale) = norme 1 (parce que le plus simple à coder)

// Dilate à distance 1
void Dilate (MetaImage & image){
  Domain domain = image.domain();
  MetaImage new_image = MetaImage(domain);
  for (Domain::Iterator it = domain.begin(); it != domain.end();it++){
    if (image(*it)) {
      new_image.setValue(*it,1);
      new_image.setValue(*it-Point(0,1),1);
      new_image.setValue(*it-Point(0,-1),1);
      new_image.setValue(*it-Point(1,0),1);
      new_image.setValue(*it-Point(-1,0),1);
    }
  }
  image = new_image;
}

// Erode à distance 1
void Erode (MetaImage & image){
  Domain domain = image.domain();
  MetaImage new_image = MetaImage(domain);
  for (Domain::Iterator it = domain.begin(); it != domain.end();it++){
    if (!image(*it)) {
      new_image.setValue(*it,1);
      new_image.setValue(*it-Point(0,1),0);
      new_image.setValue(*it-Point(0,-1),0);
      new_image.setValue(*it-Point(1,0),0);
      new_image.setValue(*it-Point(-1,0),0);
    }
  }
  image = new_image;
}

// Dilate à distance k
void Dilate_k (MetaImage & image, int k){
  for (int i = 0; i < k; i++){
    Dilate(image);
  }
}

// Erode à distance k
void Erode_k (MetaImage & image, int k){
  for (int i = 0; i < k; i++){
    Erode(image);
  }
}

// Closing avec élément structurant = boule rayon k (norme 1)
void Closing_k (MetaImage & image, int k){
  Dilate_k(image,k);
  Erode_k(image,k);
}

// Opening avec élément structurant = boule rayon k (norme 1)
void Opening_k (MetaImage & image, int k){
  Erode_k(image,k);
  Dilate_k(image,k);
}

// Trouve l'élément structurant (= le k) : nombre minimum de pixel contigus (horizontal et vertical) 
int Find_k (MetaImage & image){
  Domain domain = image.domain();
  int min = domain.upperBound()[0] - domain.lowerBound()[0];
  for (int i = domain.lowerBound()[0]; i < domain.upperBound()[0]; i++){
    int min_temp = domain.upperBound()[0] - domain.lowerBound()[0];
    int accu = 0;
    for (int j = domain.lowerBound()[1]; j < domain.upperBound()[1]; j++){
      if (image(Point(i,j))) {accu++;}
      if (!image(Point(i,j)) && accu != 0 && accu < min_temp){min_temp = accu; accu = 0;}
    }
    if (min_temp < min){min = min_temp;}
  }
  for (int j = domain.lowerBound()[1]; j < domain.upperBound()[1];j++){
    int min_temp = domain.upperBound()[0] - domain.lowerBound()[0];
    int accu = 0;
    for (int i = domain.lowerBound()[0]; i < domain.upperBound()[0]; i++){
      if (image(Point(i,j))) {accu++;}
      if (!image(Point(i,j)) && accu != 0 && accu < min_temp){min_temp = accu; accu = 0;}
    }
    if (min_temp < min){min = min_temp;}
  }
  return min;
}

    
    
    
    
    
    
    
    
    
    
    
    
    
    

    

    

   
