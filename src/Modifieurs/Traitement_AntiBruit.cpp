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

bool Apply_AntiBruit (MetaImage & image){
  Domain domain = image.domain();
  MetaImage new_image = MetaImage(domain);
  bool change=false;
  for (Domain::Iterator it = domain.begin(); it != domain.end();it++){
    int noirs =0; 		//variable indiquant le nombre de noirs
    int blancs =0;		//variable indiquant le nombre de blancs
    bool couleur=image(*it)>0;
    couleur?blancs=1:noirs=1;
    vector<Point> voisins = Anti_Bruit_Make_Voisins(*it);
    for (int i = 0; i < voisins.size(); i++){
        if (domain.isInside(voisins[i])){
	    image(voisins[i])>0?blancs++:noirs++;
	    //noirs  += 1-image(voisins[i]);
	    //blancs += image(voisins[i]);
	}
    }
    if((blancs>noirs)^couleur)change=true;
    if (noirs > blancs) {new_image.setValue(*it,0);}
    else {new_image.setValue(*it,1);}
//    new_image.setValue(*it,(1+(noirs>blancs)) %2);
  }
  image=new_image;
  return change;
}




void Traitement_AntiBruit (MetaImage & image){
  while(Apply_AntiBruit(image));
}

    
    
    
    
    
    
    
    
    
    
    
    
    
    
    

    

    

   
