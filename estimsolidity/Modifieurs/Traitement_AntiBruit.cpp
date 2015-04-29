#include "Traitement_AntiBruit.h"

/*
TRAITEMENT ANTI BRUIT 
  On fait la loi de la majorité parmi la couleur du pixel et de ses voisins
*/

using namespace std;
using namespace DGtal;
using namespace DGtal::Z2i; //We'll only consider Z² digital space on
			    //32bit integers

			
/* Fait une liste des huits voisins d'un point */
vector<Point> Anti_Bruit_Make_Voisins(Point p){
  vector<Point> voisins;
  voisins.push_back(Point(p[0]-1,p[1]));
  voisins.push_back(Point(p[0],p[1]-1));
  voisins.push_back(Point(p[0]+1,p[1]));
  voisins.push_back(Point(p[0],p[1]+1));
  voisins.push_back(Point(p[0]-1,p[1]-1));
  voisins.push_back(Point(p[0]+1,p[1]-1));
  voisins.push_back(Point(p[0]+1,p[1]+1));
  voisins.push_back(Point(p[0]-1,p[1]+1));  
  return voisins;
}

MetaImage Apply_AntiBruit (MetaImage & image){
  Domain domain = image.domain();
  MetaImage new_image = MetaImage(domain);
  for (Domain::Iterator it = domain.begin(); it != domain.end();it++){
    int noirs = 1-image(*it);		//variable indiquant le nombre de noirs
    int blancs = image(*it);		//variable indiquant le nombre de blancs
    vector<Point> voisins = Anti_Bruit_Make_Voisins(*it);
    for (int i = 0; i < voisins.size(); i++){
        if (domain.isInside(voisins[i])){
	    noirs  += 1-image(voisins[i]);
	    blancs += image(voisins[i]);
	}
    }
    new_image.setValue(*it,(1+(noirs>blancs)) %2);
  }
  return new_image;
}




void Traitement_AntiBruit (MetaImage & image){
  image = Apply_AntiBruit(image);
}

    
    
    
    
    
    
    
    
    
    
    
    
    
    
    

    

    

   
