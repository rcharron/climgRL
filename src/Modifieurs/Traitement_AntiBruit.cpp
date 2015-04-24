#include "Traitement_AntiBruit.h"

using namespace std;
using namespace DGtal;
using namespace DGtal::Z2i; //We'll only consider Z² digital space on
			    //32bit integers

			
/* Fait une liste des huits voisins d'un point */
vector<Point> Make_Voisins(Point p){
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

Image Apply_AntiBruit (Image image){
  Domain domain = image.domain();
  Image new_image = Image(domain);
  for (Domain::Iterator it = domain.begin(); it != domain.end();it++){
    bool to_swap = true;		//variable indiquant s'il faut changer la couleur du point considéré
    int color = image(*it);		//variable contenant la couleur du point courant (0 ou 1)
    vector<Point> voisins = Make_Voisins(*it);
    for (int i = 0; i < voisins.size(); i++){
        if (domain.isInside(voisins[i])){
	    if (image(voisins[i]) == color) {to_swap = false;}
	}
    if (to_swap) { new_image.setValue(*it,(1+color) %2); }
    }
  }
  return new_image;
}




Image Traitement_AntiBruit (string filename){
  Image image = Pgm_to_Image(filename);
  image = Apply_AntiBruit(image);
  return image;
}

    
    
    
    
    
    
    
    
    
    
    
    
    
    
    

    

    

   
